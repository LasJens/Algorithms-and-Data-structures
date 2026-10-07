#ifndef ARRAY_TRAITS_H
#define ARRAY_TRAITS_H

#include <iostream>
#include <type_traits>

template <class T>
struct IsArray : std::false_type {};

template <class T, size_t Sizee>
struct IsArray<T[Sizee]> : std::true_type {};

template <class T>
struct IsArray<T[]> : std::true_type {};

template <class T>
constexpr bool kIsArrayV = IsArray<T>::value;

template <class T>
struct Rank : std::integral_constant<size_t, 0> {};

template <class T>
struct Rank<T[]> : std::integral_constant<size_t, 1 + Rank<T>::value> {};

template <class T, size_t Sizee>
struct Rank<T[Sizee]> : std::integral_constant<size_t, 1 + Rank<T>::value> {};

template <class T>
constexpr size_t kRankV = Rank<T>::value;

template <class T>
struct Size : std::integral_constant<size_t, 1> {};

template <class T>
struct Size<T[]> : std::integral_constant<size_t, 0> {};

template <class T, size_t Sizee>
struct Size<T[Sizee]> : std::integral_constant<size_t, Sizee> {};

template <class T>
constexpr inline size_t kSizeV = Size<T>::value;

template <class T>
struct TotalSize : std::integral_constant<size_t, 1> {};

template <class T>
struct TotalSize<T[]> : std::integral_constant<size_t, 0> {};

template <class T, size_t Sizee>
struct TotalSize<T[Sizee]> : std::integral_constant<size_t, Sizee * TotalSize<T>::value> {};

template <class T>
constexpr size_t kTotalSizeV = TotalSize<T>::value;

template <class T>
struct RemoveArray {
  using Type = T;
};

template <class T>
struct RemoveArray<T[]> {
  using Type = T;
};

template <class T, size_t Sizee>
struct RemoveArray<T[Sizee]> {
  using Type = T;
};

template <class T>
using RemoveArrayT = typename RemoveArray<T>::Type;

template <class T>
struct RemoveAllArrays {
  using Type = T;
};

template <class T>
struct RemoveAllArrays<T[]> {
  using Type = RemoveAllArrays<T>::Type;
};

template <class T, size_t N>
struct RemoveAllArrays<T[N]> {
  using Type = RemoveAllArrays<T>::Type;
};

template <class T>
using RemoveAllArraysT = typename RemoveAllArrays<T>::Type;

template <class T, size_t Dim>
struct Extent : std::integral_constant<size_t, 0> {};

template <class T, size_t Dim>
struct Extent<T[], Dim> : std::integral_constant<size_t, Extent<T, Dim - 1>::value> {};

template <class T, size_t Sizee, size_t Dim>
struct Extent<T[Sizee], Dim> : std::integral_constant<size_t, Extent<T, Dim - 1>::value> {};

template <class T, size_t Sizee>
struct Extent<T[Sizee], 0> : std::integral_constant<size_t, Sizee> {};

template <class T, size_t Dim>
constexpr size_t kExtentV = Extent<T, Dim>::value;

#endif