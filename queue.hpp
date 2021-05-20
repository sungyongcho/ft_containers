/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:11:31 by sucho             #+#    #+#             */
/*   Updated: 2021/05/20 18:11:32 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseIterators.hpp"
#include "vector.hpp"
#include "list.hpp"

namespace ft {

template <typename T, class C>
class queue {
 public:
  C c;
  typedef T value_type;
  typedef C container_type;
  typedef size_t size_type;
  explicit queue(const container_type &ctnr = container_type());
  bool empty() const;
  size_type size() const;
  value_type &front();
  const value_type &front() const;
  value_type &back();
  const value_type &back() const;
  void push(const value_type &val);
  void pop();
};

template <typename T, class C>
queue<T, C>::queue(const container_type &ctnr) { c = ctnr; }

template <typename T, class C>
bool queue<T, C>::empty() const { return (c.empty()); }

template <typename T, class C>
typename queue<T, C>::size_type queue<T, C>::size() const { return (c.size()); }

template <typename T, class C>
typename queue<T, C>::value_type &queue<T, C>::front() { return (c.front()); }
template <typename T, class C>
const typename queue<T, C>::value_type &queue<T, C>::front() const { return (c.front()); }
template <typename T, class C>
typename queue<T, C>::value_type &queue<T, C>::back() { return (c.back()); }
template <typename T, class C>
const typename queue<T, C>::value_type &queue<T, C>::back() const { return (c.back()); }

template <typename T, class C>
void queue<T, C>::push(const value_type &val) { c.push_back(val); }

template <typename T, class C>
void queue<T, C>::pop() { c.pop_front(); }

template <class T, class C>
bool operator==(const queue<T, C> &lhs, const queue<T, C> &rhs) { return lhs.c == rhs.c; }
template <class T, class C>
bool operator!=(const queue<T, C> &lhs, const queue<T, C> &rhs) { return lhs.c != rhs.c; }
template <class T, class C>
bool operator<(const queue<T, C> &lhs, const queue<T, C> &rhs) { return lhs.c < rhs.c; }
template <class T, class C>
bool operator<=(const queue<T, C> &lhs, const queue<T, C> &rhs) { return lhs.c <= rhs.c; }
template <class T, class C>
bool operator>(const queue<T, C> &lhs, const queue<T, C> &rhs) { return lhs.c > rhs.c; }
template <class T, class C>
bool operator>=(const queue<T, C> &lhs, const queue<T, C> &rhs) { return lhs.c >= rhs.c; }

}  // namespace ft
