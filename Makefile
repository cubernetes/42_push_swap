# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 15:02:16 by tischmid          #+#    #+#              #
#    Updated: 2024/01/16 13:23:13 by tosuman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for Linux systems

NAME         = push_swap
LIBFT        = libft.a
LIBFT_       = $(patsubst lib%,%,$(patsubst %.a,%,$(LIBFT)))

unexport _SRC
_SRC         += push_swap.c
_SRC         += parsing.c
_SRC         += brute_force.c
_SRC         += ops1.c
_SRC         += ops2.c
_SRC         += ops3.c
_SRC         += printing.c
_SRC         += stack_management.c

_OBJ         = $(_SRC:.c=.o)
_HEADERS	 = push_swap.h
LIBFT_DIR    = ./libft

SRCDIR       = src
OBJDIR       = obj
INCLUDEDIR   = include
SRC          = $(addprefix $(SRCDIR)/,$(_SRC))
OBJ          = $(addprefix $(OBJDIR)/,$(_OBJ))
INCLUDE      = $(addprefix $(INCLUDEDIR)/,$(_HEADERS))

CC           = cc
CFLAGS       = -O0 -g3 -Wall -Wextra -Werror \
		       -std=c89 -pedantic -Wconversion
CPPFLAGS     = -I$(LIBFT_DIR) -I$(INCLUDEDIR)
LDFLAGS      = -L$(LIBFT_DIR)
LDLIBS       = -l$(LIBFT_)

all: $(NAME)

$(NAME): $(LIBFT_DIR)/$(LIBFT) $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $(OBJ) $(LDLIBS)
	$(MAKE)

$(LIBFT_DIR)/$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ): $(INCLUDE) | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) $@
	$(RM) $(OBJ)
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) $@
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
