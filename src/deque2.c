/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_extra2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:25:38 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/05 01:36:32 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"
#include <stddef.h>

t_deque	*deque_copy(t_deque *deque)
{
	t_deque			*new_deque;
	t_deque_node	*orig_head;
	t_deque_node	*head;

	new_deque = deque_init();
	if (!deque->head)
		return (new_deque);
	orig_head = deque->head;
	head = orig_head;
	deque_push_right(new_deque, (t_deque_type)head->data);
	head = head->next;
	while (head != orig_head)
	{
		deque_push_right(new_deque, (t_deque_type)head->data);
		head = head->next;
	}
	return (new_deque);
}

size_t	deque_size(t_deque *deque)
{
	t_deque_node	*orig_head;
	t_deque_node	*head;
	size_t			size;

	orig_head = deque->head;
	head = orig_head;
	if (!head)
		return (0);
	head = head->next;
	size = 1;
	while (head != orig_head)
	{
		head = head->next;
		++size;
	}
	return (size);
}

void	deque_sort(t_deque *deque, int(cmp)(t_deque_type, t_deque_type))
{
	size_t			n;
	size_t			orig_n;
	size_t			i;

	orig_n = deque_size(deque);
	n = orig_n;
	if (!n)
		return ;
	while (--n)
	{
		i = orig_n;
		while (--i)
		{
			if (cmp(deque->head->data, deque->head->next->data))
				deque_swap(deque);
			deque->head = deque->head->next;
		}
		deque_rotate(deque, 1);
	}
}
