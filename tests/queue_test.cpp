/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_test.cpp                                    :+:      :+:    :+:   */
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
    std::ofstream real("./diffs/std_queue_test.txt");
    std::cout.rdbuf(real.rdbuf());
    queue_test<std::queue<int> >();

    std::ofstream mine("./diffs/ft_queue_test.txt");
    std::cout.rdbuf(mine.rdbuf());
    queue_test<ft::queue<int> >();
    std::cout.rdbuf(coutbuf);
  }
}
