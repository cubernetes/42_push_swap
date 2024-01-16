/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:19:44 by tischmid          #+#    #+#             */
/*   Updated: 2024/01/16 13:09:09 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <limits.h>
#include <stdlib.h>

void	push_bucket(t_deque *deque_a, t_deque *deque_b, t_deque *sorted_deque,
		t_bucket_data *d)
{
	if (deque_index(d->slice, deque_a->head->data) != -1)
	{
		deque_rotate(d->slice, deque_index(d->slice, deque_a->head->data));
		(free(deque_pop_top(d->slice)), deque_push_value_bottom(d->ops, OP_PB));
		deque_push_node_top(deque_b, deque_pop_top(deque_a));
		if (d->slice->size == 0)
		{
			d->buck_siz = (size_t)ft_max((int)((double)d->buck_siz
						* d->factor), 1);
			(deque_free(d->slice), d->n += d->buck_siz, deque_free(d->h_slice));
			d->slice = deque_slice(sorted_deque, (int)(d->n - d->buck_siz),
					(int)d->n, 1);
			d->h_slice = deque_slice(sorted_deque, (int)(d->n - d->buck_siz),
					(int)(d->n - d->buck_siz / 2), 1);
		}
	}
	else
	{
		if (deque_b->head && deque_index(d->h_slice, deque_b->head->data) != -1)
			(deque_push_value_bottom(d->ops, OP_RR), deque_rotate(deque_a, 1),
				deque_rotate(deque_b, 1));
		else
			(deque_push_value_bottom(d->ops, OP_RA), deque_rotate(deque_a, 1));
	}
}

t_deque	*push_back_sorted(t_deque *deque_a, t_deque *deque_b)
{
	t_deque	*ops;
	int		idx_max;

	ops = deque_init();
	while (deque_b->head)
	{
		while (bottom_element_of_a_should_be_rotated(deque_a, deque_b))
			(deque_push_value_bottom(ops, OP_RRA), deque_rotate(deque_a, -1));
		deque_argmax(deque_b, &idx_max);
		if ((int)deque_b->size - idx_max < idx_max)
			rev_rotate_b(idx_max, deque_b, ops);
		else
			rotate_b(idx_max, deque_a, deque_b, ops);
		deque_push_value_bottom(ops, OP_PA);
		deque_push_node_top(deque_a, deque_pop_top(deque_b));
	}
	while (bottom_element_of_a_should_be_rotated(deque_a, deque_b))
	{
		deque_push_value_bottom(ops, OP_RRA);
		deque_rotate(deque_a, -1);
	}
	return (ops);
}

void	push_swap(int *min_ops, t_deque **ops, t_deque *deques[3],
		t_bucket_data *d)
{
	(deque_free(*ops), *ops = deque_init());
	(deque_free(deques[0]), deques[0] = deque_copy(deques[2]));
	(deque_free(deques[1]), deques[1] = deque_init());
	deque_extend_free(*ops, push_buckets(deques[0], deques[1],
			*d));
	deque_extend_free(*ops, push_back_sorted(deques[0], deques[1]));
	if ((*ops)->size < (size_t)(*min_ops))
	{
		d->min_buck_siz = d->buck_siz;
		d->bst_factor = d->factor;
		*min_ops = (int)(*ops)->size;
	}
	d->factor -= 0.01;
}

/* 500 -> 80-120 and 0.79-0.91 */
t_deque	*push_swap_benchmark(t_deque *deque_a)
{
	t_deque			*deques[3];
	t_deque			*ops;
	int				min_ops;
	t_bucket_data	d;

	min_ops = INT_MAX;
	(free(NULL), deques[0] = deque_init(), deques[1] = deque_init());
	deques[2] = deque_a;
	(free(NULL), d.buck_siz = 0, d.min_buck_siz = 1);
	ops = deque_init();
	d.bst_factor = 1.0;
	while (++d.buck_siz < (size_t)ft_min(120, ft_max(80,
				(int)deque_a->size)))
	{
		d.factor = 0.91;
		while (d.factor > 0.79)
			push_swap(&min_ops, &ops, deques, &d);
	}
	(deque_free(ops), ops = deque_init(), d.buck_siz = d.min_buck_siz);
	(deque_free(deques[0]), deques[0] = deque_copy(deque_a));
	(deque_free(deques[1]), deques[1] = deque_init(), d.factor = d.bst_factor);
	deque_extend_free(ops, push_buckets(deques[0], deques[1], d));
	deque_extend_free(ops, push_back_sorted(deques[0], deques[1]));
	(deque_free(deques[0]), deque_free(deques[1]));
	return (deque_free(deque_a), ops);
}

int	main(int argc, char **argv)
{
	t_deque	*deque_a;
	t_deque	*ops;
	t_deque	*sorted_deque;

	deque_a = parse_args(argc, argv);
	sorted_deque = deque_copy(deque_a);
	deque_sort(sorted_deque, cmp_int_asc);
	if (deque_equal(deque_a, sorted_deque) && (deque_free(deque_a), 1))
		return (deque_free(sorted_deque), 0);
	if (deque_a->size <= MAX_BRUTE_FORCE)
		ops = brute_force(deque_a);
	else
		ops = push_swap_benchmark(deque_a);
	print_ops(ops);
	deque_free(ops);
	deque_free(sorted_deque);
	return (0);
}
