/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 00:13:03 by sucho             #+#    #+#             */
/*   Updated: 2021/05/04 19:13:06 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>

#include <memory> //for allocator
#include <cmath>
#include <cstdlib>  //for ptrdiff_h, idk rest yet
#include <iostream>
#include <string>

namespace ft {
template <typename Iterator>
long long distance(Iterator first, Iterator last) {
  Iterator it_a(first);
  Iterator it_b(first);
  long long count = 0;
  while (true) {
    if (it_a == last)
      return count;
    if (it_b == last)
      return (-count);
    count++;
    ++it_a;
    --it_b;
    if (first == it_a && it_a == it_b)
      throw std::exception();
  }
}
template <typename Iterator>
Iterator next(Iterator first, size_t number) {
  while (number--)
    ++first;
  return first;
}

template <typename Iterator>
void advance(Iterator &first, size_t number) {
  while (number--)
    ++first;
}

template <typename T>
bool less(T lhs, T rhs) {
  return (lhs < rhs);
}

template <typename T>
bool is_const(const T &ref) {
  static_cast<void>(ref);
  return true;
}

template <typename T>
bool is_const(T &ref) {
  static_cast<void>(ref);
  return false;
}

template <typename T>
struct is_const_type { static const bool value = false; };
template <typename T>
struct is_const_type<const T> { static const bool value = false; };

template <class T>
T &unconst(const T &val) {
  return const_cast<T &>(val);
}

template <class T>
void swap(T &a, T &b) {
  T tmp(a);
  a = b;
  b = tmp;
}

template <typename T>
T fwd(T it, int n) {
  if (n > 0)
    while (n--) it++;
  else
    while (n++) it--;
  return (it);
}

template <typename T>
bool sort_ascend(T a, T b) {
  return (a < b);
}

template <typename T>
bool sort_descend(T a, T b) {
  return (a > b);
}

template <typename T>
bool is_even(T a) {
  return (~a & 1);
}

ssize_t circular_increment(const ssize_t &value, const ssize_t &max) {
  if (value < max && value >= 0)
    return value;
  if (value == max)
    return 0;
  if (value == -1)
    return max - 1;
  else
    throw std::exception();
}

long long circular_clamp(const long long &value, const long long &low, const long long &high) {
  if (value >= low && value < high)
    return value;
  long long dist_min = std::abs(low - value);
  long long dist_max = std::abs(high - value);
  if (dist_min < dist_max)
    return dist_min % (high - low) == 0 ? low : high - (dist_min % (high - low));
  else
    return low + (dist_max % (high - low));
}

long long substract_size_t(const size_t &a, const size_t &b) {
  long long la = a;
  long long lb = b;
  return (la - lb);
}

template <bool Condition, class T = void>
struct enable_if {};
template <class T>
struct enable_if<true, T> { typedef T type; };

template <typename T>
struct wrapper {
  typedef T type;
};

template <class T>
struct remove_const {
  typedef T type;
};
template <class T>
struct remove_const<const T> { typedef T type; };

template <class T>
struct add_const { typedef const T type; };
template <class T>
struct add_const<const T> { typedef const T type; };

template <typename T, typename U>
struct is_same { static const bool value = false; };
template <typename T>
struct is_same<T, T> { static const bool value = true; };

template <bool flag, class IsTrue, class IsFalse>
struct choose;
template <class IsTrue, class IsFalse>
struct choose<true, IsTrue, IsFalse> { typedef IsTrue type; };
template <class IsTrue, class IsFalse>
struct choose<false, IsTrue, IsFalse> { typedef IsFalse type; };

}  // namespace ft
