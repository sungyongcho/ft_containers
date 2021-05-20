/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:08:32 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 07:56:58 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "BaseIterators.hpp"
#include "deque.hpp"
#include "list.hpp"
#include "vector.hpp"

namespace ft {

template <typename T, typename C = ft::deque<T> >
class stack {
 public:
  C c;
  typedef T value_type;
  typedef C container_type;
  typedef size_t size_type;
   stack(const container_type &ctnr = C()) : c(ctnr) {};
  bool empty() const;
  size_type size() const;
  value_type &top();
  const value_type &top() const;
  void push(const value_type &val);
  void pop();
};

template <typename T, class C>
bool stack<T, C>::empty() const { return (c.empty()); }

template <typename T, class C>
typename stack<T, C>::size_type stack<T, C>::size() const { return (c.size()); }

template <typename T, class C>
typename stack<T, C>::value_type &stack<T, C>::top() { return (c.back()); }

template <typename T, class C>
const typename stack<T, C>::value_type &stack<T, C>::top() const { return (c.back()); }

template <typename T, class C>
void stack<T, C>::push(const value_type &val) { c.push_back(val); }

template <typename T, class C>
void stack<T, C>::pop() { c.pop_back(); }

template <class T, class C>
bool operator==(const stack<T, C> &lhs, const stack<T, C> &rhs) { return lhs.c == rhs.c; }
template <class T, class C>
bool operator!=(const stack<T, C> &lhs, const stack<T, C> &rhs) { return lhs.c != rhs.c; }
template <class T, class C>
bool operator<(const stack<T, C> &lhs, const stack<T, C> &rhs) { return lhs.c < rhs.c; }
template <class T, class C>
bool operator<=(const stack<T, C> &lhs, const stack<T, C> &rhs) { return lhs.c <= rhs.c; }
template <class T, class C>
bool operator>(const stack<T, C> &lhs, const stack<T, C> &rhs) { return lhs.c > rhs.c; }
template <class T, class C>
bool operator>=(const stack<T, C> &lhs, const stack<T, C> &rhs) { return lhs.c >= rhs.c; }

}  // namespace ft

#endif
