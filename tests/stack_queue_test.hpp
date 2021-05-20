/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_queue_test.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 05:46:46 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 07:59:55 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_TEST_HPP
#define STACK_TEST_HPP

#include "../includes/Containers.hpp"
template <typename C>
void stack_test() {
  //empty()
  {
    C mystack;
    int sum(0);

    for (int i = 1; i <= 10; i++) mystack.push(i);

    while (!mystack.empty()) {
      sum += mystack.top();
      mystack.pop();
    }

    std::cout << "total: " << sum << '\n';
  }
  // size()
  {
    C myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i = 0; i < 5; i++) myints.push(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.pop();
    std::cout << "2. size: " << myints.size() << '\n';
  }
  // top()
  {
    C mystack;

    mystack.push(10);
    mystack.push(20);

    mystack.top() -= 5;

    std::cout << "mystack.top() is now " << mystack.top() << '\n';
  }
  // push()
  {
    C mystack;

    for (int i = 0; i < 5; ++i) mystack.push(i);

    std::cout << "Popping out elements...";
    while (!mystack.empty()) {
      std::cout << ' ' << mystack.top();
      mystack.pop();
    }
    std::cout << '\n';
  }
  // pop()
  {
    C mystack;

    for (int i = 0; i < 5; ++i) mystack.push(i);

    std::cout << "Popping out elements...";
    while (!mystack.empty()) {
      std::cout << ' ' << mystack.top();
      mystack.pop();
    }
    std::cout << '\n';
  }
}

// template <typename C>
// void stack_test_2()
// {
//   //constructors
//   {
//     std::deque<int> mydeque(3, 100);    // deque with 3 elements
//     std::vector<int> myvector(2, 200);  // vector with 2 elements

//     C first;            // empty stack
//     C second(mydeque);  // stack initialized to copy of deque

//     // std::stack<int, std::vector<int> > third;  // empty stack using vector
//     // std::stack<int, std::vector<int> > fourth(myvector);

//     std::cout << "size of first: " << first.size() << '\n';
//     std::cout << "size of second: " << second.size() << '\n';
//     // std::cout << "size of third: " << third.size() << '\n';
//     // std::cout << "size of fourth: " << fourth.size() << '\n';
//   }
// }
#endif
