/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 03:13:02 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 03:15:55 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_TEST_HPP
#define LIST_TEST_HPP
#include "../includes/Containers.hpp"

template <typename C>
void list_test() {
  typedef typename C::size_type size_type;
  typedef typename C::iterator iterator;
  typedef typename C::reverse_iterator reverse_iterator;

  {
    // constructors used in the same order as described above:
    C first;                                // empty list of ints
    C second(4, 100);                       // four ints with value 100
    C third(second.begin(), second.end());  // iterating through second
    C fourth(third);                        // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16, 2, 77, 29};
    C fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are: ";
    for (iterator it = fifth.begin(); it != fifth.end(); it++)
      std::cout << *it << ' ';
  }
}

#endif
