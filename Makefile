# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 20:08:27 by sucho             #+#    #+#              #
#    Updated: 2021/05/21 21:14:11 by sucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cpp_module_tests

CXX				=	clang++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98 -pedantic
DEBUG			=	-g -fsanitize=address
RM				=	rm -f

SRCS			=	main.cpp

VECTOR			=	vector
LIST			=	list
STACK			=	stack
QUEUE			=	queue
MAP				=	map
DEQUE			=	deque

DIFF_DIR		=	./diffs
TESTS_DIR		=	tests
TEST_SUFFIX		=	_test.cpp
OUTPUT_SUFFIX	=	_test.txt
DIFF_SCRIPT		=	./diff_script.sh

OBJS			=	$(SRCS:.cpp=.o)

all:				$(NAME)

$(NAME):			$(OBJS)
						@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
						@./$(NAME)
						@rm $(NAME)

$(VECTOR):			$(TESTS_DIR)/$(VECTOR)$(TEST_SUFFIX)
						@$(CXX) $(CXXFLAGS) $(TESTS_DIR)/$(VECTOR)$(TEST_SUFFIX) -o $(NAME)
						@./$(NAME)
						@echo "[$(VECTOR)]"
						@$(DIFF_SCRIPT) $(DIFF_DIR)/std_vector$(OUTPUT_SUFFIX) $(DIFF_DIR)/ft_vector$(OUTPUT_SUFFIX)
						@rm $(NAME)

$(LIST):			$(TESTS_DIR)/$(LIST)$(TEST_SUFFIX)
						@$(CXX) $(CXXFLAGS) $(TESTS_DIR)/$(LIST)$(TEST_SUFFIX) -o $(NAME)
						@./$(NAME)
						@echo "[$(LIST)]"
						@$(DIFF_SCRIPT) $(DIFF_DIR)/std_list$(OUTPUT_SUFFIX) $(DIFF_DIR)/ft_list$(OUTPUT_SUFFIX)
						@rm $(NAME)

$(MAP):				$(TESTS_DIR)/$(MAP)$(TEST_SUFFIX)
						@$(CXX) $(CXXFLAGS) $(TESTS_DIR)/$(MAP)$(TEST_SUFFIX) -o $(NAME)
						@./$(NAME)
						@echo "[$(MAP)]"
						@$(DIFF_SCRIPT) $(DIFF_DIR)/std_map$(OUTPUT_SUFFIX) $(DIFF_DIR)/ft_map$(OUTPUT_SUFFIX)
						@rm $(NAME)

$(DEQUE):			$(TESTS_DIR)/$(DEQUE)$(TEST_SUFFIX)
						@$(CXX) $(CXXFLAGS) $(TESTS_DIR)/$(DEQUE)$(TEST_SUFFIX) -o $(NAME)
						@./$(NAME)
						@echo "[$(DEQUE)]"
						@$(DIFF_SCRIPT) $(DIFF_DIR)/std_deque$(OUTPUT_SUFFIX) $(DIFF_DIR)/ft_deque$(OUTPUT_SUFFIX)
						@rm $(NAME)

$(STACK):			$(TESTS_DIR)/$(STACK)$(TEST_SUFFIX)
						@$(CXX) $(CXXFLAGS) $(TESTS_DIR)/$(STACK)$(TEST_SUFFIX) -o $(NAME)
						@./$(NAME)
						@echo "[$(STACK)]"
						@$(DIFF_SCRIPT) $(DIFF_DIR)/std_stack$(OUTPUT_SUFFIX) $(DIFF_DIR)/ft_stack$(OUTPUT_SUFFIX)
						@rm $(NAME)

$(QUEUE):			$(TESTS_DIR)/$(QUEUE)$(TEST_SUFFIX)
						@$(CXX) $(CXXFLAGS) $(TESTS_DIR)/$(QUEUE)$(TEST_SUFFIX) -o $(NAME)
						@./$(NAME)
						@echo "[$(QUEUE)]"
						@$(DIFF_SCRIPT) $(DIFF_DIR)/std_queue$(OUTPUT_SUFFIX) $(DIFF_DIR)/ft_queue$(OUTPUT_SUFFIX)
						@rm $(NAME)

clean:
						$(RM) $(OBJS)

fclean:				clean
						$(RM) $(NAME)

re:					fclean $(NAME)

test:				$(VECTOR) $(LIST) $(MAP) $(DEQUE) $(STACK) $(QUEUE)

debug:				$(OBJS)
						@$(CXX) $(CXXFLAGS) $(DEBUG) -o $(NAME) $(OBJS)
						@./$(NAME)
						@rm $(NAME)

.PHONY:			all clean fclean re

