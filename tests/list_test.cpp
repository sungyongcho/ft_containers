/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.cpp                                    :+:      :+:    :+:   */
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
    std::ofstream real("./diffs/std_list_test.txt");
    std::cout.rdbuf(real.rdbuf());
    list_test<std::list<int> >();

    std::ofstream mine("./diffs/ft_list_test.txt");
    std::cout.rdbuf(mine.rdbuf());
    list_test<ft::list<int> >();
    std::cout.rdbuf(coutbuf);
  }
}
