/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 04:24:48 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 05:42:41 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TEST_HPP
#define MAP_TEST_HPP
#include "../includes/Containers.hpp"
bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp {
  bool operator()(const char &lhs, const char &rhs) const { return lhs < rhs; }
};

template <typename C>
void map_test() {
  typedef typename C::iterator iterator;
  typedef typename C::reverse_iterator reverse_iterator;
  typedef typename C::key_compare key_compare;

  //constructor
  {
    C first;

    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;

    C second(first.begin(), first.end());

    C third(second);

    std::map<char, int, classcomp> fourth;  // class as Compare

    bool (*fn_pt)(char, char) = fncomp;
    std::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer as Compare

    std::cout << "no output" << std::endl;
  }
  // = operator
  {
    C first;
    C second;

    first['x'] = 8;
    first['y'] = 16;
    first['z'] = 32;

    second = first;  // second now contains 3 ints
    first = C();     // and first is now empty

    std::cout << "Size of first: " << first.size() << '\n';
    std::cout << "Size of second: " << second.size() << '\n';
  }
  // = operator , begin, end
  {
    C mymap;

    mymap['b'] = 100;
    mymap['a'] = 200;
    mymap['c'] = 300;

    // show content:
    for (iterator it = mymap.begin(); it != mymap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';
  }
  //rbegin, rend
  {
    C mymap;

    mymap['x'] = 100;
    mymap['y'] = 200;
    mymap['z'] = 300;

    // show content:
    reverse_iterator rit;
    for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
      std::cout << rit->first << " => " << rit->second << '\n';
  }
  //empty
  {
    C mymap;

    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;

    while (!mymap.empty()) {
      std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
      mymap.erase(mymap.begin());
    }
  }
  //size
  {
    C mymap;
    mymap['a'] = 101;
    mymap['b'] = 202;
    mymap['c'] = 302;

    std::cout << "mymap.size() is " << mymap.size() << '\n';
    std::cout << "mymap.max_size() is " << mymap.max_size() << '\n';
  }
  //insert
  {
    C mymap;

    // first insert function version (single parameter):
    mymap.insert(std::pair<char, int>('a', 100));
    mymap.insert(std::pair<char, int>('z', 200));

    std::pair<iterator, bool> ret;
    ret = mymap.insert(std::pair<char, int>('z', 500));
    if (ret.second == false) {
      std::cout << "element 'z' already existed";
      std::cout << " with a value of " << ret.first->second << '\n';
    }

    // second insert function version (with hint position):
    iterator it = mymap.begin();
    mymap.insert(it, std::pair<char, int>('b', 300));  // max efficiency inserting
    mymap.insert(it, std::pair<char, int>('c', 400));  // no max efficiency inserting

    // third insert function version (range insertion):
    C anothermap;
    anothermap.insert(mymap.begin(), mymap.find('c'));

    // showing contents:
    std::cout << "mymap contains:\n";
    for (it = mymap.begin(); it != mymap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';

    std::cout << "anothermap contains:\n";
    for (it = anothermap.begin(); it != anothermap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';
  }
  //erase
  {
    C mymap;
    iterator it;

    // insert some values:
    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;
    mymap['d'] = 40;
    mymap['e'] = 50;
    mymap['f'] = 60;

    it = mymap.find('b');
    mymap.erase(it);  // erasing by iterator

    mymap.erase('c');  // erasing by key

    it = mymap.find('e');
    mymap.erase(it, mymap.end());  // erasing by range

    // show content:
    for (it = mymap.begin(); it != mymap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';
  }
  {
    C foo, bar;

    foo['x'] = 100;
    foo['y'] = 200;

    bar['a'] = 11;
    bar['b'] = 22;
    bar['c'] = 33;

    foo.swap(bar);

    std::cout << "foo contains:\n";
    for (iterator it = foo.begin(); it != foo.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';

    std::cout << "bar contains:\n";
    for (iterator it = bar.begin(); it != bar.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';
  }
  //swap
  {
    C mymap;

    mymap['x'] = 100;
    mymap['y'] = 200;
    mymap['z'] = 300;

    std::cout << "mymap contains:\n";
    for (iterator it = mymap.begin(); it != mymap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';

    mymap.clear();
    mymap['a'] = 1101;
    mymap['b'] = 2202;

    std::cout << "mymap contains:\n";
    for (iterator it = mymap.begin(); it != mymap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';
  }
  //clear
  {
    C mymap;

    mymap['x'] = 100;
    mymap['y'] = 200;
    mymap['z'] = 300;

    std::cout << "mymap contains:\n";
    for (iterator it = mymap.begin(); it != mymap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';

    mymap.clear();
    mymap['a'] = 1101;
    mymap['b'] = 2202;

    std::cout << "mymap contains:\n";
    for (iterator it = mymap.begin(); it != mymap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';
  }
  //key_comp
  {
    C mymap;

    key_compare mycomp = mymap.key_comp();

    mymap['a'] = 100;
    mymap['b'] = 200;
    mymap['c'] = 300;

    std::cout << "mymap contains:\n";

    char highest = mymap.rbegin()->first;  // key value of last element

    iterator it = mymap.begin();
    do {
      std::cout << it->first << " => " << it->second << '\n';
    } while (mycomp((*it++).first, highest));

    std::cout << '\n';
  }
  {
    C mymap;

    mymap['x'] = 1001;
    mymap['y'] = 2002;
    mymap['z'] = 3003;

    std::cout << "mymap contains:\n";

    std::pair<char, int> highest = *mymap.rbegin();  // last element

    iterator it = mymap.begin();
    do {
      std::cout << it->first << " => " << it->second << '\n';
    } while (mymap.value_comp()(*it++, highest));
  }
  //find
  {
    C mymap;
    iterator it;

    mymap['a'] = 50;
    mymap['b'] = 100;
    mymap['c'] = 150;
    mymap['d'] = 200;

    it = mymap.find('b');
    if (it != mymap.end())
      mymap.erase(it);

    // print content:
    std::cout << "elements in mymap:" << '\n';
    std::cout << "a => " << mymap.find('a')->second << '\n';
    std::cout << "c => " << mymap.find('c')->second << '\n';
    std::cout << "d => " << mymap.find('d')->second << '\n';
  }
  //count
  {
    C mymap;
    char c;

    mymap['a'] = 101;
    mymap['c'] = 202;
    mymap['f'] = 303;

    for (c = 'a'; c < 'h'; c++) {
      std::cout << c;
      if (mymap.count(c) > 0)
        std::cout << " is an element of mymap.\n";
      else
        std::cout << " is not an element of mymap.\n";
    }
  }
  //lower_bound, upper_bound
  {
    C mymap;
    iterator itlow, itup;

    mymap['a'] = 20;
    mymap['b'] = 40;
    mymap['c'] = 60;
    mymap['d'] = 80;
    mymap['e'] = 100;

    itlow = mymap.lower_bound('b');  // itlow points to b
    itup = mymap.upper_bound('d');   // itup points to e (not d!)

    mymap.erase(itlow, itup);  // erases [itlow,itup)

    // print content:
    for (iterator it = mymap.begin(); it != mymap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';
  }
  //equal_range
  {
    C mymap;

    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;

    std::pair<iterator, iterator> ret;
    ret = mymap.equal_range('b');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';
  }
}

template <typename C>
void map_test_2() {
  //operator[]
  {
    C mymap;

    mymap['a'] = "an element";
    mymap['b'] = "another element";
    mymap['c'] = mymap['b'];

    std::cout << "mymap['a'] is " << mymap['a'] << '\n';
    std::cout << "mymap['b'] is " << mymap['b'] << '\n';
    std::cout << "mymap['c'] is " << mymap['c'] << '\n';
    std::cout << "mymap['d'] is " << mymap['d'] << '\n';

    std::cout << "mymap now contains " << mymap.size() << " elements.\n";
  }
}
#endif
