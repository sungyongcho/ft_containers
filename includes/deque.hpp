/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:23:01 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 07:20:52 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "BaseIterators.hpp"
#include "vector.hpp"

namespace ft {

template <typename T, class Alloc>
class deque {
 public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef size_t size_type;
  typedef std::ptrdiff_t difference_type;

 protected:
  allocator_type _alloc;
  deque_node<T> dq;

  void expand(size_type nb_chunks = 1);
  void set_empty();
  void dump_chunks();

  template <typename U, bool is_const>
  class dq_iterator : public base_dq_iterator<U, is_const> {
   protected:
    using base_dq_iterator<U, is_const>::head;
    using base_dq_iterator<U, is_const>::dq;

   public:
    typedef U value_type;
    typedef typename choose<is_const, const U &, U &>::type reference;
    typedef typename choose<is_const, const U *, U *>::type pointer;
    typedef typename remove_const<U>::type non_const_type;
    typedef dq_iterator<non_const_type, false> non_const_iterator;

    dq_iterator() : base_dq_iterator<U, is_const>() {}
    dq_iterator(ssize_t head, const deque_node<T> *dq)
        : base_dq_iterator<U, is_const>(head, dq) {}
    dq_iterator(const base_dq_iterator<non_const_type, false> &it)
        : base_dq_iterator<U, is_const>(it.head, it.dq) {}
    dq_iterator(const non_const_iterator &target)
        : base_dq_iterator<U, is_const>(target) {}
    using base_dq_iterator<U, is_const>::operator=;
    ~dq_iterator() {}
  };

  template <typename I>
  class dq_reverse_iterator : public base_reverse_iterator<I> {
   private:
    using base_reverse_iterator<I>::itbase;
    typedef typename base_reverse_iterator<I>::non_const_iterator non_const_iterator;

   public:
    dq_reverse_iterator()
        : base_reverse_iterator<I>() {}
    dq_reverse_iterator(const dq_reverse_iterator<non_const_iterator> &it)
        : base_reverse_iterator<I>(it) {}
    dq_reverse_iterator(const base_reverse_iterator<I> &rev_it)
        : base_reverse_iterator<I>(rev_it.itbase) {}
    using base_reverse_iterator<I>::operator=;
    ~dq_reverse_iterator() {}
  };

  template <typename U, bool is_const>
  inline const base_dq_iterator<U, is_const> &bcast(const dq_iterator<U, is_const> &it) const {
    return *(base_dq_iterator<U, is_const> *)&it;
  }

 public:
  typedef dq_iterator<value_type, false> iterator;
  typedef dq_iterator<const value_type, true> const_iterator;
  typedef dq_reverse_iterator<iterator> reverse_iterator;
  typedef dq_reverse_iterator<const_iterator> const_reverse_iterator;

