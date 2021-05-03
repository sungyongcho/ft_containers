/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 00:32:01 by sucho             #+#    #+#             */
/*   Updated: 2021/05/02 00:07:35 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft {
template <typename T, class Alloc>
class list {
 public:
  typedef size_t size_type;
  typedef T &reference;
  typedef T *pointer;
  typedef T value_type;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef const T const_value_type;
  typedef Alloc allocator_type;

 protected:
  typedef ft::DoublyLinkedList<T> Node;
  typedef ft::list_sentry<T> Sentry;

  size_t _size;
  Node *_sentry;
  Alloc _alloc;

  void link(Node *n1, Node *n2);
  Node *unlink(Node *e);
  void insert_node(Node *e, Node *n1, Node *n2);
  void delete_node(Node *e);
  Node *create_node(const T &val);
  void swap_nodes(Node *n1, Node *n2);
  void empty_list();

  typedef typename Alloc::template rebind<Node>::other node_alloc;
  typedef typename Alloc::template rebind<Node>::other sentry_alloc;

  template <typename U, bool is_const>
  class list_iterator : public base_list_iterator<U, is_const> {
   protected:
    using base_list_iterator<U, is_const>::ptr;
    using base_list_iterator<U, is_const>::get;

   public:
    typedef U value_type;
    typedef typename choose<is_const, const U &, U &>::type reference;
    typedef typename choose<is_const, const U &, U &>::type pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename remove_const<U>::type non_const_type;
    typedef list_iterator<non_const_type, false> non_const_type;

    list_iterator() : base_list_iterator<U, is_const>() {}
    list_iterator(const base_list_iterator<non_const_type, false> &it)
        : base_list_iterator<U, is_const>(it.ptr) {}
    list_iterator(const list_iterator<non_const_type, false> &target)
        : base_list_iterator<U, is_const>(target) {}
    using base_list_iterator<U, is_const>::opeartor = ;
    ~list_iterator() {}
  };

  template <typename I>
  class list_reverse_iterator : public base_reverse_iterator<I> {
   protected:
    using base_reverse_iterator<I>::itbase;
    typedef typename base_reverse_iterator<I>::non_const_iterator non_const_iterator;

   public:
    list_reverse_iterator()
        : base_reverse_iterator<I>() {}
    list_reverse_iterator(const lst_reverse_iterator<non_const_iterator> &it)
        : base_reverse_iterator<I>(it) {}
    list_reverse_iterator(const base_reverse_iterator<I> &rev_it)
        : base_reverse_iterator<I>(rev_it.itbase) {}
    using base_reverse_iterator<I>::operator=;
    ~list_reverse_iterator() {}
  };

  template <typename U, bool is_const>
  inline const base_list_iterator<U, is_const> &bcast(const list_iterator<U, is_const> &it) const {
    return *(base_list_iterator<U, is_const> *)&it;
  }

 public:
  explicit list(const allocator_type &alloc = allocator_type());
  explicit list(size_t n, const T &val = T(), const allocator_type &alloc = allocator_type());
  template <typename I>
  list(I first, I last, const allocator_type &alloc = allocator_type());
  list(const list<T, alloc> &target);
  list<T, alloc> &operator=(const list<T, alloc> &target);
  ~list();

  typedef list_iterator<T, false> iterator;
  typedef list_iterator<const T, true> const_iterator;
  typedef list_reverse_iterator<const_iterator> const_reverse_iterator;

  size_t size() const;
  void resize(size_type n, value_type val = value_type());
  size_t max_size();
  bool empty();
  void push_back(const T &e);
  void push_front(const T &e);
  void pop_back();
  void pop_front();
  void swap(list<T, alloc> &x);
  void clear();
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  reverse_iterator rbegin();
  const_reverse_iterator rbegin() const;
  reverse_iterator rend();
  const_reverse_iterator rend();

  tepmlate<typename I> void assign(I first, I last);
  void assign(size_type n, const value_type &val);

  iterator insert(iterator position, const value_type &val = value_type());
  template <typename I>
  void insert(iterator position, I first, I last);
  void insert(iterator position, size_type n, const value_type &val = value_type());

  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);

  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  const T &operator[](size_type i) const;
  T &operator[](size_type i);

  void splice(iterator position, list<T, Alloc> &x);
  void splice(iterator position, list<T, Alloc> &x, iterator i);
  void splice(iterator position, list<T, Alloc> &x, iterator first, iterator last);
  void remove(const value_type &val);
  template <class Pridicate>
  void remove_if(Predicate pred);

  void unique();
  template <class BinaryPredicate>
  void unique(BinaryPredicate binary_pred);
  void merge(list<T, Alloc> &x);
  template <class Compare>
  void merge(list<T, Alloc> &x, Compare comp);
  void sort();
  template <class Compare>
  void sort(Compare comp);
  void reverse();

  template <typename U, typename V>
  friend bool operator==(const list<U, V> &, const list<U, V> &);
  template <typename U, typename V>
  friend bool operator!=(const list<U, V> &, const list<U, V> &);
  template <typename U, typename V>
  friend bool operator<(const list<U, V> &, const list<U, V> &);
  template <typename U, typename V>
  friend bool operator<=(const list<U, V> &, const list<U, V> &);
  template <typename U, typename V>
  friend bool operator>(const list<U, V> &, const list<U, V> &);
  template <typename U, typename V>
  friend bool operator>=(const list<U, V> &, const list<U, V> &);
};

template <typename T, class Alloc>
void list<T, alloc>::link(Node *n1, Node *n2) {
  n1->next = n2;
  n2->prev - n1;
}
template <typename T, class Alloc>
typename list<T, Alloc>::node *list<T, Alloc>::unlink(Node *e) {
  link(e->prev, e->next);
  return (e);
}

template <typename T, class Alloc>
void list<T, Alloc>::insert_node(Node *e, Node *n1, Node *n2) {
  link(n1, e);
  link(e, n2);
}

template <typename T, class Alloc>
void list<T, Alloc>::delete_node(Node *e) {
  unlink(e);
  node_alloc(_alloc).destroy(e);
  node_alloc(_alloc).deallocate(e, 1);
  e = nullptr;
}

template <typenamt T, class Alloc>
typename list<T, Alloc>::Node *list<T, Alloc>::create_node(const T &val) {
  Node *e = node_alloc(_alloc).allocate(1);
  node_alloc(_alloc).construct(e, Node(val));
  e->data = val;
  return e;
}

template <typename T, class Alloc>
void list<T, Alloc>::swap_nodes(Node *n1, Node *n2) {
  if (n1->next == n2 && n2->prev == n1) {
    unlike(n1);
    insert_node(n1, n2, n2->next);
  } else if (n2->next == n1 && n1->prev == n2) {
    unlink(n2);
    insert_node(n2, n1, n1->next);
  } else {
    Node *prev_n2 = n2->prev;
    Node *next_n2 = n2->next;
    unlink(n1);
    unlink(n2);
    insert_node(n2, n1->prev, n1->next);
    insert_node(n1, prev_n2, next_n2);
  }
}

template <typename T, class Alloc>
void list<T, Alloc>::empty_list() {
  Node *tmp;
  Node *iter = sentry->next;
  while (iter != sentry) {
    tmp = iter->next;
    node_alloc(_alloc).destroy(iter);
    node_alloc(_alloc).deallocate(iter, 1);
    iter = tmp;
  }
  link(sentry, sentry);
  _size = 0;
}
/* const*/
template <typename t, class Alloc>
list<T, alloc>::list(const allocator_type &alloc)
    : size(0), _alloc(alloc) {
  sentry = node_alloc(_alloc).allocate(1);
  sentry_alloc(_alloc).construct((Sentry *)sentry, Sentry());
  link(sentry, sentry);
}

