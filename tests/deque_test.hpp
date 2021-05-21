/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_test.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 05:51:39 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 20:02:39 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_TEST_HPP
#define DEQUE_TEST_HPP
#include "../includes/containers.hpp"

template <typename C>
void deque_test() {
  typedef typename C::size_type size_type;
  typedef typename C::iterator iterator;
  // typedef typename C::reverse_iterator reverse_iterator;

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
  // begin()
  {
    C mydeque;

    for (int i = 1; i <= 5; i++) mydeque.push_back(i);

    std::cout << "mydeque contains:";

    iterator it = mydeque.begin();

    while (it != mydeque.end())
      std::cout << ' ' << *it++;

    std::cout << '\n';
  }
  // end()
  {
    C mydeque;

    for (int i = 1; i <= 5; i++) mydeque.insert(mydeque.end(), i);

    std::cout << "mydeque contains:";

    iterator it = mydeque.begin();

    while (it != mydeque.end())
      std::cout << ' ' << *it++;

    std::cout << '\n';
  }
  // size(), max_size()
  {
    C myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i = 0; i < 5; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert(myints.begin(), 5, 100);
    std::cout << "2. size: " << myints.size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';

    std::cout << "4. max_size: " << myints.max_size() << '\n';
  }

  // resize()
  {
    C mydeque;
    iterator it;

    // set some initial content:
    for (int i = 1; i < 10; ++i) mydeque.push_back(i);

    mydeque.resize(5);
    mydeque.resize(8, 100);
    mydeque.resize(12);

    std::cout << "mydeque contains:";
    for (iterator it = mydeque.begin(); it != mydeque.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // empty()
  {
    C mydeque;
    int sum(0);

    for (int i = 1; i <= 10; i++) mydeque.push_back(i);

    while (!mydeque.empty()) {
      sum += mydeque.front();
      mydeque.pop_front();
    }

    std::cout << "total: " << sum << '\n';
  }
  // operator[]
  {
    C mydeque(10);  // 10 zero-initialized elements
    size_type sz = mydeque.size();

    // assign some values:
    for (unsigned i = 0; i < sz; i++) mydeque[i] = i;

    // reverse order of elements using operator[]:
    for (unsigned i = 0; i < sz / 2; i++) {
      int temp;
      temp = mydeque[sz - 1 - i];
      mydeque[sz - 1 - i] = mydeque[i];
      mydeque[i] = temp;
    }

    // print content:
    std::cout << "mydeque contains:";
    for (unsigned i = 0; i < sz; i++)
      std::cout << ' ' << mydeque[i];
    std::cout << '\n';
  }
  // front(), back()
  {
    C mydeque;

    mydeque.push_front(77);
    mydeque.push_back(20);

    mydeque.front() -= mydeque.back();

    std::cout << "mydeque.front() is now " << mydeque.front() << '\n';
  }
  // assign()
  {
    C first;
    C second;
    C third;

    first.assign(7, 100);  // 7 ints with a value of 100

    iterator it;
    it = first.begin() + 1;

    second.assign(it, static_cast<iterator>(first.end() - 1));  // the 5 central values of first

    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3);  // assigning from array.

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
    std::cout << "Size of third: " << int(third.size()) << '\n';
  }
  // push_back(), push_front()
  {
    C mydeque(1, 200);  // two ints with a value of 100
    mydeque.push_front(100);
    mydeque.push_back(300);

    std::cout << "mydeque contains:";
    for (iterator it = mydeque.begin(); it != mydeque.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // pop_back()
  {
    C mydeque;
    int sum(0);
    mydeque.push_back(10);
    mydeque.push_back(20);
    mydeque.push_back(30);

    while (!mydeque.empty()) {
      sum += mydeque.back();
      mydeque.pop_back();
    }

    std::cout << "The elements of mydeque add up to " << sum << '\n';
  }
  // pop_front()
  {
    C mydeque;

    mydeque.push_back(100);
    mydeque.push_back(200);
    mydeque.push_back(300);

    std::cout << "Popping out the elements in mydeque:";
    while (!mydeque.empty()) {
      std::cout << ' ' << mydeque.front();
      mydeque.pop_front();
    }

    std::cout << "\nThe final size of mydeque is " << int(mydeque.size()) << '\n';
  }
  // insert()
  {
    C mydeque;

    // set some initial values:
    for (int i = 1; i < 6; i++) mydeque.push_back(i);  // 1 2 3 4 5

    iterator it = mydeque.begin();
    ++it;

    it = mydeque.insert(it, 10);  // 1 10 2 3 4 5
    // "it" now points to the newly inserted 10

    mydeque.insert(it, 2, 20);  // 1 20 20 10 2 3 4 5
    // "it" no longer valid!

    it = mydeque.begin() + 2;

    std::vector<int> myvector(2, 30);
    mydeque.insert(it, myvector.begin(), myvector.end());
    // 1 20 30 30 20 10 2 3 4 5

    std::cout << "mydeque contains:";
    for (it = mydeque.begin(); it != mydeque.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // erase()
  {
    C mydeque;

    // set some values (from 1 to 10)
    for (int i = 1; i <= 10; i++) mydeque.push_back(i);

    // erase the 6th element
    mydeque.erase(mydeque.begin() + 5);

    // erase the first 3 elements:
    mydeque.erase(mydeque.begin(), mydeque.begin() + 3);

    std::cout << "mydeque contains:";
    for (iterator it = mydeque.begin(); it != mydeque.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // swap()
  {
    C foo(3, 100);  // three ints with a value of 100
    C bar(5, 200);  // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    for (iterator it = foo.begin(); it != foo.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "bar contains:";
    for (iterator it = bar.begin(); it != bar.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }

  // relational_operators
  {
    C foo(3, 100);  // three ints with a value of 100
    C bar(2, 200);  // two ints with a value of 200

    if (foo == bar) std::cout << "foo and bar are equal\n";
    if (foo != bar) std::cout << "foo and bar are not equal\n";
    if (foo < bar) std::cout << "foo is less than bar\n";
    if (foo > bar) std::cout << "foo is greater than bar\n";
    if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
    if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
  }
  // swap() (non-member)
  {
    C foo(3, 100);  // three ints with a value of 100
    C bar(5, 200);  // five ints with a value of 200

    swap(foo, bar);

    std::cout << "foo contains:";
    for (iterator it = foo.begin(); it != foo.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "bar contains:";
    for (iterator it = bar.begin(); it != bar.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
}

// for ::deque<unsigned>
template <typename C>
void deque_test_2() {
// at()
  {
    C mydeque(10);  // 10 zero-initialized unsigneds

    // assign some values:
    for (unsigned i = 0; i < mydeque.size(); i++)
      mydeque.at(i) = i;

    std::cout << "mydeque contains:";
    for (unsigned i = 0; i < mydeque.size(); i++)
      std::cout << ' ' << mydeque.at(i);
  }
}

#endif
