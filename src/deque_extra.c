/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:25:38 by tischmid          #+#    #+#             */
/*   Updated: 2023/10/20 09:43:40 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_deque	list_to_deque(char **list)
{
	t_deque	deque;

	return (deque);
}

void	deque_print(t_deque *deque)
{
	t_deque_node	*head;
	t_deque_node	*orig_head;

	head = deque->head;
	orig_head = head;
	if (head)
		ft_printf("%d", head->data);
	else
	{
		ft_printf("Empty deque.\n");
		return ;
	}
	while (head->next != orig_head)
	{
		ft_printf(" -> %d", head->next->data);
		head = head->next;
	}
	ft_printf("\n");
}

void	deque_free(t_deque *deque)
{
	t_deque_node	*head;
	t_deque_node	*tail;

	head = deque->head;
	if (!head)
		return ;
	tail = head->prev;
	while (head != tail)
	{
		free(head);
		head = head->next;
	}
	free(head);
	free(deque);
}

t_deque	*deque_init(void)
{
	t_deque	*deque;

	deque = malloc(sizeof(*deque));
	deque->head = NULL;
	return (deque);
}

void	deque_swap(t_deque *deque)
{
	t_deque_node	*orig_prev;
	t_deque_node	*orig_head;
	t_deque_node	*orig_next;
	t_deque_node	*orig_next_next;

	if (!deque->head)
		return ;
	orig_prev = deque->head->prev;
	orig_head = deque->head;
	orig_next = orig_head->next;
	orig_next_next = orig_next->next;
	deque->head = orig_next;
	orig_prev->next = orig_next;
	orig_head->next = orig_next_next;
	orig_head->prev = orig_next;
	orig_next->next = orig_head;
	orig_next->prev = orig_prev;
	orig_next_next->prev = orig_head;
}
