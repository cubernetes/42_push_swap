/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:35:28 by tischmid          #+#    #+#             */
/*   Updated: 2023/10/20 09:34:27 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;
typedef unsigned int		t_deque_type;

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

t_deque						list_to_deque(char **list);
t_deque						*deque_init(void);
void						deque_swap(t_deque *deque);
void						deque_print(t_deque *deque);
void						deque_free(t_deque *deque);

#endif
