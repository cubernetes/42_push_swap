/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_popping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 01:44:47 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/08 04:04:31 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"
#include <stddef.h>

t_deque_node	*deque_pop_bottom(t_deque *deque)
{
	t_deque_node	*head;
	t_deque_node	*prev;
	t_deque_node	*prev_prev;

	head = deque->head;
	prev = deque->head->prev;
	prev_prev = prev->prev;
	if (!head)
		return (NULL);
	if (head == head->next)
		deque->head = NULL;
	else
	{
		deque->head->prev = prev_prev;
		prev_prev->next = deque->head;
	}
	prev->next = NULL;
	prev->prev = NULL;
	return (prev);
}

t_deque_node	*deque_pop_top(t_deque *deque)
{
	t_deque_node	*prev;
	t_deque_node	*head;
	t_deque_node	*next;

	head = deque->head;
	prev = head->prev;
	next = head->next;
	if (!head)
		return (NULL);
	if (head == head->next)
		deque->head = NULL;
	else
	{
		deque->head = next;
		next->prev = prev;
		prev->next = next;
	}
	head->next = NULL;
	head->prev = NULL;
	return (head);
}

