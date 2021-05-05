/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:28:47 by sucho             #+#    #+#             */
/*   Updated: 2021/05/05 17:54:30 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BaseIterators.hpp"

namespace ft {

template <typename T, class Alloc>
class vector {
 public:
  // clang-format off
  typedef T               value_type;
  typedef const T         const_value_type;
  typedef Alloc           allocator_type;
  typedef T               &reference;
  typedef const T         &const_reference;
  typedef T               *pointer;
  typedef const T         *const_pointer;
  typedef size_t          size_type;
  typedef std::ptrdiff_t  difference_type;
  // clang-format on

 protected:
  size_type _size;
  size_type _capacity;
  T *_array;
  allocator_type _alloc;
  void realloc(size_type nsize);

  template <typename U, bool is_const>
  class vector_iterator : public base_vector_iterator<U, is_const> {
   protected:
    using base_vector_iterator<U, is_const>::ptr;
    using base_vector_iterator<U, is_const>::get;

   public:
    // clang-format off
   typedef U                                                value_type;
   typedef typename choose<is_const, const U &, U &>::type  reference;
   typedef typename choose<is_const, const U *, U *>::type  pointer;
   typedef std::ptrdiff_t                                   difference_type;
   typedef std::random_access_iterator_tag                  iterator_category;
   typedef typename remove_const<U>::type                   non_const_type;
   typedef vector_iterator<non_const_type, false>                non_const_iterator;
    // clang-format on

    vector_iterator()
        : base_vector_iterator<U, is_const>(){};
    vector_iterator(const base_vector_iterator<non_const_type, false> &it)
        : base_vector_iterator<U, is_const>(it.ptr) {}
    vector_iterator(const v_iterator<non_const_type, false> &target)
        : base_vector_iterator<V, is_const>(target) {}
    using base_vector_iterator<U, is_const>::operator=;
    ~vector_iterator() {}
  };

  template <typename I>
  class vector_reverse_iterator : public base_reverse_iterator<I> {
   protected:
    // clang-format off
   using base_reverse_iterator<I>::itbase;
   typedef typename base_reverse_iterator<I>::non_const_iterator no_const_iterator;
    // clang-format on
   public:
    vector_reverse_iterator()
        : base_reverse_iterator<I> {}
    vector_reverse_iterator(const vector_reverse_iterator<non_const_iterator> &it)
        : base_reverse_iterator<I>(it) {}
    vector_reverer_iterator(const base_reverse_iterator<I> &rev_it)
        : base_reverse_iterator<I>(rev_it.itbase) {}
    using base_reverse_iterator<I>::operator=;
    ~vector_reverse_iterator();
  };

  template <typename U, bool is_const>
  inline const base_vector_iterator<U, is_const> &bcast(const vector_iterator<U, is_const> &it) const {
    return (*(base_vector_iterator<U, is_const> *)&it);
  }

 public:
  explicit vector(const allocator_type &alloc = allocator_type());
  explicit vector(size_t n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
  template <typename I>
  vector(I first, I last, const allocator_type &alloc = allocator_type());
  vector(const vector<T, Alloc> &target);
  vector<T, Alloc> &operator=(const vector<T, Alloc> &target);
  ~vector()

      // clang-format off
  typedef vector_iterator<T, false>                iterator;
  typedef vector_iterator<const T, true>           const_iterator;
  typedef vector_reverse_iterator<iterator>        reverse_iterator;
  typedef vector_reverse_iterator<const_iterator>  const_reverse_iterator;
  // clang-format on

  size_type size() const;
  void resize(size_type n, value_type val = value_type());
  size_type max_size() const;
  size_type capacity() const;
  bool empty() const;
  void reverse(size_type n);
  void push_back(const T &e);
  void pop_back();
  void swap(vector<T, Alloc> &x);
  void clear();

  const_iterator begin() const;
  iterator begin();
  const_iterator end() const;
  iterator end();
  const_reverse_iterator rbegin() const;
  reverse_iterator rbegin();
  const_reverse_iterator rend() const;
  reverse_iterator rend();

  template << typename I > void assign(I first, I last);
  void assign(size_type n, const value_type &val);

  iterator insert(iterator position, const value_type &val = value_type());

  template <typename I>
  void insert(iterator position, I first, I last);
  void insert(iterator position, size_type n, const value_type &val = value_type());

  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);

  reference operator[](size_type i);
  const_reference operator[](size_type i) const;
  reference at(size_type n);
  const_reference at(size_type n) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;

  template <typename U, class V>
  friend bool operator==(const vector<U, V> &, const vector<U, V> &);
  template <typename U, class V>
  friend bool operator!=(const vector<U, V> &, const vector<U, V> &);
  template <typename U, class V>
  friend bool operator<(const vector<U, V> &, const vector<U, V> &);
  template <typename U, class V>
  friend bool operator<=(const vector<U, V> &, const vector<U, V> &);
  template <typename U, class V>
  friend bool operator>(const vector<U, V> &, const vector<U, V> &);
  template <typename U, class V>
  friend bool operator>=(const vector<U, V> &, const vector<U, V> &)
};

template <typename T, class Alloc>
vector<T, Alloc>::vector(const allocator_type &alloc)
    : _size(0), _capacity(0), _array(NULL), _alloc(alloc) {}

template <typename T, class Alloc>
vector<T, Alloc>::vector(size_t n, const T &val, const allocator_type &alloc)
  : _size(n), _capacity(n), _alloc(alloc)
  {
    _array = _alloc.allocate(_size);
    for (size_t i(0); i < _size = i++)
      _alloc.construct(_array + i, val);
  }
}  // namespace ft