  explicit deque(const allocator_type &alloc = allocator_type());
  explicit deque(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
  template <typename I>
  deque(I first, I last, const allocator_type &alloc = allocator_type());
  deque(const deque<T, Alloc> &target);
  deque<T, Alloc> &operator=(const deque<T, Alloc> &target);
  ~deque();

  size_type size() const;
  void resize(size_type n, value_type val = value_type());
  size_type max_size() const;
  size_type capacity() const;
  bool empty() const;
  void push_back(const value_type &e);
  void push_front(const value_type &e);
  void pop_back();
  void pop_front();
  void swap(deque<T, Alloc> &x);
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
  friend bool operator==(const deque<U, V> &, const deque<U, V> &);
  template <typename U, class V>
  friend bool operator!=(const deque<U, V> &, const deque<U, V> &);
  template <typename U, class V>
  friend bool operator<(const deque<U, V> &, const deque<U, V> &);
  template <typename U, class V>
  friend bool operator<=(const deque<U, V> &, const deque<U, V> &);
  template <typename U, class V>
  friend bool operator>(const deque<U, V> &, const deque<U, V> &);
  template <typename U, class V>
  friend bool operator>=(const deque<U, V> &, const deque<U, V> &);

 protected:
  template <typename Integer>
  void m_initialize_dispatch(Integer n, Integer val, TrueType) {
    dq._chunksize = std::max(16 * sizeof(value_type), 4096ul) / sizeof(value_type);
    pointer array = _alloc.allocate(dq._chunksize);
    dq._pmap.push_back(array);
    dq._capacity = dq._chunksize;
    assign(n, val);
  }
  template <typename InputIter>
  void m_initialize_dispatch(InputIter first, InputIter last, FalseType) {
    dq._chunksize = std::max(16 * sizeof(value_type), 4096ul) / sizeof(value_type);
    pointer array = _alloc.allocate(dq._chunksize);
    dq._pmap.push_back(array);
    dq._capacity = dq._chunksize;
    assign(first, last);
  }

  template <typename Integer>
  void m_assign_dispatch(Integer n, Integer val, TrueType) {
    if (static_cast<size_type>(n) < 0 || (size_type)n > max_size())
      throw std::bad_alloc();
    if (static_cast<size_type>(n) > dq._capacity)
      expand(substract_size_t(static_cast<size_type>(n), dq._capacity) / sizeof(value_type) + 1);
    for (size_type i = 0; i < size(); ++i)
      _alloc.destroy(&this->at(i));
    dq._size = 0;
    set_empty();
    for (size_type i = 0; i < static_cast<size_t>(n); ++i)
      push_back(val);
  }

  template <typename InputIter>
  void m_assign_dispatch(InputIter first, InputIter last, FalseType) {
    long n(0);
    n = std::distance(first, last);
    if ((size_type)n < 0 || (size_type)n > max_size())
      throw std::bad_alloc();
    long cap = dq._capacity;
    if (n > cap)
      expand((n - cap) / sizeof(value_type) + 1);
    for (size_type i = 0; i < size(); ++i)
      _alloc.destroy(&this->at(i));
    dq._size = 0;
    set_empty();
    for (InputIter it = first; it != last; it++)
      push_back(*it);
  }
};

template <typename T, class Alloc>
deque<T, Alloc>::deque(const allocator_type &alloc)
    : _alloc(alloc) {
  dq._chunksize = std::max(16 * sizeof(value_type), 4096ul) / sizeof(value_type);
  pointer array = _alloc.allocate(dq._chunksize);
  dq._pmap.push_back(array);
  dq._capacity = dq._chunksize;
}

template <typename T, class Alloc>
deque<T, Alloc>::deque(size_type n, const T &val, const allocator_type &alloc)
    : _alloc(alloc) {
  dq._chunksize = std::max(16 * sizeof(value_type), 4096ul) / sizeof(value_type);
  pointer array = _alloc.allocate(dq._chunksize);
  dq._pmap.push_back(array);
  dq._capacity = dq._chunksize;
  assign(n, val);
}

template <typename T, class Alloc>
template <typename I>
deque<T, Alloc>::deque(I first, I last, const allocator_type &alloc)
    : _alloc(alloc) {
  typedef typename ft::is_integer<I>::type Integral;
  m_initialize_dispatch(first, last, Integral());
}

template <typename T, class Alloc>
deque<T, Alloc>::deque(const deque<T, Alloc> &target)
    : _alloc(target._alloc) {
  dq._chunksize = std::max(16 * sizeof(value_type), 4096ul) / sizeof(value_type);
  pointer array = _alloc.allocate(dq._chunksize);
  dq._pmap.push_back(array);
  dq._capacity = dq._chunksize;
  assign(target.begin(), target.end());
}

template <typename T, class Alloc>
deque<T, Alloc>::~deque() {
  for (iterator it = begin(); it != end(); ++it)
    _alloc.destroy(&(*it));
  for (typename ft::vector<pointer>::iterator it = dq._pmap.begin(); it != dq._pmap.end(); ++it)
    _alloc.deallocate(*it, dq._chunksize);
  dq._pmap.clear();
}

template <typename T, class Alloc>
size_t deque<T, Alloc>::size() const { return (dq._size); }

template <typename T, class Alloc>
void deque<T, Alloc>::resize(size_type n, value_type val) {
  if (n > max_size() || n < 0)
    return;
  size_type current_size = dq._size;
  if (n <= dq._size) {
    for (size_type i = n; i < current_size; ++i)
      _alloc.destroy(&this->at(i));
    dq._tail = circular_clamp(dq._tail - (current_size - n), 0, dq._capacity);
    dq._size = n;
  } else {
    for (size_type i(0); i < n - current_size; ++i)
      push_back(val);
  }
}

/* MAX_SIZE */
template <typename T, class Alloc>
size_t deque<T, Alloc>::max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(value_type)); }

/* EMPTY */
template <typename T, class Alloc>
bool deque<T, Alloc>::empty() const { return !dq._size; }

