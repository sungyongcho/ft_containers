/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:19:00 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 21:11:17 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>

#include "./tests/tests.hpp"
int main(void) {
  std::cout << "====================WARNING=====================" << std::endl;
  std::cout << " - this file only creates output of test results for each container," << std::endl;
  std::cout << "   so make sure if you want check the result, run \'make test\'." << std::endl;
  {
    std::streambuf *coutbuf = std::cout.rdbuf();
    {
      std::ofstream real("./diffs/std_vector_test.txt");
      std::cout.rdbuf(real.rdbuf());
      vector_test<std::vector<int> >();

      std::ofstream mine("./diffs/ft_vector_test.txt");
      std::cout.rdbuf(mine.rdbuf());
      vector_test<ft::vector<int> >();
      std::cout.rdbuf(coutbuf);
    }
  }
  {
    std::streambuf *coutbuf = std::cout.rdbuf();
    {
      std::ofstream real("./diffs/std_list_test.txt");
      std::cout.rdbuf(real.rdbuf());
      list_test<std::list<int> >();

      std::ofstream mine("./diffs/ft_list_test.txt");
      std::cout.rdbuf(mine.rdbuf());
      list_test<ft::list<int> >();
      std::cout.rdbuf(coutbuf);
    }
  }
  {
    std::streambuf *coutbuf = std::cout.rdbuf();
    {
      std::ofstream real("./diffs/std_map_test.txt");
      std::cout.rdbuf(real.rdbuf());
      map_test<std::map<char, int> >();
      map_test_2<std::map<char, std::string> >();

      std::ofstream mine("./diffs/ft_map_test.txt");
      std::cout.rdbuf(mine.rdbuf());
      map_test<ft::map<char, int> >();
      map_test_2<ft::map<char, std::string> >();
      std::cout.rdbuf(coutbuf);
    }
  }
  {
    std::streambuf *coutbuf = std::cout.rdbuf();
    {
      std::ofstream real("./diffs/std_deque_test.txt");
      std::cout.rdbuf(real.rdbuf());
      deque_test<std::deque<int> >();
      deque_test_2<std::deque<unsigned> >();

      std::ofstream mine("./diffs/ft_deque_test.txt");
      std::cout.rdbuf(mine.rdbuf());
      deque_test<ft::deque<int> >();
      deque_test_2<ft::deque<unsigned> >();
      std::cout.rdbuf(coutbuf);
    }
  }
  {
    std::streambuf *coutbuf = std::cout.rdbuf();
    {
      std::ofstream real("./diffs/std_stack_test.txt");
      std::cout.rdbuf(real.rdbuf());
      stack_test<std::stack<int> >();
      stack_test_2<std::stack<int>, std::deque<int>, std::vector<int> >();

      std::ofstream mine("./diffs/ft_stack_test.txt");
      std::cout.rdbuf(mine.rdbuf());
      stack_test<ft::stack<int> >();
      stack_test_2<ft::stack<int>, ft::deque<int>, ft::vector<int> >();
      std::cout.rdbuf(coutbuf);
    }
  }
  {
    std::streambuf *coutbuf = std::cout.rdbuf();
    {
      std::ofstream real("./diffs/std_queue_test.txt");
      std::cout.rdbuf(real.rdbuf());
      queue_test<std::queue<int> >();

      std::ofstream mine("./diffs/ft_queue_test.txt");
      std::cout.rdbuf(mine.rdbuf());
      queue_test<ft::queue<int> >();
      std::cout.rdbuf(coutbuf);
    }
  }
  std::cout << "creating output is DONE, check \'diffs\' folder." << std::endl;
}
