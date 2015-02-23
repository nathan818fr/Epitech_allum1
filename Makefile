##
## Makefile for  in /repo/Epitech/Empty_Project
## 
## Made by Nathan Poirier
## Login   <poirie_n@epitech.net>
## 
## Started on  Tue Feb 10 16:21:13 2015 Nathan Poirier
## Last update Sun Feb 22 19:15:50 2015 Nathan Poirier
##

SRCS		= main.c					\
		  draw.c					\
		  termcap/tc_init.c				\
		  termcap/tc_read.c				\
		  termcap/tc_sig.c				\
		  termcap/tc_fct.c				\
		  termcap/tc_verify.c				\
		  menu/menu.c					\
		  menu/menu_draw.c				\
		  menu/menu_draw_play.c				\
		  menu/menu_draw_list.c				\
		  game/game_init.c				\
		  game/game_line.c				\
		  game/game_player.c				\
		  game/game_loop.c				\
		  game/game_loop_keyboard.c			\
		  game/game_loop_computer.c			\
		  game/game_draw.c				\
		  game/game_draw2.c				\
		  game/ai/game_ai.c				\
		  game/ai/game_ai_best.c			\
		  game/ai/game_ai_btable.c

OBJS		= $(addprefix src/, $(SRCS:.c=.o))

PROJECT		= CPE_2014_allum1

NAME		= allum1

RM		= rm -f

CC		= gcc -g3

LIBS		= -Llib/
LIBS		+= -Ilib/C_Lib_MyUtils/include -Llib/C_Lib_MyUtils -lmyutils
LIBS		+= -lncurses

CFLAGS		= -W -Wall -Wextra
CFLAGS		+= -Wno-variadic-macros -Wno-unused-parameter
CFLAGS		+= -ansi -pedantic
CFLAGS		+= -Ofast
CFLAGS		+= -Iinclude/
CFLAGS		+= -D_BSD_SOURCE -D_POSIX_SOURCE
CFLAGS		+= $(LIBS)

LDFLAGS		= $(LIBS)

LIB_MYUTILS	= lib/C_Lib_MyUtils/libmyutils.a
LIB_MYUTILS_MK	= make -C lib/C_Lib_MyUtils/

$(PROJECT):	$(LIB_MYUTILS) $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIB_MYUTILS):
		$(LIB_MYUTILS_MK)

all:		$(PROJECT)

clean:
		$(RM) $(OBJS)
		$(LIB_MYUTILS_MK) clean

fclean:		clean
		$(RM) $(NAME)
		$(LIB_MYUTILS_MK) fclean

re:		fclean all

.PHONY: re fclean clean all $(PROJECT)
