/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 03:10:02 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 19:59:50 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TEST_HPP
#define VECTOR_TEST_HPP
#include "../includes/Containers.hpp"
template<typename C>
void vector_test() {
  typedef typename C::size_type size_type;
  typedef typename C::iterator iterator;
  typedef typename C::reverse_iterator reverse_iterator;
  // // typedef typename C::const_iterator const_iterator;
  // typedef typename C::const_reverse_iterator const_reverse_iterator;

  {
    C first;
    C second(4, 100);
    C third(second.begin(), second.end());
    C fourth(third);

    int myints[] = {16, 2, 77, 29};
    C fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for (iterator it = fifth.begin(); it != fifth.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << second.size() << std::endl;
  }
  // iterator
  // begin, end
  {
    C myvector;
    for (int i = 1; i <= 5; i++) myvector.push_back(i);

    std::cout << "myvector contains:";
    for (iterator it = myvector.begin(); it != myvector.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  //rbegin
  {
    C myvector(5);  // 5 default-constructed ints

    int i = 0;

    reverse_iterator rit = myvector.rbegin();
    for (; rit != myvector.rend(); ++rit)
      *rit = ++i;

    std::cout << "myvector contains:";
    for (iterator it = myvector.begin(); it != myvector.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  //rend
  {
    C myvector(5);  // 5 default-constructed ints

    reverse_iterator rit = myvector.rbegin();

    int i = 0;
    for (rit = myvector.rbegin(); rit != myvector.rend(); ++rit)
      *rit = ++i;

    std::cout << "myvector contains:";
    for (iterator it = myvector.begin(); it != myvector.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  ///size
  {
    C myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i = 0; i < 10; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert(myints.end(), 10, 100);
    std::cout << "2. size: " << myints.size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';
  }
  //max_size
  {
    C myvector;

    // set some content in the vector:
    for (int i = 0; i < 100; i++) myvector.push_back(i);

    std::cout << "size: " << myvector.size() << "\n";
    std::cout << "capacity: " << myvector.capacity() << "\n";
    std::cout << "max_size: " << myvector.max_size() << "\n";
  }
  //resize
  {
    C myvector;

    // set some initial content:
    for (int i = 1; i < 10; i++) myvector.push_back(i);

    myvector.resize(5);
    myvector.resize(8, 100);
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (size_t i = 0; i < myvector.size(); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }
  // size, capacity, max_size
  {
    C myvector;

    // set some content in the vector:
    for (size_t i = 0; i < 100; i++) myvector.push_back(i);

    std::cout << "size: " << (int)myvector.size() << '\n';
    std::cout << "capacity: " << (int)myvector.capacity() << '\n';
    std::cout << "max_size: " << (int)myvector.max_size() << '\n';
  }
  //reverse
  {
    C myvector(10);  // 10 zero-initialized elements

    size_type sz = myvector.size();

    // assign some values:
    for (unsigned i = 0; i < sz; i++) myvector[i] = i;

    // reverse vector using operator[]:
    for (unsigned i = 0; i < sz / 2; i++) {
      int temp;
      temp = myvector[sz - 1 - i];
      myvector[sz - 1 - i] = myvector[i];
      myvector[i] = temp;
    }

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < sz; i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }
  //operator[]
  {
    C myvector(10);  // 10 zero-initialized elements

    size_type sz = myvector.size();

    // assign some values:
    for (unsigned i = 0; i < sz; i++) myvector[i] = i;

    // reverse vector using operator[]:
    for (unsigned i = 0; i < sz / 2; i++) {
      int temp;
      temp = myvector[sz - 1 - i];
      myvector[sz - 1 - i] = myvector[i];
      myvector[i] = temp;
    }

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < sz; i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }
  // at
  {
    C myvector(10);  // 10 zero-initialized ints

    // assign some values:
    for (unsigned i = 0; i < myvector.size(); i++)
      myvector.at(i) = i;

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++)
      std::cout << ' ' << myvector.at(i);
    std::cout << '\n';
  }
  // front
  {
    C myvector;

    myvector.push_back(78);
    myvector.push_back(16);

    // now front equals 78, and back 16

    myvector.front() -= myvector.back();

    std::cout << "myvector.front() is now " << myvector.front() << '\n';
  }
  //back
  {
    C myvector;

    myvector.push_back(10);

    while (myvector.back() != 0) {
      myvector.push_back(myvector.back() - 1);
    }

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }
  // assign
  {
    C first;
    C second;
    C third;

    first.assign(7, 100);  // 7 ints with a value of 100

    iterator it;
    it = first.begin() + 1;

    second.assign(first.begin(), static_cast<iterator>(first.end()--));  // the 5 central values of first

    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3);  // assigning from array.

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
    std::cout << "Size of third: " << int(third.size()) << '\n';
  }
  //push_back , pop_back
  {
    C myvector;
    int sum(0);
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);

    while (!myvector.empty()) {
      sum += myvector.back();
      myvector.pop_back();
    }

    std::cout << "The elements of myvector add up to " << sum << '\n';
  }
  //insert
  {
    C myvector(3, 100);
    iterator it;

    it = myvector.begin();
    it = myvector.insert(it, 200);

    myvector.insert(it, 2, 300);

    // "it" no longer valid, get a new one:
    it = myvector.begin();

    C anothervector(2, 400);
    myvector.insert(it + 2, anothervector.begin(), anothervector.end());

    int myarray[] = {501, 502, 503};
    myvector.insert(myvector.begin(), myarray, myarray + 3);

    std::cout << "myvector contains:";
    for (it = myvector.begin(); it < myvector.end(); it++)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  {
    C myvector;

    // set some values (from 1 to 10)
    for (int i = 1; i <= 10; i++) myvector.push_back(i);

    // erase the 6th element
    myvector.erase(myvector.begin() + 5);

    // erase the first 3 elements:
    myvector.erase(myvector.begin(), myvector.begin() + 3);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); ++i)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }
  ///swap
  {
    C foo(3, 100);  // three ints with a value of 100
    C bar(5, 200);  // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    for (unsigned i = 0; i < foo.size(); i++)
      std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i = 0; i < bar.size(); i++)
      std::cout << ' ' << bar[i];
    std::cout << '\n';
  }
  //clear
  {
    C myvector;
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';

    myvector.clear();
    myvector.push_back(1101);
    myvector.push_back(2202);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }
  //relational operator
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
  //non_member swap
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
}
#endif
