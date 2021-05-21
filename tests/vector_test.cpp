/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
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
    std::ofstream real("./diffs/std_vector_test.txt");
    std::cout.rdbuf(real.rdbuf());
    vector_test<std::vector<int> >();

    std::ofstream mine("./diffs/ft_vector_test.txt");
    std::cout.rdbuf(mine.rdbuf());
    vector_test<ft::vector<int> >();
    std::cout.rdbuf(coutbuf);
  }
}