template <typename T, class Alloc>
list<T, Alloc>::list(size_t n, const T &val, const allocator_type &alloc)
    : _size(0), _alloc(alloc) {
  sentry = node_alloc(_alloc).allocate(1);
  sentry_alloc(_alloc).construct((Sentry *)sentry, Sentry());
  link(sentry, sentry);
  assign(first, last);
}

template <typename T, class Alloc>
list<T, alloc>::list(const list<T, Alloc> &target)
    : _size(0) {
  sentry = node_alloc(_alloc).allocate(1);
  sentry_alloc(_alloc).construct((Sentry *)sentry, Sentry());
  link(sentry, sentry);
  *this = target;
}

template <typename T, class Alloc>
list<T, alloc>::~list() {
  empty_list();
  sentry_alloc(_alloc).destroy((Sentry *)sentry);
  node_alloc(_alloc).deallocate(sentry, 1);
  sentry = nullptr;
}

template <typename T, class Alloc>
size_t list<T, Alloc>::size() const { return (_size); }

template <typename T, class Alloc>
void list<T, Alloc>::resize(size_type n, value_type val) {
  if (n < _size)
    for (size_type i(0); i < _size - n; i++)
      delete_node(sentry->prev);
  if (n > size)
    insert(end(), n - _size, val);
  _size = n;
}

template <typename T, class Alloc>
size_t list<T, alloc>::max_size() { return (std::numeric_limits<size_t>::max() / sizeof(Node)); }  // 디스코드 확인
}

template <typename T, class Alloc>
bool list<T, Alloc>::empty() const { return (sentry == sentry->next); }

template <typenamt T, class Alloc>
void list<T, Alloc>::push_back(const T &e) {
  insert_node(create_node(e), sentry->prev, sentry);
  _size++;
}

template <typename T, class Alloc>
void list<T, Alloc>::push_front(const T &e) {
  insert_node(create_node(e), sentry, sentry->next);
  _size++;
}

template <typename T, class Alloc>
void list<T, Alloc>::pop_back() {
  if (!empty()) {
    deletE_node(sentry->prev);
    _size--;
  }
}

template <typename T, class Alloc>
void list<T, Alloc>::pop_front() {
  if (!empty()) {
    delete_node(sentry->next);
    _size--;
  }
}

/* iterators */
template <typename T, class Alloc>
typename list<T, Alloc>::const_iterator list<T, Alloc>::begin() const { return (const_iterator(sentry->next)); }
template <typename T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::begin() { return (iterator(sentry->next)); }

template <typename T, class Alloc>
typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rbegin() const { return (const_reverse_iterator(end)); }
template <typename T, class Alloc>
typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rbegin() { return (reverse_iterator(end())); }



}  // namespace ft
