/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:28:47 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 04:12:29 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "BaseIterators.hpp"
#include "utils.hpp"

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
    vector_iterator(const vector_iterator<non_const_type, false> &target)
        : base_vector_iterator<U, is_const>(target) {}
    using base_vector_iterator<U, is_const>::operator=;
    ~vector_iterator() {}
  };

  template <typename I>
  class vector_reverse_iterator : public base_reverse_iterator<I> {
   protected:
    // clang-format off
   using base_reverse_iterator<I>::itbase;
   typedef typename base_reverse_iterator<I>::non_const_iterator non_const_iterator;
    // clang-format on
   public:
    vector_reverse_iterator()
        : base_reverse_iterator<I>() {}
    vector_reverse_iterator(const vector_reverse_iterator<non_const_iterator> &it)
        : base_reverse_iterator<I>(it) {}
    vector_reverse_iterator(const base_reverse_iterator<I> &rev_it)
        : base_reverse_iterator<I>(rev_it.itbase) {}
    using base_reverse_iterator<I>::operator=;
    ~vector_reverse_iterator() {}
  };

  template <typename U, bool is_const>
  inline const base_vector_iterator<U, is_const> &bcast(const vector_iterator<U, is_const> &it) const {
    return (*(base_vector_iterator<U, is_const> *)&it);
  }

 public:
  explicit vector(const allocator_type &alloc = allocator_type())
      : _size(0), _capacity(0), _array(NULL), _alloc(alloc){};

  explicit vector(size_type n, const T &val = value_type(), const allocator_type &alloc = allocator_type())
      : _size(n), _capacity(n), _alloc(alloc) {
    _array = _alloc.allocate(_size);
    for (size_t i(0); i < _size; i++)
      _alloc.construct(_array + i, val);
  };

  template <typename I>
  vector(I first, I last, const allocator_type &alloc = allocator_type())
      : _size(0), _capacity(0), _array(NULL), _alloc(alloc) {
    typedef typename ft::is_integer<I>::type Integral;
    m_initialize_dispatch(first, last, Integral());
  };
  vector(const vector<T, Alloc> &target) : _array(NULL) { *this = target; };

  vector<T, Alloc> &operator=(const vector<T, Alloc> &target);

  ~vector() {
    for (size_type i = 0; i < _size; ++i)
      _alloc.destroy(_array + i);
    _alloc.deallocate(_array, _size);
  };

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
  void reserve(size_type n);
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

  template <typename I>
  void assign(I first, I last);
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
  friend bool operator>=(const vector<U, V> &, const vector<U, V> &);

 protected:
  template <typename Integer>
  void m_insert_dispatch(iterator pos, Integer n, Integer val, TrueType) {
    fill_insert(pos, n, val);
  }

  template <typename InputIter>
  void m_insert_dispatch(iterator pos, InputIter first, InputIter last, FalseType) {
    for (; first != last; ++first) {
      pos = insert(pos, *first);
      ++pos;
    }
  };
  void fill_insert(iterator pos, size_t n, const value_type &x) {
    size_type ind(0);
    for (iterator b = begin(); b != pos; b++, ind++) {
    }
    for (size_type i(0); i < n; i++)
      push_back(x);
    pos = _array + ind;
    for (iterator b = --end(); b != pos + n - 1; b--) {
      _alloc.destroy(bcast(b).ptr);
      _alloc.construct(bcast(b).ptr, *(b - n));
    }
    for (iterator b = pos; b != pos + n; b++) {
      _alloc.destroy(bcast(b).ptr);
      _alloc.construct(bcast(b).ptr, x);
    }
  }
  template <typename Integer>
  void m_initialize_dispatch(Integer n, Integer val, TrueType) {
    _array = _alloc.allocate(n);
    _size = static_cast<size_t>(n);
    for (size_t i(0); i < static_cast<size_t>(n) ; i++)
      _alloc.construct(_array + i, val);
  }
  template <typename InputIter>
  void m_initialize_dispatch(InputIter first, InputIter last, FalseType) {
    assign(static_cast<InputIter>(first), static_cast<InputIter>(last));
  }

  template <typename Integer>
  void m_assign_dispatch(Integer n, Integer val, TrueType) {
    if (n < 0)
      throw std::bad_alloc();
    if (static_cast<size_t>(n) > _capacity)
      realloc(n);
    for (size_type i = 0; i < size(); ++i)
      _alloc.destroy(&at(i));
    _size = 0;
    for (size_type i(0); i < static_cast<size_t>(n); i++)
      push_back(val);
  }

  template <typename InputIter>
  void m_assign_dispatch(InputIter first, InputIter last, FalseType) {
    size_type n(0);
    for (InputIter it = first; it != last; it++, n++) {
    }
    if (n > _capacity)
      realloc(n);
    for (size_type i = 0; i < size(); ++i)
      _alloc.destroy(&at(i));
    _size = 0;
    for (InputIter it = first; it != last; it++)
      push_back(*it);
  }
};

