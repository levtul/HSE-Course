#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
    static constexpr int pos = -1;
};

template<typename Head, typename Tail>
struct IndexOf<TypeList<Head, Tail>, Head> {
    static constexpr int pos = 0;
};

template<typename Head, typename Tail, typename TargetType>
struct IndexOf<TypeList<Head, Tail>, TargetType> {
    static constexpr int pos = (IndexOf<Tail, TargetType>::pos == -1 ? -1 : 1 + IndexOf<Tail, TargetType>::pos);
};
