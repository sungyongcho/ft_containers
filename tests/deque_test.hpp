/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_test.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 05:51:39 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 07:23:00 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_TEST_HPP
#define DEQUE_TEST_HPP
#include "../includes/Containers.hpp"
template <typename C>
void deque_test() {
  // // typedef typename C::size_type size_type;
  typedef typename C::iterator iterator;
  // // typedef typename C::reverse_iterator reverse_iterator;

  // constructors
  {
    // constructors used in the same order as described above:
    C first;                                // empty deque of ints
    C second(4, 100);                       // four ints with value 100
    C third(second.begin(), second.end());  // iterating through second
    C fourth(third);                        // a copy of third

    // the iterator constructor can be used to copy arrays:
    int myints[] = {16, 2, 77, 29};
    C fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for (iterator it = fifth.begin(); it != fifth.end(); ++it)
      std::cout << ' ' << *it;

    std::cout << '\n';
  }
  // operator=
  {
    C first(3);   // deque with 3 zero-initialized ints
    C second(5);  // deque with 5 zero-initialized ints

    second = first;
    first = C();

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
  }
  //begin
  {
    C mydeque;

    for (int i = 1; i <= 5; i++) mydeque.push_back(i);

    std::cout << "mydeque contains:";

    iterator it = mydeque.begin();

    while (it != mydeque.end())
      std::cout << ' ' << *it++;

    std::cout << '\n';
  }
  //end
  {
    C mydeque;

    for (int i = 1; i <= 5; i++) mydeque.insert(mydeque.end(), i);

    std::cout << "mydeque contains:";

    iterator it = mydeque.begin();

    while (it != mydeque.end())
      std::cout << ' ' << *it++;

    std::cout << '\n';
  }
  {
    C myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i = 0; i < 5; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert(myints.begin(), 5, 100);
    std::cout << "2. size: " << myints.size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';
  }
}
#endif
