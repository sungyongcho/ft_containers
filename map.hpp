/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 22:06:40 by sucho             #+#    #+#             */
/*   Updated: 2021/05/07 14:54:52 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #pragma once

// #include "BaseIterators.hpp"

// namespace ft {
// template <class Ky, class T, class Cmp, class Alloc>
// class map {
//  public:
//   // clang-format off
//    typedef Key                                     key_type;
//    typedef T                                       mapped_value;
//    typedef Cmp                                     key_compare;
//    typedef Alloc                                   allocator_type;
//    typedef std::pair<const key_type, mapped_type>  value_type;
//    typedef value_type&                             reference;
//    typedef const value_type&*                      const_reference;
//    typedef value_type*                             pointer;
//    typedef const value_type*                       const_pointer;
//    typedef size_t                                  size_type;
//    typedef str::ptrdiff_t                          difference_type;
//   // clang-format on

//   class value_compare {
//    private:
//     value_compare() {}
//     key_compare comp;

//    public:
//     // clang-format off
//     typedef bool                    result_type;
//     typedef std::pair<const Key, T> first_argument_type;
//     typedef std::pair<const Key, T> second_argument_type;
//     // clang-format on

//     value_compare(const value_compare &o) : comp(o.comp) {}
//     value_comapre(const key_compare &c) : comp(c) {}
//     value_compare &operator=(const value_compare &other) {
//       comp = other.comp;
//       return (*this);
//     }
//     ~value_compare() {}
//     bool operator()(const std::pair<const Key, T> &a, const std::pair<const Key, T> &b) const {
//       return comp(a.first, b.first);
//     }
//   };

//  protected:
//   typedef ft::map_node<value_type> Node;

//   typedef typename Alloc::template rebind<Node>::other node_alloc;

//   template <typename U, bool is_const>
//   class avl_iterator : public base_avl_iterator<U, is_const> {
//    protected:
//     using base_avl_iterator<U, is_const>::ptr;
//     using base_avl_iterator<U, is_const>::get;
//     using base_avl_iterator<U, is_const>::get_next;
//     using base_avl_iterator<U, is_const>::get_prev;
//     using base_avl_iterator<U, is_const>::tree_ref;

//    public:
//     // clang-format off
//     typedef U                                             value_type;
//     typedef typename choose<is_const, const U&, U&>::type reference;
//     typedef typename choose<is_const, const U*, U*>::type pointer;
//     typedef std::ptrdiff_t                                difference_type;
//     typedef std::bidirectional_iterator_tag               iterator_category;
//     typedef typename remove_const<U>::type                non_const_type;
//     typedef avl_iterator<non_const_type, false>           non_const_iterator;
//     // clang-format on

//     avl_iterator() : base_avl_iterator<U, is_const>() {}
//     avl_iterator(Node *ptr, Node *const *tree)
//         : base_avl_iterator<U, is_const>(ptr, tree) {}
//     avl_iterator(const base_avl_iterator<non_const_type, false> &it)
//         : base_avl_iterator<U, is_const>(it.ptr, it.tree_ref) {}
//     avl_iterator(const non_const_iterator &target)
//         : base_avl_iterator<U, is_const>(target) {}
//     using base_avl_iterator<U, is_const>::operator=;
//     ~avl_iterator() {}
//   };

//   template <typename I>
//   class avl_reverse_iterator : public base_reverse_iterator<I> {
//    private:
//     using base_reverse_iterator<I>::itbase;
//     typedef typename base_reverse_iterator<I>::non_const_iterator non_const_iterator;

//    public:
//     avl_reverse_iterator()
//         : base_reverse_iterator<I>() {}
//     avl_reverse_iterator(const avl_reverse_iterator<non_const_iterator> &it)
//         : base_reverse_iterator<I>(it) {}
//     avl_reverse_iterator(const base_reverse_iterator<I> &rev_it)
//         : base_reverse_iterator<I>(rev_it.itbase) {}
//     using base_reverse_iterator<I>::operator=;
//     ~avl_reverse_iterator() {}
//   };

//   template <typename U, bool is_const>
//   inline const base_avl_iterator<U, is_const> &bcast(const avl_iterator<U, is_const> &it) const {
//     return *(base_avl_iterator<U, is_const> *)&it;
//   }
// };
// }  // namespace ft
