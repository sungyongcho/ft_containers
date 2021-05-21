/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 20:20:02 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 20:20:44 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/containers.hpp"
#include "tests.hpp"

int main(void) {
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
