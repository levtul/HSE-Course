#include "biginteger.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

const int mod = 1000000000;

BigInteger::BigInteger() {
	blocks.push_back(0);
	negative = 0;
}
BigInteger::BigInteger(int value) {
	blocks.push_back(abs(value));
	negative = value < 0;
}
BigInteger::BigInteger(BigInteger const &other) {
	negative = other.negative;
	for (auto block : other.blocks) {
		blocks.push_back(block);
	}
}
BigInteger::BigInteger(const std::string &str) {
	std::string number = str;
	negative = 0;
	if (number[0] == '-' && (str.size() != 2 || str[1]!='0')) {
		negative = 1;
		number.erase(number.begin());
	}
	unsigned long long len = (unsigned long long) ((number.size() - 1) / 9) + 1;
	blocks.resize(len);
	unsigned long long block_number;
	for (int counter = 0; counter < number.size(); counter++) {
		block_number = (number.size() - counter - 1) / 9;
		blocks[block_number] = blocks[block_number] * 10 + ((unsigned long long)number[counter] - '0');
	}
}

BigInteger BigInteger::operator+(BigInteger const& other) const {
	if (negative && !other.negative) {
		return other - *this;
	}
	else if (!negative && other.negative) {
		return *this - other;
	}
	BigInteger result;
	bool change = 0;
	if (negative && other.negative) {
		change = 1;
	}
	result.blocks.pop_back();
	size_t min = (blocks.size() < other.blocks.size() ? blocks.size() : other.blocks.size());
	size_t max = (blocks.size() > other.blocks.size() ? blocks.size() : other.blocks.size());
	int overflow = 0;
	for (size_t i = 0; i < min; i++) {
		result.blocks.push_back((blocks[i] + other.blocks[i] + overflow) % mod);
		overflow = (blocks[i] + other.blocks[i] + overflow) / mod;
	}
	if (blocks.size() == max) {
		for (size_t i = min; i < max; i++) {
			result.blocks.push_back((blocks[i] + overflow) % mod);
			overflow = (blocks[i] + overflow) / mod;
		}
	}
	else {
		for (size_t i = min; i < max; i++) {
			result.blocks.push_back((other.blocks[i] + overflow) % mod);
			overflow = (other.blocks[i] + overflow) / mod;
		}
	}
	if (overflow) {
		result.blocks.push_back(overflow);
	}
	if (change) {
		result.change_sign();
	}
	return result;
}
BigInteger& BigInteger::operator+=(BigInteger const& other) {
	*this = *this + other;
	return *this;
}
BigInteger BigInteger::operator-(BigInteger const& other) const {
	if (negative && !other.negative) {
		return (-*this) + (-other);
	}
	else if (!negative && other.negative) {
		return *this + (-other);
	}
	if (negative && other.negative) {
		return other - (*this);
	}
	BigInteger result;
	if (*this < other) {
		return -(other - *this);
	}
	result.blocks.pop_back();
	int min = (blocks.size() < other.blocks.size() ? blocks.size() : other.blocks.size());
	int max = (blocks.size() > other.blocks.size() ? blocks.size() : other.blocks.size());
	int overflow = 0;
	for (int i = 0; i < min; i++) {
		result.blocks.push_back((blocks[i] - other.blocks[i] - overflow + mod) % mod);
		overflow = (((long long)blocks[i] - overflow) < (long long) other.blocks[i]);
	}
	if (blocks.size() == max) {
		for (int i = min; i < max; i++) {
			result.blocks.push_back((blocks[i] - overflow + mod) % mod);
			overflow = ((long long) blocks[i] - overflow < 0);
		}
	}
	if (result.blocks.size() > 1 && result.blocks.back() == 0) {
		while (result.blocks.back() == 0) {
			result.blocks.pop_back();
		}
	}
	return result;
}
BigInteger& BigInteger::operator-=(BigInteger const& other) {
	*this = *this - other;
	return *this;
}
BigInteger BigInteger::operator*(BigInteger const& other) const {
	if (*this == 0 || other == 0) {
		return 0;
	}
	BigInteger result;
	result.blocks.resize(blocks.size() + other.blocks.size() - 1);
	unsigned long long overflow = 0, tmp = 0;
	for (size_t i = 0; i < blocks.size(); i++) {
		for (size_t j = 0; j < other.blocks.size(); j++) {
			int block_num = i + j;
			tmp = (result.blocks[block_num] + overflow + blocks[i] * other.blocks[j]) / mod;
			result.blocks[block_num] = ((result.blocks[block_num] + overflow) % mod + (blocks[i] * other.blocks[j]) % mod) % mod;
			overflow = tmp;
		}
		int block_num = i + other.blocks.size();
		while (overflow) {
			if (block_num == result.blocks.size()) {
				result.blocks.push_back(0);
			}
			tmp = (result.blocks[block_num] + overflow) / mod;
			result.blocks[block_num] = (result.blocks[block_num] + overflow) % mod;
			overflow = tmp;
		}
	}
	return result;
}
BigInteger& BigInteger::operator*=(BigInteger const& other)  {
	*this = *this * other;
	return *this;
}
BigInteger BigInteger::operator/(int other) const {
	BigInteger result;
	if (*this == 0) {
		return result;
	}
	result.blocks.pop_back();
	unsigned long long overflow = 0;
    for (size_t i = 0; i < blocks.size(); i++) {
		size_t block_num = blocks.size() - i - 1;
		int block = blocks[block_num];
		result.blocks.push_back((block + overflow)/other);
		overflow = ((block + overflow) % other) * mod;
	}
	for (size_t i = 0; i < result.blocks.size() / 2; i++){
		std::swap(result.blocks[i], result.blocks[result.blocks.size() - i - 1]);
	}
	if (result.blocks.back() == 0 && result.blocks.size() != 1) {
		result.blocks.pop_back();
	}
	if (negative != (other < 0)) {
		result++;
		result.negative = 1;
	}
	return result;
}
BigInteger BigInteger::operator/(BigInteger const& other) const {
    BigInteger result;
	if (*this == 0) {
		return result;
	}
	BigInteger l = 0, r = *this;
	while(r - l > BigInteger(1)) {
		BigInteger m = (r + l) / 2;
		BigInteger mul = m * other;
		if (mul > *this) {
			r = m;
		}
		else {
			l = m;
		}
	}
	result = l;
	if (negative != other.negative) {
		result++;
		result.negative = 1;
	}
	return result;
}
BigInteger& BigInteger::operator/=(BigInteger const& other) {
    *this = *this / other;
    return *this;
}
BigInteger BigInteger::operator%(BigInteger const& other) const {
    return *this - *this / other * other;
}
BigInteger& BigInteger::operator%=(BigInteger const& other) {
    *this = *this - *this / other * other;
    return *this;
}