template <typename T, class Alloc>
void vector<T, Alloc>::realloc(size_t nsize) {
  _capacity = nsize;
  T *copy = _alloc.allocate(_capacity);
  for (size_t i(0); i < _size; i++)
    _alloc.construct(copy + i, _array[i]);
  if (_array) {
    for (size_type i = 0; i < _size; ++i)
      _alloc.destroy(_array + i);
    _alloc.deallocate(_array, _size);
  }
  _array = copy;
}

template <typename T, class Alloc>
size_t vector<T, Alloc>::size() const { return (_size); }

template <typename T, class Alloc>
void vector<T, Alloc>::resize(size_type n, value_type val) {
  if (n > max_size())
    return;
  if (n <= (size_type)_size)
    _size = n;
  else {
    size_type current_size = _size;
    for (size_type i(0); i < n - current_size; ++i)
      push_back(val);
  }
}

template <typename T, class Alloc>
size_t vector<T, Alloc>::max_size() const {
  return (std::numeric_limits<size_type>::max() / sizeof(value_type));
}

template <typename T, class Alloc>
size_t vector<T, Alloc>::capacity() const {
  return (_capacity);
}

template <typename T, class Alloc>
bool vector<T, Alloc>::empty() const {
  return (!_size);
}

template <typename T, class Alloc>
void vector<T, Alloc>::reserve(size_type n) {
  if (n > max_size())
    throw std::length_error("Error: reserve() parameter greater than container's max_size()");
  else if (n > _capacity)
    realloc(n);
}

template <typename T, class Alloc>
void vector<T, Alloc>::push_back(const T &e) {
  if (_size == _capacity)
    realloc(_capacity ? _capacity * 2 : 1);
  _alloc.construct(_array + _size, e);
  _size++;
}

template <typename T, class Alloc>
void vector<T, Alloc>::pop_back() {
  if (_size) {
    _alloc.destroy(_array + _size - 1);
    --_size;
  }
}

template <typename T, class Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::begin() const { return (const_iterator(_array)); }

template <typename T, class Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::begin() { return (iterator(_array)); }

template <typename T, class Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::end() const { return (const_iterator(_array + _size)); }

template <typename T, class Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::end() { return (iterator(_array + _size)); }

template <typename T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator
vector<T, Alloc>::rbegin() const { return const_reverse_iterator(end()); }

template <typename T, class Alloc>
typename vector<T, Alloc>::reverse_iterator
vector<T, Alloc>::rbegin() { return reverse_iterator(end()); }

template <typename T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator
vector<T, Alloc>::rend() const { return const_reverse_iterator(begin()); }

template <typename T, class Alloc>
typename vector<T, Alloc>::reverse_iterator
vector<T, Alloc>::rend() { return reverse_iterator(begin()); }

template <typename T, class Alloc>
T &vector<T, Alloc>::at(size_type i) {
  if (i < 0 || i >= size())
    throw std::out_of_range(std::string("Error: out of bounds access"));
  return (_array[i]);
}

template <typename T, class Alloc>
const T &vector<T, Alloc>::at(size_type i) const {
  if (i < 0 || i >= size())
    throw std::out_of_range(std::string("Error: out of bounds access"));
  return (_array[i]);
}

template <typename T, class Alloc>
T &vector<T, Alloc>::front() {
  if (!_size)
    throw std::out_of_range(std::string("Error: out of bounds access"));
  return (_array[0]);
}

template <typename T, class Alloc>
const T &vector<T, Alloc>::front() const {
  if (!_size)
    throw std::out_of_range(std::string("Error: out of bounds access"));
  return (_array[0]);
}

template <typename T, class Alloc>
T &vector<T, Alloc>::back() {
  if (!_size)
    throw std::out_of_range(std::string("Error: out of bounds access"));
  return (_array[_size - 1]);
}

template <typename T, class Alloc>
const T &vector<T, Alloc>::back() const {
  if (!_size)
    throw std::out_of_range(std::string("Error: out of bounds access"));
  return (_array[_size - 1]);
}

template <typename T, class Alloc>
void vector<T, Alloc>::assign(size_type n, const value_type &val) {
  if (n < 0)
    throw std::bad_alloc();
  if (n > _capacity)
    realloc(n);
  for (size_type i = 0; i < size(); ++i)
    _alloc.destroy(&at(i));
  _size = 0;
  for (size_type i(0); i < n; i++)
    push_back(val);
}

template <typename T, class Alloc>
template <typename I>
void vector<T, Alloc>::assign(I first, I last) {
  typedef typename ft::is_integer<I>::type Integral;
  m_assign_dispatch(first, last, Integral());
}

