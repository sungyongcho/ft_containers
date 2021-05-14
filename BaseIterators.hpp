/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseIterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 00:12:52 by sucho             #+#    #+#             */
/*   Updated: 2021/05/14 17:04:41 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#pragma once

#include "utils.hpp"

namespace ft {

template <class T, class Cmp = std::less<T>, class Alloc = std::allocator<T> >
class set;
template <class T, class Cmp = std::less<T>, class Alloc = std::allocator<T> >
class multiset;
template <class Key, class T, class Cmp = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
class map;
template <class Key, class T, class Cmp = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
class multimap;
template <typename T, class Alloc = std::allocator<T> >
class list;
template <typename T, class Alloc = std::allocator<T> >
class vector;
template <typename T, class Alloc = std::allocator<T> >
class deque;
template <typename T, class C = ft::deque<T> >
class stack;
template <typename T, class C = ft::deque<T> >
class queue;

template <typename T>
struct DoublyLinkedList {
  DoublyLinkedList *next;
  DoublyLinkedList *prev;
  T element;
  DoublyLinkedList(T val) : element(val) {}
};

template <typename T>
struct list_sentry {
  DoublyLinkedList<T> *next;
  DoublyLinkedList<T> *prev;
};

template <typename T, bool is_const>
class base_list_iterator {
 public:
  typedef typename remove_const<T>::type non_const_type;
  typedef base_list_iterator<non_const_type, false> non_const_iterator;
  typedef typename choose<is_const, const DoublyLinkedList<T> *, DoublyLinkedList<T> *>::type node_pointer;
  typedef T value_type;
  typedef typename choose<is_const, const T &, T &>::type reference;
  typedef typename choose<is_const, const T *, T *>::type pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;

  DoublyLinkedList<non_const_type> *ptr;
  DoublyLinkedList<non_const_type> *get() { return (ptr); }

  base_list_iterator() : ptr(NULL) {}
  base_list_iterator(node_pointer p) : ptr(p) {}
  base_list_iterator(const non_const_iterator &target) : ptr(target.ptr) {}

  virtual ~base_list_iterator() {}

  base_list_iterator &
  operator=(const non_const_iterator &target) {
    ptr = target.ptr;
    return (*this);
  }

  reference operator*() {
    if (ptr)
      return (ptr->element);
    throw std::out_of_range(std::string("Error: dereferencing null pointer"));
  }

  base_list_iterator &operator++() {
    if (ptr)
      ptr = ptr->next;
    return (*this);
  }

  base_list_iterator operator++(int) {  // 왜 굳이 int 가 들어가야하는지??? -> 후위연산자임을 구분지어주게 하기 위해서
    base_list_iterator tmp(ptr);
    operator++();
    return (tmp);
  }

  base_list_iterator &operator--() {
    if (ptr)
      ptr = ptr->prev;
    return (*this);
  }

  base_list_iterator operator--(int) {
    base_list_iterator tmp(ptr);
    operator--();
    return (tmp);
  }

  template <typename T_a, typename T_b, bool A, bool B>
  friend bool operator==(const base_list_iterator<T_a, A> &a, const base_list_iterator<T_b, B> &b) {  // 왜 friend를 쓰는가??? -> 두개 일때
    return (a.ptr == b.ptr);
  }

  template <typename T_a, typename T_b, bool A, bool B>
  friend bool operator!=(const base_list_iterator<T_a, A> &a, const base_list_iterator<T_b, B> &b) {
    return (a.ptr != b.ptr);
  }

  bool operator==(node_pointer b) { return (ptr == b); }
  bool operator!=(node_pointer b) { return (ptr != b); }
};

template <class U>
class base_reverse_iterator {
 public:
  typedef U iterator_type;
  typedef typename iterator_type::iterator_category iterator_category;
  typedef typename iterator_type::value_type value_type;
  typedef typename iterator_type::difference_type difference_type;
  typedef typename iterator_type::pointer pointer;
  typedef typename iterator_type::reference reference;
  typedef typename iterator_type::non_const_type non_const_type;
  typedef typename iterator_type::non_const_iterator non_const_iterator;

  iterator_type itbase;

  base_reverse_iterator() {}
  base_reverse_iterator(const iterator_type &it)
      : itbase(it) {}
  base_reverse_iterator(const base_reverse_iterator<non_const_iterator> &rev_it)
      : itbase(rev_it.itbase) {}
  virtual ~base_reverse_iterator() {}
  base_reverse_iterator &operator=(const base_reverse_iterator<non_const_iterator> &target) {
    itbase = target.itbase;
    return *this;
  }

  reference operator*() {
    return (*ft::fwd(itbase, -1));
  }

  pointer operator->() {
    return ft::fwd(itbase, -1).operator->();
  }

  base_reverse_iterator &operator++() {
    --itbase;
    return *this;
  }

  base_reverse_iterator operator++(int) {
    base_reverse_iterator tmp(*this);
    --itbase;
    return (tmp);
  }

  base_reverse_iterator &operator--() {
    ++itbase;
    return *this;
  }

  base_reverse_iterator operator--(int) {
    base_reverse_iterator tmp(*this);
    ++itbase;
    return (tmp);
  }

  base_reverse_iterator operator+(difference_type n) {
    base_reverse_iterator tmp(*this);
    while (n--) ++tmp;
    return tmp;
  }

  base_reverse_iterator operator-(difference_type n) {
    base_reverse_iterator tmp(*this);
    while (n--) --tmp;
    return tmp;
  }

  template <typename A>
  long operator-(const base_reverse_iterator<A> &other) {
    return -(itbase - other.itbase);
  }

  iterator_type base() {
    return itbase;
  }

  reference operator[](difference_type n) {
    return itbase[-n - 1];
  }

  template <typename A, typename B>
  friend bool operator==(const base_reverse_iterator<A> &a,
                         const base_reverse_iterator<B> &b) {
    return a.itbase == b.itbase;
  }

  template <typename A, typename B>
  friend bool operator!=(const base_reverse_iterator<A> &a,
                         const base_reverse_iterator<B> &b) {
    return a.itbase != b.itbase;
  }

  template <typename A, typename B>
  friend bool operator<(const base_reverse_iterator<A> &a,
                        const base_reverse_iterator<B> &b) {
    return a.itbase >= b.itbase;
  }

  template <typename A, typename B>
  friend bool operator<=(const base_reverse_iterator<A> &a,
                         const base_reverse_iterator<B> &b) {
    return a.itbase > b.itbase;
  }

  template <typename A, typename B>
  friend bool operator>(const base_reverse_iterator<A> &a,
                        const base_reverse_iterator<B> &b) {
    return a.itbase <= b.itbase;
  }

  template <typename A, typename B>
  friend bool operator>=(const base_reverse_iterator<A> &a,
                         const base_reverse_iterator<B> &b) {
    return a.itbase < b.itbase;
  }
};

template <typename T, bool is_const>
class base_vector_iterator {
 public:
  typedef T value_type;
  typedef typename choose<is_const, const T &, T &>::type reference;
  typedef typename choose<is_const, const T *, T *>::type pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::random_access_iterator_tag iterator_category;
  typedef typename remove_const<T>::type non_const_type;
  typedef typename add_const<T>::type const_type;
  typedef base_vector_iterator<non_const_type, false> non_const_iterator;
  typedef base_vector_iterator<const_type, false> const_iterator;

  T *ptr;
  T &get() { return (ptr); }

  base_vector_iterator() : ptr(NULL) {}
  base_vector_iterator(pointer p) : ptr(p) {}
  base_vector_iterator(const non_const_iterator &target) : ptr(target.ptr) {}
  virtual ~base_vector_iterator() {}

  inline base_vector_iterator &operator=(const non_const_iterator &target) {
    this->ptr = target.ptr;
    return (*this);
  }

  inline base_vector_iterator &operator++() {
    ptr++;
    return (*this);
  }

  inline base_vector_iterator operator++(int) {
    base_vector_iterator tmp(ptr);
    operator++();
    return (tmp);
  }

  inline base_vector_iterator &operator--() {
    ptr--;
    return (*this);
  }

  inline base_vector_iterator operator--(int) {
    base_vector_iterator tmp(ptr);
    operator--();
    return (tmp);
  }

  inline reference operator*() {
    return (*ptr);
  }

  inline reference operator[](difference_type n) {
    return (ptr[n]);
  }

  inline base_vector_iterator operator+(difference_type n) {
    return base_vector_iterator(ptr + n);
  }

  inline base_vector_iterator &operator+=(difference_type n) {
    ptr += n;
    return (*this);
  }

  inline base_vector_iterator operator-(difference_type n) {
    return base_vector_iterator(ptr - n);
  }

  inline long operator-(const non_const_iterator &other) {
    return (((long)ptr - (long)other.ptr) / (long)sizeof(value_type));
  }

  inline long operator-(const const_iterator &other) {
    return ((long)ptr - (long)other.ptr / (long)sizeof(value_type));
  }

  inline base_vector_iterator &operator-=(difference_type n) {
    ptr -= n;
    return (*this);
  }

  template <typename T_a, typename T_b, bool A, bool B>
  friend inline bool operator==(base_vector_iterator<T_a, A> a,
                                base_vector_iterator<T_b, B> b) {
    return (a.ptr == b.ptr);
  }

  template <typename T_a, typename T_b, bool A, bool B>
  friend inline bool operator!=(base_vector_iterator<T_a, A> a,
                                base_vector_iterator<T_b, B> b) {
    return (a.ptr != b.ptr);
  }

  template <typename T_a, typename T_b, bool A, bool B>
  friend inline bool operator<(base_vector_iterator<T_a, A> a,
                               base_vector_iterator<T_b, B> b) {
    return (a.ptr < b.ptr);
  }

  template <typename T_a, typename T_b, bool A, bool B>
  friend inline bool operator<=(base_vector_iterator<T_a, A> a,
                                base_vector_iterator<T_b, B> b) {
    return (a.ptr <= b.ptr);
  }

  template <typename T_a, typename T_b, bool A, bool B>
  friend inline bool operator>(base_vector_iterator<T_a, A> a,
                               base_vector_iterator<T_b, B> b) {
    return (a.ptr > b.ptr);
  }

  template <typename T_a, typename T_b, bool A, bool B>
  friend inline bool operator>=(base_vector_iterator<T_a, A> a,
                                base_vector_iterator<T_b, B> b) {
    return (a.ptr != b.ptr);
  }
};

template <typename T>
struct map_node {
  T pair;
  map_node *left;
  map_node *right;
  map_node *parent;
  ssize_t height;
  map_node(T val)
      : pair(val), left(NULL), right(NULL), parent(NULL), height(-1) {}
  ~map_node() {}
};

template <typename T, bool is_const>
class base_avl_iterator {
 public:
  typedef typename remove_const<T>::type non_const_type;
  typedef base_avl_iterator<non_const_type, false> non_const_iterator;
  typedef typename choose<is_const, const map_node<T> *, map_node<T> *>::type node_pointer;

  typedef typename choose<is_const, const T &, T &>::type reference;
  typedef typename choose<is_const, const T *, T *>::type pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;

  map_node<non_const_type> *ptr;
  map_node<non_const_type> *const *tree_ref;

  base_avl_iterator() : ptr(nullptr), tree_ref(nullptr) {}
  base_avl_iterator(map_node<non_const_type> *p, map_node<non_const_type> *const *tree_ref)
      : ptr(p), tree_ref(tree_ref) {}
  base_avl_iterator(const non_const_iterator &target)
      : ptr(target.ptr), tree_ref(target.tree_ref) {}
  virtual ~base_avl_iterator() {}

  base_avl_iterator &operator=(const non_const_iterator &target) {
    ptr = target.ptr;
    tree_ref = target.tree_ref;
    return *this;
  }

  map_node<non_const_type> *get() { return (ptr); }

  base_avl_iterator get_next(map_node<non_const_type> *root) {
    if (root->right) {
      root = root->right;
      while (root->left)
        root = root->left;
    } else {
      map_node<non_const_type> *old;
      do {
        old = root;
        root = root->parent;
        if (!root)
          return base_avl_iterator(nullptr, tree_ref);
      } while (root->right == old);
    }
    return base_avl_iterator(root, tree_ref);
  }

  base_avl_iterator get_prev(map_node<non_const_type> *root) {
    if (root->left) {
      root = root->left;
      while (root->right)
        root = root->right;
    } else {
      map_node<non_const_type> *old;
      do {
        old = root;
        root = root->parent;
        if (!root)
          return base_avl_iterator(nullptr, tree_ref);
      } while (root->left == old);
    }
    return base_avl_iterator(root, tree_ref);
  }

  bool operator==(map_node<non_const_type> *b) { return (ptr == b); }
  bool operator!=(map_node<non_const_type> *b) { return (ptr != b); }

  pointer operator->() {
    if (ptr)
      return &ptr->pair;
    throw std::out_of_range(std::string("Error: dereferencing null pointer"));
  }

  reference operator*() {
    if (ptr)
      return ptr->pair;
    throw std::out_of_range(std::string("Error: dereferencing null pointer"));
  }

  base_avl_iterator &operator++() {
    if (!ptr) {
      ptr = *tree_ref;
      while (ptr && ptr->left)
        ptr = ptr->left;
    } else
      *this = get_next(ptr);
    return (*this);
  }

  base_avl_iterator operator++(int) {
    base_avl_iterator tmp(ptr, tree_ref);
    operator++();
    return (tmp);
  }

  base_avl_iterator &operator--() {
    if (!ptr) {
      ptr = *tree_ref;
      while (ptr && ptr->right)
        ptr = ptr->right;
    } else
      *this = get_prev(ptr);
    return (*this);
  }

  base_avl_iterator operator--(int) {
    base_avl_iterator tmp(ptr, tree_ref);
    operator--();
    return (tmp);
  }

  template <typename Ta, typename Tb, bool A, bool B>
  friend bool operator==(const base_avl_iterator<Ta, A> &a,
                         const base_avl_iterator<Tb, B> &b) {
    return (a.ptr == b.ptr);
  }

  template <typename Ta, typename Tb, bool A, bool B>
  friend bool operator!=(const base_avl_iterator<Ta, A> &a,
                         const base_avl_iterator<Tb, B> &b) {
    return (a.ptr != b.ptr);
  }
};

}  // namespace ft