/* PUSH_BACK */
template <typename T, class Alloc>
void deque<T, Alloc>::push_back(const T &e) {
  if (empty()) {
    dq._head = 0;
    dq._tail = 0;
    dq._tailchunk = 0;
    dq._headchunk = 0;
    _alloc.construct(dq._pmap[0], e);
    ++dq._size;
    return;
  }
  if (dq._size == dq._capacity)
    expand();
  dq._tail = circular_increment(dq._tail + 1, dq._capacity);
  dq._tailchunk = dq._tail / dq._chunksize;
  _alloc.construct(dq._pmap[dq._tailchunk] + (dq._tail % dq._chunksize), e);
  ++dq._size;
}

/* POP_BACK */
template <typename T, class Alloc>
void deque<T, Alloc>::pop_back() {
  if (empty())
    return;
  _alloc.destroy(dq._pmap[dq._tailchunk] + (dq._tail % dq._chunksize));
  if (dq._tail == dq._head)
    set_empty();
  else {
    dq._tail = circular_increment(dq._tail - 1, dq._capacity);
    dq._tailchunk = dq._tail / dq._chunksize;
  }
  --dq._size;
}

/* PUSH_FRONT */
template <typename T, class Alloc>
void deque<T, Alloc>::push_front(const T &e) {
  if (empty()) {
    dq._head = 0;
    dq._tail = 0;
    dq._tailchunk = 0;
    dq._headchunk = 0;
    _alloc.construct(dq._pmap[0], e);
    ++dq._size;
    return;
  }
  if (dq._size == dq._capacity)
    expand();
  dq._head = circular_increment(dq._head - 1, dq._capacity);
  dq._headchunk = dq._head / dq._chunksize;
  _alloc.construct(dq._pmap[dq._headchunk] + (dq._head % dq._chunksize), e);
  ++dq._size;
}

/* POP_FRONT */
template <typename T, class Alloc>
void deque<T, Alloc>::pop_front() {
  if (empty())
    return;
  _alloc.destroy(dq._pmap[dq._headchunk] + (dq._head % dq._chunksize));
  if (dq._tail == dq._head)
    set_empty();
  else {
    dq._head = circular_increment(dq._head + 1, dq._capacity);
    dq._headchunk = dq._head / dq._chunksize;
  }
  --dq._size;
}

// /* ITERATEURS */
template <typename T, class Alloc>
typename deque<T, Alloc>::const_iterator deque<T, Alloc>::begin() const { return (const_iterator(dq._head, &dq)); }
template <typename T, class Alloc>
typename deque<T, Alloc>::iterator deque<T, Alloc>::begin() { return (iterator(dq._head, &dq)); }

template <typename T, class Alloc>
typename deque<T, Alloc>::const_iterator deque<T, Alloc>::end() const { return (const_iterator(-1, &dq)); }
template <typename T, class Alloc>
typename deque<T, Alloc>::iterator deque<T, Alloc>::end() { return (iterator(-1, &dq)); }

template <typename T, class Alloc>
typename deque<T, Alloc>::const_reverse_iterator deque<T, Alloc>::rbegin() const { return const_reverse_iterator(end()); }
template <typename T, class Alloc>
typename deque<T, Alloc>::reverse_iterator deque<T, Alloc>::rbegin() { return reverse_iterator(end()); }

template <typename T, class Alloc>
typename deque<T, Alloc>::const_reverse_iterator deque<T, Alloc>::rend() const { return const_reverse_iterator(begin()); }
template <typename T, class Alloc>
typename deque<T, Alloc>::reverse_iterator deque<T, Alloc>::rend() { return reverse_iterator(begin()); }

/* AT */
template <typename T, class Alloc>
T &deque<T, Alloc>::at(size_type i) {
  if (i < 0 || i >= size())
    throw std::out_of_range(std::string("Error: tried to access out of bounds element\n"));
  size_type index = (dq._head + i) % dq._capacity;
  return (dq._pmap[index / dq._chunksize][index % dq._chunksize]);
}

template <typename T, class Alloc>
const T &deque<T, Alloc>::at(size_type i) const {
  if (i < 0 || i >= size())
    throw std::out_of_range(std::string("Error: tried to access out of bounds element\n"));
  size_type index = (dq._head + i) % dq._capacity;
  return (dq._pmap[index / dq._chunksize][index % dq._chunksize]);
}

/* FRONT */
template <typename T, class Alloc>
T &deque<T, Alloc>::front() {
  if (!dq._size)
    throw std::out_of_range(std::string("Error: out of bounds access"));
  return at(0);
}

