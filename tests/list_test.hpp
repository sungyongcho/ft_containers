/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 03:13:02 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 20:02:39 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_TEST_HPP
#define LIST_TEST_HPP
#include "../includes/containers.hpp"

// a predicate implemented as a function:
bool single_digit(const int &value) { return (value < 10); }

// a predicate implemented as a class:
struct is_odd {
  bool operator()(const int &value) { return (value % 2) == 1; }
};

// a binary predicate implemented as a function:
bool same_integral_part(double first, double second) { return (int(first) == int(second)); }

// a binary predicate implemented as a class:
struct is_near {
  bool operator()(double first, double second) { return (fabs(first - second) < 5.0); }
};

bool compare_nocase(const std::string &first, const std::string &second) {
  unsigned int i = 0;
  while ((i < first.length()) && (i < second.length())) {
    if (tolower(first[i]) < tolower(second[i]))
      return true;
    else if (tolower(first[i]) > tolower(second[i]))
      return false;
    ++i;
  }
  return (first.length() < second.length());
}

template <typename C>
void list_test() {
  // typedef typename C::size_type size_type;
  typedef typename C::iterator iterator;
  typedef typename C::reverse_iterator reverse_iterator;
  // constructors()
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
    std::cout << std::endl;
  }
  // begin()
  {
    int myints[] = {75, 23, 65, 42, 13};
    C mylist(myints, myints + 5);

    std::cout << "mylist contains:";
    for (iterator it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;

    std::cout << '\n';
    ;
  }
  // end()
  {
    int myints[] = {75, 23, 65, 42, 13};
    C mylist(myints, myints + 5);

    std::cout << "mylist contains:";
    for (iterator it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;

    std::cout << '\n';
  }
  // rbegin(), rend()
  {
    C mylist;
    for (int i = 1; i <= 5; ++i) mylist.push_back(i);

    std::cout << "mylist backwards:";
    for (reverse_iterator rit = mylist.rbegin(); rit != mylist.rend(); ++rit)
      std::cout << ' ' << *rit;

    std::cout << '\n';
  }
  // empty()
  {
    C mylist;
    int sum(0);

    for (int i = 1; i <= 10; ++i) mylist.push_back(i);

    while (!mylist.empty()) {
      sum += mylist.front();
      mylist.pop_front();
    }

    std::cout << "total: " << sum << '\n';
  }
  //size(), max_size()
  {
    C myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i = 0; i < 10; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert(myints.begin(), 10, 100);
    std::cout << "2. size: " << myints.size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';

    std::cout << "4. max_size: " << myints.max_size() << '\n';
  }
  // front()
  {
    C mylist;

    mylist.push_back(77);
    mylist.push_back(22);

    // now front equals 77, and back 22

    mylist.front() -= mylist.back();

    std::cout << "mylist.front() is now " << mylist.front() << '\n';
  }
  // back()
  {
    C mylist;

    mylist.push_back(10);

    while (mylist.back() != 0) {
      mylist.push_back(mylist.back() - 1);
    }

    std::cout << "mylist contains:";
    for (iterator it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;

    std::cout << '\n';
  }
  // assign()
  {
    C first;
    C second;

    first.assign(7, 100);  // 7 ints with value 100

    second.assign(first.begin(), first.end());  // a copy of first

    int myints[] = {1776, 7, 4};
    first.assign(myints, myints + 3);  // assigning from array

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
  }
  // push_front()
  {
    C mylist(2, 100);  // two ints with a value of 100
    mylist.push_front(200);
    mylist.push_front(300);

    std::cout << "mylist contains:";
    for (iterator it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;

    std::cout << '\n';
  }
  // push_back(), pop_front()
  {
    C mylist;
    mylist.push_back(100);
    mylist.push_back(200);
    mylist.push_back(300);

    std::cout << "Popping out the elements in mylist:";
    while (!mylist.empty()) {
      std::cout << ' ' << mylist.front();
      mylist.pop_front();
    }

    std::cout << "\nFinal size of mylist is " << mylist.size() << '\n';
  }
  //push_back, pop_back
  {
    C mylist;
    mylist.push_back(100);
    mylist.push_back(200);
    mylist.push_back(300);

    std::cout << "Popping out the elements in mylist:";
    while (!mylist.empty()) {
      std::cout << ' ' << mylist.front();
      mylist.pop_back();
    }

    std::cout << "\nFinal size of mylist is " << mylist.size() << '\n';
  }
  // insert()
  {
    C mylist;
    iterator it;

    // set some initial values:
    for (int i = 1; i <= 5; ++i) mylist.push_back(i);  // 1 2 3 4 5

    it = mylist.begin();
    ++it;  // it points now to number 2           ^

    mylist.insert(it, 10);  // 1 10 2 3 4 5

    // "it" still points to number 2                      ^
    mylist.insert(it, 2, 20);  // 1 10 20 20 2 3 4 5

    --it;  // it points now to the second 20            ^

    std::vector<int> myvector(2, 30);
    mylist.insert(it, myvector.begin(), myvector.end());
    // 1 10 20 30 30 20 2 3 4 5
    //               ^
    std::cout << "mylist contains:";
    for (it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // erase()
  {
    C mylist;
    iterator it1, it2;

    // set some values:
    for (int i = 1; i < 10; ++i) mylist.push_back(i * 10);

    // 10 20 30 40 50 60 70 80 90
    it1 = it2 = mylist.begin();  // ^^
    advance(it2, 6);             // ^                 ^
    ++it1;                       //    ^              ^

    it1 = mylist.erase(it1);  // 10 30 40 50 60 70 80 90
                              //    ^           ^

    it2 = mylist.erase(it2);  // 10 30 40 50 60 80 90
                              //    ^           ^

    ++it1;  //       ^        ^
    --it2;  //       ^     ^

    mylist.erase(it1, it2);  // 10 30 60 80 90
                             //        ^

    std::cout << "mylist contains:";
    for (it1 = mylist.begin(); it1 != mylist.end(); ++it1)
      std::cout << ' ' << *it1;
    std::cout << '\n';
  }
  // swap()
  {
    C first(3, 100);   // three ints with a value of 100
    C second(5, 200);  // five ints with a value of 200

    first.swap(second);

    std::cout << "first contains:";
    for (iterator it = first.begin(); it != first.end(); it++)
      std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "second contains:";
    for (iterator it = second.begin(); it != second.end(); it++)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // resize()
  {
    C mylist;

    // set some initial content:
    for (int i = 1; i < 10; ++i) mylist.push_back(i);

    mylist.resize(5);
    mylist.resize(8, 100);
    mylist.resize(12);

    std::cout << "mylist contains:";
    for (iterator it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;

    std::cout << '\n';
  }
  // clear()
  {
    C mylist;
    iterator it;

    mylist.push_back(100);
    mylist.push_back(200);
    mylist.push_back(300);

    std::cout << "mylist contains:";
    for (it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';

    mylist.clear();
    mylist.push_back(1101);
    mylist.push_back(2202);

    std::cout << "mylist contains:";
    for (it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // // splice()
  // {
  //   C list1;
  //   C list2;

  //   list1.push_back(1);
  //   list1.push_back(2);
  //   list1.push_back(3);
  //   list1.push_back(4);
  //   list1.push_back(5);

  //   list2.push_back(100);
  //   list2.push_back(200);
  //   list2.push_back(300);
  //   list2.push_back(400);
  //   list2.push_back(500);

  //   iterator it = list1.begin();
  //   std::advance(it, 2);

  //   list1.splice(it, list2);

  //   std::cout << "list1: " << list1 << "\n";
  //   std::cout << "list2: " << list2 << "\n";

  //   list2.splice(list2.begin(), list1, it, list1.end());

  //   std::cout << "list1: " << list1 << "\n";
  //   std::cout << "list2: " << list2 << "\n";
  // }
  // remove()
  {
    int myints[] = {17, 89, 7, 14};
    C mylist(myints, myints + 4);

    mylist.remove(89);

    std::cout << "mylist contains:";
    for (iterator it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // remove_if()
  {
    int myints[] = {15, 36, 7, 17, 20, 39, 4, 1};
    C mylist(myints, myints + 8);  // 15 36 7 17 20 39 4 1

    mylist.remove_if(single_digit);  // 15 36 17 20 39

    mylist.remove_if(is_odd());  // 36 20

    std::cout << "mylist contains:";
    for (iterator it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // unique()
  {
    double mydoubles[] = {12.15, 2.72, 73.0, 12.77, 3.14,
                          12.77, 73.35, 72.25, 15.3, 72.25};
    C mylist(mydoubles, mydoubles + 10);

    mylist.sort();  //  2.72,  3.14, 12.15, 12.77, 12.77,
                    // 15.3,  72.25, 72.25, 73.0,  73.35

    mylist.unique();  //  2.72,  3.14, 12.15, 12.77
                      // 15.3,  72.25, 73.0,  73.35

    mylist.unique(same_integral_part);  //  2.72,  3.14, 12.15
                                        // 15.3,  72.25, 73.0

    mylist.unique(is_near());  //  2.72, 12.15, 72.25

    std::cout << "mylist contains:";
    for (iterator it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // sort()
  {
    std::list<std::string> mylist;
    std::list<std::string>::iterator it;
    mylist.push_back("one");
    mylist.push_back("two");
    mylist.push_back("Three");

    mylist.sort();

    std::cout << "mylist contains:";
    for (it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';

    mylist.sort(compare_nocase);

    std::cout << "mylist contains:";
    for (it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << '\n';
  }
  // reverse()
  {
    C mylist;

    for (int i = 1; i < 10; ++i) mylist.push_back(i);

    mylist.reverse();

    std::cout << "mylist contains:";
    for (iterator it = mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << *it;

    std::cout << '\n';
  }
  // relational operators
  {
    C a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);

    C b;
    b.push_back(10);
    b.push_back(20);
    b.push_back(30);

    C c;
    c.push_back(30);
    c.push_back(20);
    c.push_back(10);

    if (a == b) std::cout << "a and b are equal\n";
    if (b != c) std::cout << "b and c are not equal\n";
    if (b < c) std::cout << "b is less than c\n";
    if (c > b) std::cout << "c is greater than b\n";
    if (a <= b) std::cout << "a is less than or equal to b\n";
    if (a >= b) std::cout << "a is greater than or equal to b\n";
  }
// swap (non-member)
  {
    C foo(3, 100);  // three ints with a value of 100
    C bar(5, 200);  // five ints with a value of 200

    std::swap(foo, bar);

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
