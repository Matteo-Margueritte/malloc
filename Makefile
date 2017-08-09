##
## Makefile for malloc in /home/margue_m/rendu/malloc
## 
## Made by Mattéo Margueritte
## Login   <margue_m@epitech.net>
## 
## Started on  Mon Jan 23 18:45:40 2017 Mattéo Margueritte
## Last update Thu Feb  9 13:21:19 2017 Mattéo Margueritte
##

SRC	= malloc.c \
	  free.c \
	  other_alloc.c \
	  utils.c \
	  split.c

OBJS	= $(SRC:.c=.o)

NAME	= libmy_malloc.so

CFLAGS	+= -fpic -W -Wall -Wextra -Werror -Wpadded

LDFLAGS	+= -shared

RM	= rm -f

CC	= gcc

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