template <typename T, class Alloc>
const T &deque<T, Alloc>::front() const {
  if (!dq._size)
    throw std::out_of_range(std::string("Error: out of bounds access"));
  return at(0);
}

/* BACK */
template <typename T, class Alloc>
T &deque<T, Alloc>::back() {
  if (!dq._size)
    throw std::out_of_range(std::string("Error: out of bounds access"));
  return at(dq._size - 1);
}

template <typename T, class Alloc>
const T &deque<T, Alloc>::back() const {
  if (!dq._size)
    throw std::out_of_range(std::string("Error: out of bounds access"));
  return at(dq._size - 1);
}

// /* ASSIGN */
template <typename T, class Alloc>
template <typename I>
void deque<T, Alloc>::assign(I first, I last) {
  typedef typename ft::is_integer<I>::type Integral;
  m_assign_dispatch(first, last, Integral());
}

template <typename T, class Alloc>
void deque<T, Alloc>::assign(size_type n, const value_type &val) {
  if (n < 0 || (size_type)n > max_size())
    throw std::bad_alloc();
  if (n > dq._capacity)
    expand(substract_size_t(n, dq._capacity) / sizeof(value_type) + 1);
  for (size_type i = 0; i < size(); ++i)
    _alloc.destroy(&this->at(i));
  dq._size = 0;
  set_empty();
  for (size_type i = 0; i < n; ++i)
    push_back(val);
}

// /* INSERT */
template <typename T, class Alloc>
typename deque<T, Alloc>::iterator deque<T, Alloc>::insert(iterator position, const value_type &val) {
  if (position == end()) {
    push_back(val);
    return end() - 1;
  }
  long n(0);
  n = std::distance(begin(), position);
  if (n < 0 || n > (long)size())
    throw std::invalid_argument("Error: position iterator is not valid");
  push_back(val);
  for (iterator b = end() - 1; b != position; --b) {
    _alloc.destroy(&(*b));
    _alloc.construct(&(*b), *(b - 1));
  }
  _alloc.destroy(&(*position));
  _alloc.construct(&(*position), val);
  return (position);
}

template <typename T, class Alloc>
void deque<T, Alloc>::insert(iterator position, size_type n, const value_type &val) {
  if (position == end()) {
    for (size_type i(0); i < n; i++)
      push_back(val);
    return;
  }
  long d(0);
  d = std::distance(begin(), position);
  if (d < 0 || d > (long)size())
    throw std::invalid_argument("Error: position iterator is not valid");
  for (size_type i(0); i < n; i++)
    push_back(val);
  for (iterator b = --end(); b != position + n - 1; --b) {
    _alloc.destroy(&(*b));
    _alloc.construct(&(*b), *(b - n));
  }
  for (iterator b = position; b != position + n; ++b) {
    _alloc.destroy(&(*b));
    _alloc.construct(&(*b), val);
  }
}

template <typename T, class Alloc>
template <typename I>
void deque<T, Alloc>::insert(deque<T, Alloc>::iterator position, I first, I last) {
  if (position == end()) {
    for (I it = first; it != last; ++it)
      push_back(*it);
    return;
  }
  long d, n;
  d = std::distance(begin(), position);
  n = std::distance(first, last);
  if (d < 0 || d > (long)size() || n < 0)
    throw std::invalid_argument("Error: invalid iterator(s)");
  for (I it = first; it != last; ++it)
    push_back(*it);
  for (iterator b = --end(); b != position + n - 1; --b) {
    _alloc.destroy(&(*b));
    _alloc.construct(&(*b), *(b - n));
  }
  I itb = first;
  for (iterator b = position; b != position + n; ++b, ++itb) {
    _alloc.destroy(&(*b));
    _alloc.construct(&(*b), *itb);
  }
}

/* ERASE */
template <typename T, class Alloc>
typename deque<T, Alloc>::iterator deque<T, Alloc>::erase(iterator position) {
  if (position == end()) {
    pop_back();
    return end();
  }
  for (iterator it = position; it != this->end() - 1; ++it) {
    _alloc.destroy(&(*it));
    _alloc.construct(&(*it), *(it + 1));
  }
  pop_back();
  return (position);
}

