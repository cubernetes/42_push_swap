/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:09:05 by tosuman           #+#    #+#             */
/*   Updated: 2024/01/16 13:10:03 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"

t_deque	*push_buckets(t_deque *deque_a, t_deque *deque_b, t_bucket_data d)
{
	t_deque			*sorted_deque;

	sorted_deque = deque_copy(deque_a);
	deque_sort(sorted_deque, cmp_int_asc);
	d.ops = deque_init();
	if (d.buck_siz < 1)
		d.buck_siz = 1;
	d.n = d.buck_siz;
	d.slice = deque_slice(sorted_deque, (int)(d.n - d.buck_siz),
			(int)d.n, 1);
	d.h_slice = deque_slice(sorted_deque, (int)(d.n - d.buck_siz),
			(int)(d.n - d.buck_siz / 2), 1);
	while (deque_a->head)
		push_bucket(deque_a, deque_b, sorted_deque, &d);
	deque_free(d.slice);
	deque_free(d.h_slice);
	deque_free(sorted_deque);
	return (d.ops);
}

int	b_top_is_bigger_than_a_bottom(t_deque *deque_a, t_deque *deque_b)
{
	t_deque_type	b_top;
	t_deque_type	a_bottom;
	t_deque_type	a_max;
	t_deque_type	max_idx;
	t_deque_type	max;

	if (!deque_a->head)
		return (1);
	if (!deque_b->head)
		return (0);
	b_top = deque_b->head->data;
	a_bottom = deque_a->head->prev->data;
	a_max = deque_argmax(deque_a, &max_idx);
	max = ft_max(a_max, deque_argmax(deque_b, &max_idx));
	if (b_top > a_bottom || a_bottom == max)
		return (1);
	return (0);
}

int	bottom_element_of_a_should_be_rotated(t_deque *deque_a, t_deque *deque_b)
{
	t_deque_type	a_bottom;
	t_deque_type	a_max;
	t_deque_type	b_max;
	t_deque_type	max_idx;
	t_deque_type	max;

	if (!deque_a->head)
		return (0);
	a_bottom = deque_a->head->prev->data;
	a_max = deque_argmax(deque_a, &max_idx);
	b_max = deque_argmax(deque_b, &max_idx);
	max = ft_max(a_max, b_max);
	if (a_bottom >= b_max && a_bottom != max)
		return (1);
	if (max_idx == -1 && a_bottom <= deque_a->head->data)
		return (1);
	return (0);
}

void	rev_rotate_b(int idx_max, t_deque *deque_b, t_deque *ops)
{
	int	i;

	i = -1;
	while (++i < (int)deque_b->size - idx_max)
	{
		deque_push_value_bottom(ops, OP_RRB);
		deque_rotate(deque_b, -1);
	}
}

void	rotate_b(int idx_max, t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	int	i;

	i = -1;
	while (++i < idx_max)
	{
		if (b_top_is_bigger_than_a_bottom(deque_a, deque_b))
		{
			deque_push_value_bottom(ops, OP_PA);
			deque_push_value_bottom(ops, OP_RA);
			deque_push_node_bottom(deque_a, deque_pop_top(deque_b));
		}
		else
		{
			deque_push_value_bottom(ops, OP_RB);
			deque_rotate(deque_b, 1);
		}
	}
}
