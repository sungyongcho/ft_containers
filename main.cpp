/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:19:00 by sucho             #+#    #+#             */
/*   Updated: 2021/05/21 07:20:50 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Containers.hpp"
#include "./tests/tests.hpp"

int main(void) {
  // vector_test<std::vector<int> >();
  // vector_test<ft::vector<int> >();

  // list_test<std::list<int> >();
  // list_test<ft::list<int> >();

  // map_test<std::map<char, int> >();
  // map_test<ft::map<char, int> >();

  // map_test_2<std::map<char, std::string> >();
  // map_test_2<ft::map<char, std::string> >();

  deque_test<std::deque<int> >();
  deque_test<ft::deque<int> >();

}
