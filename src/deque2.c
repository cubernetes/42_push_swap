/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:25:38 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/21 21:06:35 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"
#include <stddef.h>
#include <limits.h>

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
	deque_push_value_bottom(new_deque, (t_deque_type)head->data);
	head = head->next;
	while (head != orig_head)
	{
		deque_push_value_bottom(new_deque, (t_deque_type)head->data);
		head = head->next;
	}
	return (new_deque);
}

void	deque_sort(t_deque *deque, int(cmp)(t_deque_type, t_deque_type))
{
	size_t	n;
	size_t	orig_n;
	size_t	i;

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

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

unsigned int	ft_abs(int a)
{
	if (a < 0)
		return ((unsigned int)(-a));
	return (a);
}

t_deque	*deque_slice(t_deque *deque, int start, int end, int step)
{
	t_deque_node	*head;
	t_deque			*slice;
	int				size;
	int				orig_start;

	slice = deque_init();
	size = (int)deque_size(deque);
	orig_start = start;
	if (start < 0)
		start = ft_max(start + size, 0);
	start = ft_min(start, size - 1);
	if (end < 0)
		end = ft_max(end + size, 0);
	end = ft_min(end, size);
	if (orig_start < 0 && end == 0 && step > 0)
		end = size;
	else if ((end - start) * step <= 0)
		return (slice);
		/* return (slice->size = , slice); */
	head = deque->head;
	size = start;
	while (size--)
		head = head->next;
	while ((step > 0 && start < end) || (step < 0 && start > end))
	{
		deque_push_value_bottom(slice, head->data);
		size = ft_abs(step);
		while (size--)
		{
			if (step > 0)
				head = head->next;
			else
				head = head->prev;
		}
		start += step;
	}
	return (slice);
}

#include "../libft/libft.h"
int	deque_index(t_deque *deque, t_deque_type data)
{
	t_deque_node	*orig_head;
	t_deque_node	*head;
	int				idx;

	orig_head = deque->head;
	head = orig_head;
	if (!head)
		return (-1);
	if (head->data == data)
		return (0);
	head = head->next;
	idx = 1;
	while (head != orig_head)
	{
		if (head->data == data)
			return (idx);
		++idx;
		head = head->next;
	}
	return (-1);
}
