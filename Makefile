# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 15:02:16 by tischmid          #+#    #+#              #
#    Updated: 2024/01/16 19:13:38 by tosuman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for Linux systems
# Source Lines of Code (including libft): 2838
# Source Lines of Code (excluding libft, including deque code): 1568
# Source Lines of Code (excluding libft): 692

NAME            := push_swap
BONUS           := checker
LIBFT           := libft.a
LIBFT_          := $(patsubst lib%,%,$(patsubst %.a,%,$(LIBFT)))

unexport _SRC
_SRC           += push_swap.c
_SRC           += parsing.c
_SRC           += brute_force.c
_SRC           += ops1.c
_SRC           += ops2.c
_SRC           += ops3.c
_SRC           += printing.c
_SRC           += stack_management.c

unexport _BONUS_SRC
_BONUS_SRC     += checker.c
_BONUS_SRC     += parsing.c
_BONUS_SRC     += ops1.c
_BONUS_SRC     += ops2.c
_BONUS_SRC     += ops3.c

_OBJ           := $(_SRC:.c=.o)
_BONUS_OBJ     := $(_BONUS_SRC:.c=.o)
_HEADERS       := push_swap.h
_BONUS_HEADERS := checker.h

SRCDIR         := src
OBJDIR         := obj
INCLUDEDIR     := include
LIBFT_DIR      := ./libft
SRC            := $(addprefix $(SRCDIR)/,$(_SRC))
BONUS_SRC      := $(addprefix $(SRCDIR)/,$(_BONUS_SRC))
OBJ            := $(addprefix $(OBJDIR)/,$(_OBJ))
BONUS_OBJ      := $(addprefix $(OBJDIR)/,$(_BONUS_OBJ))
INCLUDE        := $(addprefix $(INCLUDEDIR)/,$(_HEADERS))

CC             := cc
RM             := /bin/rm -f
CFLAGS         := -O3 -Wall -Wextra -Werror \
                  -std=c89 -pedantic -Wconversion
CPPFLAGS       := -I$(LIBFT_DIR) -I$(INCLUDEDIR)
LDFLAGS        := -L$(LIBFT_DIR)
LDLIBS         := -l$(LIBFT_)

all: $(NAME) bonus

# mandatory part
$(NAME): $(LIBFT_DIR)/$(LIBFT) $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $(OBJ) $(LDLIBS)
	$(MAKE)

$(OBJ): $(INCLUDE) | $(OBJDIR)

# bonus part
$(BONUS): $(LIBFT_DIR)/$(LIBFT) $(BONUS_OBJ)
	$(CC) -o $@ $(LDFLAGS) $(BONUS_OBJ) $(LDLIBS)
	$(MAKE)

$(BONUS_OBJ): $(INCLUDE) | $(OBJDIR)

# both
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT_DIR)/$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

bonus: $(BONUS)

clean:
	$(MAKE) -C $(LIBFT_DIR) $@
	$(RM) $(OBJ)
	$(RM) $(BONUS_OBJ)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) $@
	$(RM) $(NAME)
	$(RM) $(BONUS)

re: fclean all

.PHONY: re fclean clean all bonus
