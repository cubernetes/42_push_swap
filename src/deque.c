/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:34:41 by tischmid          #+#    #+#             */
/*   Updated: 2023/10/27 11:26:51 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	deque_push_left(t_deque *deque, t_deque_type data)
{
	t_deque_node	*new;

	if (deque->head)
	{
		new = malloc(sizeof(*new));
		new->data = data;
		new->next = deque->head;
		new->prev = deque->head->prev;
		deque->head->prev->next = new;
		deque->head->prev = new;
		deque->head = new;
	}
	else
	{
		deque->head = malloc(sizeof(*deque->head));
		deque->head->data = data;
		deque->head->next = deque->head;
		deque->head->prev = deque->head;
	}
}

void	deque_push_right(t_deque *deque, t_deque_type data)
{
	t_deque_node	*new;

	if (deque->head)
	{
		new = malloc(sizeof(*new));
		new->data = data;
		new->next = deque->head;
		new->prev = deque->head->prev;
		deque->head->prev->next = new;
		deque->head->prev = new;
	}
	else
	{
		deque->head = malloc(sizeof(*deque->head));
		deque->head->data = data;
		deque->head->next = deque->head;
		deque->head->prev = deque->head;
	}
}

t_deque_node	*deque_pop_right(t_deque *deque)
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

t_deque_node	*deque_pop_left(t_deque *deque)
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

void	deque_rotate(t_deque *deque, int n)
{
	if (!deque->head)
		return ;
	if (n > 0)
	{
		while (n--)
		{
			deque->head = deque->head->next;
		}
	}
	else if (n < 0)
		while (n++)
			deque->head = deque->head->prev;
}