template <typename T, class Alloc>
typename deque<T, Alloc>::iterator deque<T, Alloc>::erase(iterator first, iterator last) {
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

/* SWAP */
template <typename T, class Alloc>
void deque<T, Alloc>::swap(deque<T, Alloc> &x) {
  std::swap(this->dq._size, x.dq._size);
  std::swap(this->dq._capacity, x.dq._capacity);
  std::swap(this->dq._chunksize, x.dq._chunksize);
  std::swap(this->dq._pmap, x.dq._pmap);
  std::swap(this->_alloc, x._alloc);

  std::swap(this->dq._head, x.dq._head);
  std::swap(this->dq._headchunk, x.dq._headchunk);
  std::swap(this->dq._tail, x.dq._tail);
  std::swap(this->dq._tailchunk, x.dq._tailchunk);
}

/* CLEAR */
template <typename T, class Alloc>
void deque<T, Alloc>::clear() {
  for (iterator it = begin(); it != end(); ++it)
    _alloc.destroy(&(*it));
  set_empty();
  dq._size = 0;
}

// /* OPERATOR OVERLOADS */
template <typename T, class Alloc>
const T &deque<T, Alloc>::operator[](size_type i) const {
  i = (dq._head + i) % dq._capacity;
  return (dq._pmap[i / dq._chunksize][i % dq._chunksize]);
}

template <typename T, class Alloc>
T &deque<T, Alloc>::operator[](size_type i) {
  i = (dq._head + i) % dq._capacity;
  return (dq._pmap[i / dq._chunksize][i % dq._chunksize]);
}

template <typename T, class Alloc>
deque<T, Alloc> &deque<T, Alloc>::operator=(const deque<T, Alloc> &target) {
  assign(target.begin(), target.end());
  return *this;
}

template <typename U, class V>
bool operator==(const deque<U, V> &lhs, const deque<U, V> &rhs) {
  if (lhs.size() != rhs.size())
    return false;
  for (size_t i = 0; i < lhs.size(); i++) {
    if (lhs[i] != rhs[i])
      return false;
  }
  return true;
}

template <typename U, class V>
bool operator!=(const deque<U, V> &lhs, const deque<U, V> &rhs) {
  return (!(lhs == rhs));
}

template <typename U, class V>
bool operator<(const deque<U, V> &lhs, const deque<U, V> &rhs) {
  return std::lexicographical_compare<
      base_dq_iterator<const U, true>,
      base_dq_iterator<const U, true> >(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename U, class V>
bool operator<=(const deque<U, V> &lhs, const deque<U, V> &rhs) {
  return ((lhs == rhs) || (lhs < rhs));
}

template <typename U, class V>
bool operator>(const deque<U, V> &lhs, const deque<U, V> &rhs) {
  return (!(lhs <= rhs));
}

template <typename U, class V>
bool operator>=(const deque<U, V> &lhs, const deque<U, V> &rhs) {
  return (!(lhs < rhs));
}

/* NON-MEMBER SWAP */
template <typename T, class Alloc>
void swap(deque<T, Alloc> &x, deque<T, Alloc> &y) {
  deque<T, Alloc> tmp = x;
  x = y;
  y = tmp;
}

// 888888  dP"Yb   dP"Yb  88     .dP"Y8
//   88   dP   Yb dP   Yb 88     `Ybo.
//   88   Yb   dP Yb   dP 88       `Y8b
//   88    YbodP   YbodP  88ood8 8bodP'

template <typename T, class Alloc>
void deque<T, Alloc>::expand(size_type nb_chunks) {
  pointer array = _alloc.allocate(dq._chunksize);
  dq._pmap.insert(dq._pmap.begin() + dq._tailchunk + 1, array);
  for (size_type i = dq._tail % dq._chunksize + 1; i < dq._chunksize; ++i) {
    _alloc.construct(array + i, dq._pmap[dq._tailchunk][i]);
    _alloc.destroy(dq._pmap[dq._tailchunk] + i);
  }
  for (size_type i = 0; i < nb_chunks - 1; ++i)
    dq._pmap.insert(dq._pmap.begin() + dq._tailchunk + 1, _alloc.allocate(dq._chunksize));
  if (dq._head > dq._tail) {
    dq._headchunk += nb_chunks;
    dq._head += nb_chunks * dq._chunksize;
  }
  dq._capacity += nb_chunks * dq._chunksize;
}

template <typename T, class Alloc>
void deque<T, Alloc>::set_empty() {
  dq._head = -1;
  dq._tail = -1;
  dq._headchunk = 0;
  dq._tailchunk = 0;
}

}  // namespace ft

#endif
