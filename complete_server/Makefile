##
## Makefile for Bomberman in /Users/jeanle/Desktop/Bomberman/Recette
## 
## Made by LE Jean
## Login   <le_j@etna-alternance.net>
## 
## Started on  Thu Jun  2 12:11:04 2016 LE Jean
## Last update Sun Aug 14 13:50:15 2016 LE Jean
##

NAME		=	server
CC		=	gcc
CFLAGS		=	-W -Wall -Werror -Iincludes/

## SOURCES ##
SOURCES_DIR	=	./sources
SOURCES_SRCS	=	$(SOURCES_DIR)/main.c			\
			$(SOURCES_DIR)/init_server.c		\
			$(SOURCES_DIR)/start_coms.c		\
			$(SOURCES_DIR)/exit_server.c		\
			$(SOURCES_DIR)/protocol.c		\
			$(SOURCES_DIR)/manage_map.c		\
			$(SOURCES_DIR)/bonus_malus.c		\
			$(SOURCES_DIR)/positions_players.c	\
			$(SOURCES_DIR)/prohibit_client.c	\
			$(SOURCES_DIR)/bombs.c
OBJ		=	$(SOURCES_SRCS:%.c=%.o)

## LIBMY ##
LIBMY_DIR	=	./libmy
LIBMY_NAME	=	$(LIBMY_DIR)/libmy.a
LIBMY_SRCS	=	$(LIBMY_DIR)/my_putstr.c		\
			$(LIBMY_DIR)/my_putint.c		\
			$(LIBMY_DIR)/my_strcmp.c		\
			$(LIBMY_DIR)/my_strcat.c		\
			$(LIBMY_DIR)/my_memset.c
LIBMY_OBJS	=	$(LIBMY_SRCS:%.c=%.o)

RM		=	rm -f

$(NAME)		:	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBMY_DIR) -lmy

all		:	$(LIBMY_NAME) $(NAME)

$(LIBMY_NAME)	:	$(LIBMY_OBJS)
			ar -rcs $(LIBMY_NAME) $(LIBMY_OBJS)
			ranlib $(LIBMY_NAME)

.PHONY		:	clean
clean		:
			$(RM) $(OBJ) $(LIBMY_OBJS)

fclean		:	clean
			$(RM) $(NAME) $(LIBMY_NAME) $(LIBMY_DIR)/*~ $(SOURCES_DIR)/*~ ./includes/*~ *~

re		:	fclean all
