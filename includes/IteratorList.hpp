/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorList.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:24:32 by sucho             #+#    #+#             */
/*   Updated: 2021/04/05 03:14:42 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORLIST_HPP
#define ITERATORLIST_HPP

#include "Iterator.hpp"

namespace ft {
template <class T>
struct DoubleLinkedList {
  DoubleLinkedList *prev;
  DoubleLinkedList *next;
  T *element;
};

template <class T, class Category = bidirectional_iterator_tag>
class IteratorList {
 private:
  // 일단 없이 해보자
  // IteratorList operator+(const IteratorList &rhs) const;
  // IteratorList operator+(int n) const;
  // IteratorList operator-(const IteratorList &rhs) const;
  // IteratorList operator-(int n) const;

  // bool opeartor < (const IteratorList &rhs) const;
  // bool opeartor > (const IteratorList &rhs) const;
  // bool opeartor >= (onst IteratorList & rhs) const;
  // bool opeartor <= (const IteratorList &rhs) const;

  // IteratorList &operator+=(int n) const;
  // IteratorList &operator-=(int n) const;

  // T &opeartor[](int n) const;

 protected:
  DoubleLinkedList<T> *ptr;

 public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef Category category;
  typedef std::ptrdiff_t difference_type;

  IteratorList(void) {}
  IteratorList(const IteratorList &other) { *this = other; }
  IteratorList &operator= (const IteratorList &rhs) {
    this->ptr = rhs.ptr;
    return (*this);
  }
  IteratorList(DoubleLinkedList<T> *list) { this->ptr = list;}
};

template <class T>
class ReverseIteratorList : public IteratorList<T> {
};

template <class T>
class ConstIteratorList : public IteratorList<T> {
};

template <class T>
class ConstReverseIteratorList : public IteratorList<T> {
};

};  // namespace ft

#endif  //ITERATORLIST_HPP
