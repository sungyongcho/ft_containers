/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_queue_test.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 05:46:46 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 20:52:15 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_TEST_HPP
#define STACK_TEST_HPP

#include "../includes/containers.hpp"
template <typename C>
void stack_test() {
  // empty()
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

template <typename C>
void queue_test() {
  // empty()
  {
    C myqueue;
    int sum(0);

    for (int i = 1; i <= 10; i++) myqueue.push(i);

    while (!myqueue.empty()) {
      sum += myqueue.front();
      myqueue.pop();
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

  //front()
  {
    C myqueue;

    myqueue.push(77);
    myqueue.push(16);

    myqueue.front() -= myqueue.back();  // 77-16=61

    std::cout << "myqueue.front() is now " << myqueue.front() << '\n';
  }
  // back()
  {
    C myqueue;

    myqueue.push(12);
    myqueue.push(75);  // this is now the back

    myqueue.back() -= myqueue.front();

    std::cout << "myqueue.back() is now " << myqueue.back() << '\n';
  }
  // push()
  {
    C myqueue;

    myqueue.push(12);
    myqueue.push(75);  // this is now the back

    myqueue.back() -= myqueue.front();

    std::cout << "myqueue.back() is now " << myqueue.back() << '\n';
  }
  // pop()
  {
    C myqueue;

    myqueue.push(1);
    myqueue.push(2);
    myqueue.push(3);
    myqueue.push(4);
    myqueue.push(5);

    std::cout << "myqueue.back() before " << myqueue.front() << '\n';

    myqueue.pop();
    std::cout << "myqueue.back() after " << myqueue.front() << '\n';
  }
}

template <typename C1, typename C2, typename C3>
void stack_test_2() {
  //constructors
  {
    std::cout << "=============CONSTRUCTORS TEST======"<<std::endl;
    C2 mydeque(3, 100);   // deque with 3 elements
    C3 myvector(2, 200);  // vector with 2 elements

    C1 first;            // empty stack
    C1 second(mydeque);  // stack initialized to copy of deque

    std::stack<int, C3 > third;  // empty stack using vector
    std::stack<int, C3 > fourth(myvector);

    std::cout << "size of first: " << first.size() << '\n';
    std::cout << "size of second: " << second.size() << '\n';
    std::cout << "size of third: " << third.size() << '\n';
    std::cout << "size of fourth: " << fourth.size() << '\n';
  }
}
#endif
