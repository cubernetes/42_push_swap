/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:19:44 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/06 16:40:42 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"
#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	push_buckets(t_deque *deque_a, t_deque *deque_b, size_t bucket_size)
{
	t_deque	*sorted_deque;
	t_deque	*slice;
	size_t	n;
	int		idx;

	sorted_deque = deque_copy(deque_a);
	deque_sort(sorted_deque, cmp_int_asc);
	if (bucket_size < 1)
		bucket_size = 1;
	n = bucket_size;
	slice = deque_slice(sorted_deque, n - bucket_size, n, 1);
	while (deque_a->head)
	{
		idx = deque_index(slice, deque_a->head->data);
		if (idx != -1)
		{
			ft_dprintf(1, "pb\n");
			deque_push_node_right(deque_b, deque_pop_left(deque_a));
			deque_rotate(slice, idx);
			free(deque_pop_left(slice));
			if (deque_size(slice) == 0)
			{
				n += bucket_size;
				slice = deque_slice(sorted_deque, n - bucket_size, n, 1);
			}
		}
		else
		{
			ft_dprintf(1, "ra\n");
			deque_rotate(deque_a, 1);
		}
	}
}

int	deque_argmax(t_deque *deque)
{
	t_deque_node	*orig_head;
	t_deque_node	*head;
	t_deque_type	max_value;
	int				max_idx;
	int				idx;

	orig_head = deque->head;
	head = orig_head;
	if (!head)
		return (-1);
	idx = 0;
	max_idx = idx;
	max_value = head->data;
	head = head->next;
	while (head != orig_head)
	{
		++idx;
		if (head->data > max_value)
		{
			max_value = head->data;
			max_idx = idx;
		}
		head = head->next;
	}
	return (max_idx);
}

void	push_back_sorted(t_deque *deque_a, t_deque *deque_b)
{
	int	idx_max;

	(void)deque_a;
	(void)idx_max;
	while (deque_b->head)
	{
		idx_max = deque_argmax(deque_b);
		/* deque_b->head = deque_b->head->next; */
	}
}

void	push_swap(t_deque *deque_a)
{
	t_deque	*deque_b;
	size_t	bucket_size;

	deque_b = deque_init();
	bucket_size = deque_size(deque_a) / 4;
	push_buckets(deque_a, deque_b, bucket_size);
	/* push_back_sorted(deque_a, deque_b); */
}

int	main(int argc, char **argv)
{
	t_deque	*deque_a;

	deque_a = parse_args(argc, argv);
	push_swap(deque_a);
	deque_free(deque_a);
	return (0);
}