template <typename T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const value_type &val) {
  size_type ind(0);
  for (iterator b = begin(); b != position; b++, ind++) {
  }
  if (_size == _capacity) {
    realloc(_capacity ? _capacity * 2 : 1);
    position = _array + ind;
  }
  for (iterator b = this->end(); b != position; b--) {
    _alloc.destroy(bcast(b).ptr);
    _alloc.construct(bcast(b).ptr, *(b - 1));
  }
  *position = val;
  _size++;
  return (position);
}

template <typename T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const value_type &val) {
  size_type ind(0);
  for (iterator b = begin(); b != position; b++, ind++) {
  }
  for (size_type i(0); i < n; i++)
    push_back(val);
  position = _array + ind;
  for (iterator b = --end(); b != position + n - 1; b--) {
    _alloc.destroy(bcast(b).ptr);
    _alloc.construct(bcast(b).ptr, *(b - n));
  }
  for (iterator b = position; b != position + n; b++) {
    _alloc.destroy(bcast(b).ptr);
    _alloc.construct(bcast(b).ptr, val);
  }
}

template <typename T, class Alloc>
template <typename I>
void vector<T, Alloc>::insert(vector<T, Alloc>::iterator position, I first, I last) {
  typedef typename ft::is_integer<I>::type Integral;
  m_insert_dispatch(position, first, last, Integral());
}

template <typename T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position) {
  if (position == end()) {
    pop_back();
    return end();
  }
  for (iterator it = position; it != this->end() - 1; ++it) {
    _alloc.destroy(bcast(it).ptr);
    _alloc.construct(bcast(it).ptr, *(it + 1));
  }
  _alloc.destroy(_array + _size - 1);
  _size--;
  return (position);
}

template <typename T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last) {
  long n = std::distance(first, last);
  if (n < 0)
    throw std::invalid_argument("Error: invalid iterator(s)");
  if (last == end()) {
    for (long i = 0; i < n; ++i)
      pop_back();
    return end();
  }
  for (iterator it = last; it != end(); ++it) {
    _alloc.destroy(&(*(it - n)));
    _alloc.construct(&(*(it - n)), *it);
  }
  for (long i = 0; i < n; ++i)
    pop_back();
  return (first);
}

template <typename T, class Alloc>
void vector<T, Alloc>::swap(vector<T, Alloc> &x) {
  std::swap(this->_capacity, x._capacity);
  std::swap(this->_size, x._size);
  std::swap(this->_array, x._array);
}

template <typename T, class Alloc>
void vector<T, Alloc>::clear() {
  for (size_type i = 0; i < _size; ++i)
    _alloc.destroy(_array + i);
  _size = 0;
}

template <typename T, class Alloc>
const T &vector<T, Alloc>::operator[](size_type i) const { return (_array[i]); }
template <typename T, class Alloc>
T &vector<T, Alloc>::operator[](size_type i) { return (_array[i]); }

template <typename T, class Alloc>
vector<T, Alloc> &vector<T, Alloc>::operator=(const vector<T, Alloc> &target) {
  if (_array) {
    for (size_type i = 0; i < _size; ++i)
      _alloc.destroy(_array + i);
    _alloc.deallocate(_array, _size);
  }
  _size = target.size();
  _capacity = target._capacity;
  _array = _alloc.allocate(_capacity);
  for (size_t i(0); i < _size; i++)
    _alloc.construct(_array + i, target[i]);
  return (*this);
}

template <typename U, class V>
bool operator==(const vector<U, V> &lhs, const vector<U, V> &rhs) {
  if (lhs.size() != rhs.size())
    return false;
  for (size_t i(0); i < lhs.size(); i++)
    if (lhs[i] != rhs[i])
      return false;
  return true;
}

template <typename U, class V>
bool operator!=(const vector<U, V> &lhs, const vector<U, V> &rhs) {
  return (!(lhs == rhs));
}

template <typename U, class V>
bool operator<(const vector<U, V> &lhs, const vector<U, V> &rhs) {
  return std::lexicographical_compare<
      base_vector_iterator<const U, true>,
      base_vector_iterator<const U, true> >(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  return true;
}

template <typename U, class V>
bool operator<=(const vector<U, V> &lhs, const vector<U, V> &rhs) {
  return ((lhs == rhs) || (lhs < rhs));
}

template <typename U, class V>
bool operator>(const vector<U, V> &lhs, const vector<U, V> &rhs) {
  return (!(lhs <= rhs));
}

template <typename U, class V>
bool operator>=(const vector<U, V> &lhs, const vector<U, V> &rhs) {
  return (!(lhs < rhs));
}

template <typename T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
  vector<T, Alloc> tmp = x;
  x = y;
  y = tmp;
}
}  // namespace ft

#endif
