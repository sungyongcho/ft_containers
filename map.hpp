/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:06:40 by sucho             #+#    #+#             */
/*   Updated: 2021/05/11 23:01:19 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "BaseIterators.hpp"

namespace ft {
template <class Key, class T, class Cmp, class Alloc>
class map {
 public:
  // clang-format off
   typedef Key                                     key_type;
   typedef T                                       mapped_type;
   typedef Cmp                                     key_compare;
   typedef Alloc                                   allocator_type;
   typedef std::pair<const key_type, mapped_type>  value_type;
   typedef value_type&                             reference;
   typedef const value_type&*                      const_reference;
   typedef value_type*                             pointer;
   typedef const value_type*                       const_pointer;
   typedef size_t                                  size_type;
   typedef std::ptrdiff_t                          difference_type;
  // clang-format on

  class value_compare {
   private:
    value_compare() {}
    key_compare comp;

   public:
    // clang-format off
    typedef bool                    result_type;
    typedef std::pair<const Key, T> first_argument_type;
    typedef std::pair<const Key, T> second_argument_type;
    // clang-format on

    value_compare(const value_compare &o) : comp(o.comp) {}
    value_comapre(const key_compare &c) : comp(c) {}
    value_compare &operator=(const value_compare &other) {
      comp = other.comp;
      return (*this);
    }
    ~value_compare() {}
    bool operator()(const std::pair<const Key, T> &a, const std::pair<const Key, T> &b) const {
      return comp(a.first, b.first);
    }
  };

 protected:
  typedef ft::map_node<value_type> Node;

  typedef typename Alloc::template rebind<Node>::other node_alloc;

  template <typename U, bool is_const>
  class avl_iterator : public base_avl_iterator<U, is_const> {
   protected:
    using base_avl_iterator<U, is_const>::ptr;
    using base_avl_iterator<U, is_const>::get;
    using base_avl_iterator<U, is_const>::get_next;
    using base_avl_iterator<U, is_const>::get_prev;
    using base_avl_iterator<U, is_const>::tree_ref;

   public:
    // clang-format off
    typedef U                                             value_type;
    typedef typename choose<is_const, const U&, U&>::type reference;
    typedef typename choose<is_const, const U*, U*>::type pointer;
    typedef std::ptrdiff_t                                difference_type;
    typedef std::bidirectional_iterator_tag               iterator_category;
    typedef typename remove_const<U>::type                non_const_type;
    typedef avl_iterator<non_const_type, false>           non_const_iterator;
    // clang-format on

    avl_iterator() : base_avl_iterator<U, is_const>() {}
    avl_iterator(Node *ptr, Node *const *tree)
        : base_avl_iterator<U, is_const>(ptr, tree) {}
    avl_iterator(const base_avl_iterator<non_const_type, false> &it)
        : base_avl_iterator<U, is_const>(it.ptr, it.tree_ref) {}
    avl_iterator(const non_const_iterator &target)
        : base_avl_iterator<U, is_const>(target) {}
    using base_avl_iterator<U, is_const>::operator=;
    ~avl_iterator() {}
  };

  template <typename I>
  class avl_reverse_iterator : public base_reverse_iterator<I> {
   private:
    using base_reverse_iterator<I>::itbase;
    typedef typename base_reverse_iterator<I>::non_const_iterator non_const_iterator;

   public:
    avl_reverse_iterator()
        : base_reverse_iterator<I>() {}
    avl_reverse_iterator(const avl_reverse_iterator<non_const_iterator> &it)
        : base_reverse_iterator<I>(it) {}
    avl_reverse_iterator(const base_reverse_iterator<I> &rev_it)
        : base_reverse_iterator<I>(rev_it.itbase) {}
    using base_reverse_iterator<I>::operator=;
    ~avl_reverse_iterator() {}
  };

  template <typename U, bool is_const>
  inline const base_avl_iterator<U, is_const> &bcast(const avl_iterator<U, is_const> &it) const {
    return *(base_avl_iterator<U, is_const> *)&it;
  }

 public:
  // clang-format off
  typedef avl_iterator<value_type, false>       iterator;
  typedef avl_iterator<const value_type, true>  const_iterator;
  typedef avl_reverse_iterator<iterator>        reverse_iterator;
  typedef avl_reverse_iterator<const_iterator>  const_reverse_iterator;
  // clang-format on
  explicit map(const key_compare &comp = key_compare());
  template <typename I>
  map(I first, I last, const key_compare &comp = key_compare());
  map(const map &other);
  ~map();

  map<Key, T, Cmp, Alloc> &operator=(const map<Key, T, Cmp, Alloc> &target);

  const_iterator begin() const;
  iterator begin();

  const_iterator end() const;
  iterator end();

  const_reverse_iterator rbegin() const;
  reverse_iterator rbegin();

  const_reverse_iterator rend() const;
  reverse_iterator rend();

  template <class I>
  void insert(I first, I last);
  std::pair<iterator, bool> insert(const value_type &val);
  iterator insert(iterator position, const value_type &val);

  void erase(iterator position);
  size_type erase(const key_type &k);
  void erase(iterator first, iterator last);

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void swap(map<Key, T, Cmp, Alloc> &x);

  void clear();

  key_compare key_comp() const;
  value_compare value_comp() const;

  iterator find(const key_type &k);
  const_iterator find(const key_type &k) const;

  size_type count(const key_type &k) const;

  iterator lower_bound(const key_type &k);
  const_iterator lower_bound(const key_type &k) const;

  iterator upper_bound(const key_type &k);
  const_iterator upper_bound(const key_type &k) const;

  std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
  std::pair<iterator, iterator> equal_range(const key_type &k);

  mapped_type &operator[](const key_type &key);

 protected:
  Node *tree;
  size_type m_size;
  key_compare m_comp;
  allocator_type m_alloc;

  const Node *get();
  bool key_equal(Key lhs, Key rhs) const;
  Node *find_node(Node *root, const key_type &key) const;
  mapped_type &get_mapped(Node *root, const key_type &key, bool force);

  void link_left(Node *parent, Node *child);
  void link_right(Node *parent, Node *child);
  int set_heights(Node *root);
  std::pair<iterator, bool> insert_node(Node *root, Key key, T val, bool force = false);
  std::pair<Node *, bool> recursive_insert(Node *root, Key key, T Val, bool force = false);
  size_type delete_node(Key key);
  Node *recursive_extract(Node *parent, Node *root, Key key);
  int readjust_heights(Node *node, Key key);
  void update_node_height(Node *node);
  void rebalance_tree(Node *parent, Node *node, Key key);
  void left_rotate(Node *root, Node *node, Key key);
  void right_rotate(Node *root, Node *node, Key key);
  bool is_balanced(Node *root);

  void print();
  void print_root(const Node *root);
  void free_tree(Node *&root);
};

/* constructor */

template <class Key, class T, class Cmp, class Alloc>
map<Key, T, Cmp, Alloc>::map(const key_compare &comp)
    : tree(NULL), m_size(0), m_comp(comp), m_alloc(allocator_type()) {}

template <class Key, class T, class Cmp, class Alloc>
template <typename I>
map<Key, T, Cmp, Alloc>::map(I first, I last, const key_compare &comp)
    : tree(NULL), m_size(0), m_comp(comp), m_alloc(allocator_type()) {
  for (I it = first; it != last; ++it)
    insert_node(tree, it->first, it->second, false);
}

template <class Key, class T, class Cmp, class Alloc>
map<Key, T, Cmp, Alloc>::map(const map &other)
    : tree(NULL), m_size(0), m_comp(other.m_comp), m_alloc(other.m_alloc) {
  *this = other;
}

}  // namespace ft
