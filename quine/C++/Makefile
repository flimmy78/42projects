#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/16 18:53:45 by gbourgeo          #+#    #+#              #
#    Updated: 2017/12/17 20:11:21 by gbourgeo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = Colleen
NAME2 = Grace
NAME3 = Sully

SRCS = Colleen.cpp
SRCS2 = Grace.cpp
SRCS3 = Sully.cpp

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
OBJS2 = $(addprefix $(OBJS_DIR), $(SRCS2:.cpp=.o))
OBJS3 = $(addprefix $(OBJS_DIR), $(SRCS3:.cpp=.o))
OBJS_DIR = obj/

FLAGS = -Wall -Werror -Wextra -std=c++11

all: $(OBJS_DIR) $(NAME) $(NAME2) $(NAME3) 

$(OBJS_DIR):
	@mkdir -p $@

$(NAME): $(OBJS)
	$(CXX) -o $@ $^

$(NAME2): $(OBJS2)
	$(CXX) $(FLAGS) -o $@ $^

$(NAME3): $(OBJS3)
	$(CXX) $(FLAGS) -o $@ $^

$(OBJS_DIR)%.o: %.cpp
	$(CXX) $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME) $(NAME2) $(NAME3)

re: fclean all

del: fclean
	rm -rf Grace_kid.c
	rm -rf Sully_*
