#pragma once
#include <cstddef>
#include <vector>
#include <string>
#include <iostream>

class BigInteger {
private:
    std::vector<unsigned long long> blocks;
    bool negative;
public:
    BigInteger();
    BigInteger(int value);
    BigInteger(BigInteger const& other);
    BigInteger(const std::string& str);

    BigInteger operator+(BigInteger const& other) const;
    BigInteger& operator+=(BigInteger const& other);
    BigInteger operator-(BigInteger const& other) const;
    BigInteger& operator-=(BigInteger const& other);
    BigInteger operator*(BigInteger const& other) const;
    BigInteger& operator*=(BigInteger const& other);
    BigInteger operator/(int other) const;
    BigInteger operator/(BigInteger const& other) const;
    BigInteger& operator/=(BigInteger const& other);
    BigInteger operator%(BigInteger const& other) const;
    BigInteger& operator%=(BigInteger const& other);
    
    BigInteger operator-() const;

    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);

    bool operator==(BigInteger const& other) const;
    bool operator!=(BigInteger const& other) const;
    bool operator<(BigInteger const& other) const;
    bool operator<=(BigInteger const& other) const;
    bool operator>(BigInteger const& other) const;
    bool operator>=(BigInteger const& other) const;

    std::string toString() const;
    void change_sign();
    bool is_negative() const;
    operator bool();

    friend std::istream& operator>>(std::istream& in, BigInteger& number);
    friend std::ostream& operator<<(std::ostream& out, BigInteger const& number);
};
