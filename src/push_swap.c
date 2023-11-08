/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:19:44 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/08 05:39:05 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"
#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	print_op(char *op, int amount)
{
	int	count;

	count = 0;
	while (amount--)
		count += ft_printf("%s\n", op);
	return (count);
}

int	flush_ops(t_deque *ops)
{
	static char	*ops_strings[11] = {"ra", "rra", "rb", "rrb", "rr", "rrr", "sa",
			"sb", "ss", "pa", "pb"};
	int			count;

	count = 0;
	while (ops->head)
	{
		count += print_op(ops_strings[ops->head->data], 1);
		free(deque_pop_top(ops));
	}
	deque_free(ops);
	return (count);
}

t_deque	*push_buckets(t_deque *deque_a, t_deque *deque_b, size_t bucket_size)
{
	t_deque	*sorted_deque;
	t_deque	*slice;
	t_deque	*half_slice;
	t_deque	*ops;
	size_t	n;
	int		idx;

	sorted_deque = deque_copy(deque_a);
	deque_sort(sorted_deque, cmp_int_asc);
	ops = deque_init();
	if (bucket_size < 1)
		bucket_size = 1;
	n = bucket_size;
	slice = deque_slice(sorted_deque, n - bucket_size, n, 1);
	half_slice = deque_slice(sorted_deque, n - bucket_size, n - bucket_size / 2, 1);
	while (deque_a->head)
	{
		idx = deque_index(slice, deque_a->head->data);
		if (idx != -1)
		{
			deque_push_value_bottom(ops, OP_PB);
			deque_push_node_top(deque_b, deque_pop_top(deque_a));
			deque_rotate(slice, idx);
			free(deque_pop_top(slice));
			if (deque_size(slice) == 0)
			{
				n += bucket_size;
				slice = deque_slice(sorted_deque, n - bucket_size, n, 1);
				half_slice = deque_slice(sorted_deque, n - bucket_size, n - bucket_size / 2, 1);
			}
		}
		else
		{
			if (deque_b->head && deque_index(half_slice, deque_b->head->data)
				!= -1)
				(deque_push_value_bottom(ops, OP_RR), deque_rotate(deque_a,
						1), deque_rotate(deque_b, 1));
			else
				(deque_push_value_bottom(ops, OP_RA), deque_rotate(deque_a,
						1));
		}
	}
	deque_free(slice);
	deque_free(half_slice);
	return (ops);
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

t_deque	*push_back_sorted(t_deque *deque_a, t_deque *deque_b)
{
	int		idx_max;
	int		i;
	size_t	size;
	t_deque	*ops;

	ops = deque_init();
	while (deque_b->head)
	{
		idx_max = deque_argmax(deque_b);
		size = deque_size(deque_b);
		i = -1;
		if (size - idx_max < idx_max && (deque_rotate(deque_b, -(size
						- idx_max)), 1))
		{
			while (++i < size - idx_max)
				deque_push_value_bottom(ops, OP_RRB);
		}
		else if ((deque_rotate(deque_b, idx_max), 1))
		{
			while (++i < idx_max)
				deque_push_value_bottom(ops, OP_RB);
		}
		deque_push_value_bottom(ops, OP_PA);
		deque_push_node_top(deque_a, deque_pop_top(deque_b));
	}
	return (ops);
}

void	push_swap(t_deque *deque_a)
{
	t_deque	*deques[2];
	t_deque	*ops;
	size_t	min_bucket_size;
	size_t	bucket_size;
	int		min_ops;

	min_ops = INT_MAX;
	deques[0] = deque_init();
	deques[1] = deque_init();
	bucket_size = 0;
	min_bucket_size = 1;
	ops = deque_init();
	while (++bucket_size < ft_min(60, deque_size(deque_a)))
	{
		deque_free(ops);
		deque_free(deques[0]);
		deque_free(deques[1]);
		ops = deque_init();
		deques[0] = deque_copy(deque_a);
		deques[1] = deque_init();
		deque_extend_free(ops, push_buckets(deques[0], deques[1], bucket_size));
		deque_extend_free(ops, push_back_sorted(deques[0], deques[1]));
		if (deque_size(ops) < min_ops)
		{
			min_bucket_size = bucket_size;
			min_ops = deque_size(ops);
		}
	}
	deque_free(ops);
	deque_free(deques[0]);
	deque_free(deques[1]);
	ops = deque_init();
	deques[0] = deque_copy(deque_a);
	deques[1] = deque_init();
	deque_extend_free(ops, push_buckets(deques[0], deques[1], min_bucket_size));
	deque_extend_free(ops, push_back_sorted(deques[0], deques[1]));
	flush_ops(ops);
}

int	main(int argc, char **argv)
{
	t_deque	*deque_a;

	deque_a = parse_args(argc, argv);
	push_swap(deque_a);
	deque_free(deque_a);
	return (0);
}