BigInteger BigInteger::operator-() const {
	BigInteger res(*this);
	res.change_sign();
	return res;
}

BigInteger& BigInteger::operator++() {
	*this += 1;
	return *this;
}
BigInteger BigInteger::operator++(int) {
	BigInteger other(*this);
	(*this) += 1;
	return other;
}
BigInteger& BigInteger::operator--() {
	*this = *this - BigInteger(1);
	return *this;
}
BigInteger BigInteger::operator--(int) {
	BigInteger other(*this);
	(*this)--;
	return other;
}

bool BigInteger::operator==(BigInteger const& other) const {
	if (blocks.size() != other.blocks.size() || (negative != other.negative && blocks[0])) {
		return 0;
	}
	for (size_t i = 0; i < blocks.size(); i++) {
		if (blocks[i] != other.blocks[i]) {
			return 0;
		}
	}
	return 1;
}
bool BigInteger::operator!=(BigInteger const& other) const {
	return !this->operator==(other);
}
bool BigInteger::operator<(BigInteger const& other) const {
	if (negative != other.negative) {
		return negative > other.negative;
	}
	if (blocks.size() < other.blocks.size()) {
		return !negative;
	}
	if (blocks.size() > other.blocks.size()) {
		return negative;
	}
	for (int i = blocks.size() - 1; i >= 0; i--) {
		if (blocks[i] < other.blocks[i]) {
			return !negative;
		}
		if (blocks[i] > other.blocks[i]) {
			return negative;
		}
	}
	return 0;
}
bool BigInteger::operator<=(BigInteger const& other) const {
	return *this == other || *this < other;
}
bool BigInteger::operator>(BigInteger const& other) const {
	return !(*this <= other);
}
bool BigInteger::operator>=(BigInteger const& other) const {
	return *this == other || *this > other;
}

std::string BigInteger::toString() const {
	if (blocks.size() == 1 && blocks[0] == 0) {
		return "0";
	}
		std::string res = "";
	for (size_t i = 0; i < blocks.size() - 1; i++) {
		unsigned long long block = blocks[i];
		for (int i = 0; i < 9; i++) {
			res.push_back('0' + (block % 10));
			block /= 10;
		}
	}
	int block = blocks.back();
	while (block) {
		res.push_back('0' + (block % 10));
		block /= 10;
	}
	for (size_t i = 0; i < res.size() / 2; i++) {
		std::swap(res[i], res[res.size() - i - 1]);
	}
	if (negative) {
		res= "-" + res;
	}
	return res;
}
void BigInteger::change_sign() {
	if (blocks.size() == 1 && blocks[0] == 0) return;
	negative = !negative;
}
BigInteger::operator bool() {
	return (*this != BigInteger(0));
}

std::istream& operator>>(std::istream& in, BigInteger& number) {
	std::string str;
	in >> str;
	number = BigInteger(str);
	return in;
}
std::ostream& operator<<(std::ostream& out, BigInteger const& number) {
	out << number.toString();
	return out;
}
