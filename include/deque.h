/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:35:28 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/08 04:45:04 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

# include <stddef.h>

typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;
typedef int					t_deque_type;

struct						s_deque_node
{
	t_deque_node			*prev;
	t_deque_node			*next;
	t_deque_type			data;
};

struct						s_deque
{
	t_deque_node			*head;
};

t_deque_node				*deque_pop_bottom(t_deque *deque);
t_deque_node				*deque_pop_top(t_deque *deque);
void						deque_push_value_top(t_deque *deque,
								t_deque_type data);
void						deque_push_node_top(t_deque *deque,
								t_deque_node *node);
void						deque_push_value_bottom(t_deque *deque,
								t_deque_type data);
void						deque_push_node_bottom(t_deque *deque,
								t_deque_node *node);
void						deque_swap(t_deque *deque);
void						deque_rotate(t_deque *deque, int n);
t_deque						*deque_copy(t_deque *deque);
size_t						deque_size(t_deque *deque);
void						deque_sort(t_deque *deque, int(cmp)(t_deque_type,
									t_deque_type));
t_deque						*array_list_to_deque(char **array_list);
void						deque_print(t_deque *deque);
void						deque_free(t_deque *deque);
t_deque						*deque_init(void);
t_deque						*deque_slice(t_deque *deque, int start, int end,
								int step);
int							deque_index(t_deque *deque, t_deque_type data);
void						deque_extend_free(t_deque *deque_a,
								t_deque *deque_b);

#endif
