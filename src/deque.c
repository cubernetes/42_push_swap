/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:34:41 by tischmid          #+#    #+#             */
/*   Updated: 2023/10/19 14:35:19 by tischmid         ###   ########.fr       */
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

t_deque_node	*deque_pop_right(t_deque *deque)
{
	t_deque_node	*prev;
	t_deque_node	*prev_prev;

	if (!deque->head)
		return (NULL);
	if (deque->head == deque->head->next)
	{
		prev = deque->head;
		deque->head = NULL;
	}
	else
	{
		prev = deque->head->prev;
		prev_prev = prev->prev;
		deque->head->prev = prev_prev;
		prev_prev->next = deque->head;
		if (deque->head->next == prev)
		{
			deque->head->next = prev_prev;
			prev_prev->prev = deque->head;
		}
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
	if (!head)
		return (NULL);
	if (head == head->next)
		deque->head = NULL;
	else
	{
		next = head->next;
		prev = head->prev;
		deque->head->prev = prev_prev;
		prev_prev->next = deque->head;
		if (deque->head->next == prev)
		{
			deque->head->next = prev_prev;
			prev_prev->prev = deque->head;
		}
	}
	head->next = NULL;
	head->prev = NULL;
	return (head);
}

int	main(void)
{
	t_deque	*deque_a;

	deque_a = deque_init();
	deque_push_right(deque_a, 1);
	deque_push_right(deque_a, 2);
	deque_push_right(deque_a, 3);
	deque_push_left(deque_a, 5);
	deque_push_left(deque_a, 4);
	deque_rotate(deque_a, 2);
	deque_swap(deque_a);
	deque_swap(deque_a);
	/* ft_printf("%d\n", deque_pop_right(deque_a)->data); */
	/* ft_printf("%d\n", deque_pop_right(deque_a)->data); */
	/* ft_printf("%d\n", deque_pop_right(deque_a)->data); */
	/* ft_printf("%d\n", deque_pop_right(deque_a)->data); */
	/* ft_printf("%d\n", deque_pop_right(deque_a)->data); */
	print_deque(deque_a);
	return (0);
}
