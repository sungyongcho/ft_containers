/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 20:20:02 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 20:20:44 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

int main(void) {
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
