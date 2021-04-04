# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 02:28:53 by sucho             #+#    #+#              #
#    Updated: 2021/04/01 02:43:59 by sucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_containers_test

CXX			=	clang++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98
RM			=	rm -f

SRCS		=	main.cpp
OBJS		=	$(SRCS:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
					$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
					$(RM) $(OBJS)

fclean:			clean
					$(RM) $(NAME)

re:				fclean $(NAME)

test:			all
				./$(NAME)


.PHONY:			all clean fclean re
