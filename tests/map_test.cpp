/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                    :+:      :+:    :+:   */
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
