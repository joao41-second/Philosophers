# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 06:17:31 by jperpect          #+#    #+#              #
#    Updated: 2024/09/25 13:48:30 by jperpect         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLGS = -Wall -Wextra -Werror -pthread 

MAKEFLAGS += -s

FILES = ./src/main.c ./src/mandatory/start_thead.c \
./src/mandatory/mutex/mutex_gen.c src/mandatory/thead.c \
./src/utilitis/ft_atol.c ./src/mandatory/bar_men.c \
./src/utilitis/ft_math.c  src/utilitis/ft_forks.c \
./src/utilitis/ft_random.c \


SRCS = $(FILES:.c=.o)

LIB = ./libft/libft.a ./libft/libftprintf.a ./libft/get_next_line.a 

MINX_FLAG = -Lminilibx-linux -lmlx_Linux -lX11 -lXext

AR = ar rcs

CC = cc 

RM = rm -f

CAT = cat number.txt 

NAME = philo

COUNT_FILE = count.txt

COUNT = $(shell cat $(COUNT_FILE))


COUNT_FILE_EXISTS := $(wildcard $(COUNT_FILE))


	
#.SILENT:

all: $(NAME)
%.o:%.c 
	make file
	@cc -c -g $(FLGS) -o $@ $< && clear && echo $(COUNT) && sleep 0.2
	$(eval COUNT=$(shell echo $$(( $(COUNT) + 1 ))))
	# Salva o novo valor de COUNT no arquivo
	@echo $(COUNT) > $(COUNT_FILE)
$(NAME) : $(SRCS)
	cc $(FLGS) $(SRCS) -o $(NAME)
	echo "╔══════════════════════════╗"
	echo "║ ✅ Compiled Successfully!║"
	echo "╚══════════════════════════╝"	
	@rm -f $(COUNT_FILE)

file:
ifeq ($(COUNT_FILE_EXISTS),)
	@rm -f $(COUNT_FILE)
endif

bonus: $(OBJECT_B) $(NAME)
	ar rcs $(NAME) $^
	

clean:
	$(RM)  $(SRCS)
		@rm -f $(COUNT_FILE)

fclean: clean
	$(RM) $(NAME)
		@rm -f $(COUNT_FILE)


re: fclean all

exec:
	cc	-g $(FLGS)  $(SRCS) $(BONUS) -lbsd
		@rm -f $(COUNT_FILE)

norm: 
	 yes y|	python3 -m c_formatter_42 -c $(FILES)
		@rm -f $(COUNT_FILE)

normi:
	norminette $(FILES)
	cd ./libft && norminette
		@rm -f $(COUNT_FILE)
	


