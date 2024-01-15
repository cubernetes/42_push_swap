/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:19:44 by tischmid          #+#    #+#             */
/*   Updated: 2024/01/15 22:25:36 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <limits.h>
#include <stdlib.h>

int	print_op(char *op, int amount)
{
	int	count;

	count = 0;
	while (amount--)
		count += ft_printf("%s\n", op);
	return (count);
}

int	print_ops(t_deque *ops)
{
	static char	*ops_strings[] = {"ra", "rra", "rb", "rrb", "rr", "rrr",
		"sa", "sb", "ss", "pa", "pb"};
	int			count;

	count = 0;
	while (ops && ops->head)
	{
		count += print_op(ops_strings[ops->head->data], 1);
		free(deque_pop_top(ops));
	}
	return (count);
}

t_deque	*push_buckets(t_deque *deque_a, t_deque *deque_b, size_t bucket_size,
		double factor)
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
	slice = deque_slice(sorted_deque, (int)(n - bucket_size), (int)n, 1);
	half_slice = deque_slice(sorted_deque, (int)(n - bucket_size), (int)(n
				- bucket_size / 2), 1);
	while (deque_a->head)
	{
		idx = deque_index(slice, deque_a->head->data);
		if (idx != -1)
		{
			deque_push_value_bottom(ops, OP_PB);
			deque_push_node_top(deque_b, deque_pop_top(deque_a));
			deque_rotate(slice, idx);
			free(deque_pop_top(slice));
			if (slice->size == 0)
			{
				bucket_size = (size_t)ft_max((int)((double)bucket_size
							* factor), 1);
				n += bucket_size;
				deque_free(slice);
				deque_free(half_slice);
				slice = deque_slice(sorted_deque, (int)(n - bucket_size),
						(int)n, 1);
				half_slice = deque_slice(sorted_deque, (int)(n - bucket_size),
						(int)(n - bucket_size / 2), 1);
			}
		}
		else
		{
			if (deque_b->head && deque_index(half_slice, deque_b->head->data)
				!= -1)
				(deque_push_value_bottom(ops, OP_RR), deque_rotate(deque_a, 1),
					deque_rotate(deque_b, 1));
			else
				(deque_push_value_bottom(ops, OP_RA), deque_rotate(deque_a, 1));
		}
	}
	deque_free(slice);
	deque_free(half_slice);
	deque_free(sorted_deque);
	return (ops);
}

int	deque_argmax(t_deque *deque, int *max_idx)
{
	t_deque_node	*orig_head;
	t_deque_node	*head;
	t_deque_type	max_value;
	int				idx;

	orig_head = deque->head;
	head = orig_head;
	if (!head)
		return (INT_MIN);
	idx = 0;
	if (max_idx)
		*max_idx = idx;
	max_value = head->data;
	head = head->next;
	while (head != orig_head)
	{
		++idx;
		if (head->data > max_value)
		{
			max_value = head->data;
			if (max_idx)
				*max_idx = idx;
		}
		head = head->next;
	}
	return (max_value);
}

int	b_top_is_bigger_than_a_bottom(t_deque *deque_a, t_deque *deque_b)
{
	t_deque_type	b_top;
	t_deque_type	a_bottom;
	t_deque_type	a_max;
	t_deque_type	a_max_idx;
	t_deque_type	b_max_idx;
	t_deque_type	max;

	if (!deque_a->head)
		return (1);
	if (!deque_b->head)
		return (0);
	b_top = deque_b->head->data;
	a_bottom = deque_a->head->prev->data;
	a_max = deque_argmax(deque_a, &a_max_idx);
	max = ft_max(a_max, deque_argmax(deque_b, &b_max_idx));
	if (b_top > a_bottom || a_bottom == max)
	{
		return (1);
	}
	return (0);
}

int	bottom_element_of_A_should_be_rotated(t_deque *deque_a, t_deque *deque_b)
{
	t_deque_type	a_bottom;
	t_deque_type	a_max;
	t_deque_type	b_max;
	t_deque_type	a_max_idx;
	t_deque_type	b_max_idx;
	t_deque_type	max;

	if (!deque_a->head)
		return (0);
	a_bottom = deque_a->head->prev->data;
	a_max = deque_argmax(deque_a, &a_max_idx);
	b_max = deque_argmax(deque_b, &b_max_idx);
	max = ft_max(a_max, b_max);
	if (a_bottom > b_max && a_bottom != max)
	{
		return (1);
	}
	return (0);
}

t_deque	*push_back_sorted(t_deque *deque_a, t_deque *deque_b)
{
	t_deque	*ops;
	int		i;
	int		idx_max;

	ops = deque_init();
	while (deque_b->head)
	{
		while (bottom_element_of_A_should_be_rotated(deque_a, deque_b))
		{
			deque_push_value_bottom(ops, OP_RRA);
			deque_rotate(deque_a, -1);
		}
		deque_argmax(deque_b, &idx_max);
		i = -1;
		if ((int)deque_b->size - idx_max < idx_max)
		{
			while (++i < (int)deque_b->size - idx_max)
			{
				deque_push_value_bottom(ops, OP_RRB);
				deque_rotate(deque_b, -1);
			}
		}
		else
		{
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
		deque_push_value_bottom(ops, OP_PA);
		deque_push_node_top(deque_a, deque_pop_top(deque_b));
	}
	while (bottom_element_of_A_should_be_rotated(deque_a, deque_b))
	{
		deque_push_value_bottom(ops, OP_RRA);
		deque_rotate(deque_a, -1);
	}
	return (ops);
}

/* 500 -> 80-120 and 0.79-0.91 */
t_deque	*push_swap_benchmark(t_deque *deque_a)
{
	t_deque	*deques[2];
	t_deque	*ops;
	size_t	min_bucket_size;
	double	best_factor;
	double	factor;
	size_t	bucket_size;
	int		min_ops;

	min_ops = INT_MAX;
	deques[0] = deque_init();
	deques[1] = deque_init();
	bucket_size = 0;
	min_bucket_size = 1;
	ops = deque_init();
	best_factor = 1.0;
	while (++bucket_size < (size_t)ft_min(120, ft_max(80,
				(int)deque_a->size)))
	{
		factor = 0.91;
		while (factor > 0.79)
		{
			deque_free(ops);
			deque_free(deques[0]);
			deque_free(deques[1]);
			ops = deque_init();
			deques[0] = deque_copy(deque_a);
			deques[1] = deque_init();
			deque_extend_free(ops, push_buckets(deques[0], deques[1],
					bucket_size, factor));
			deque_extend_free(ops, push_back_sorted(deques[0], deques[1]));
			if (ops->size < (size_t)min_ops)
			{
				min_bucket_size = bucket_size;
				best_factor = factor;
				min_ops = (int)ops->size;
			}
			factor -= 0.01;
		}
	}
	deque_free(ops);
	deque_free(deques[0]);
	deque_free(deques[1]);
	ops = deque_init();
	deques[0] = deque_copy(deque_a);
	deques[1] = deque_init();
	deque_extend_free(ops, push_buckets(deques[0], deques[1], min_bucket_size,
			best_factor));
	deque_extend_free(ops, push_back_sorted(deques[0], deques[1]));
	/* fprintf(stderr, "Buckets: %zu\nFactor: %.10f\n", min_bucket_size,
		best_factor); */
	deque_free(deques[0]);
	deque_free(deques[1]);
	return (deque_free(deque_a), ops);
}

void	print_state(void *state, int first)
{
	if (!first)
		ft_printf("\n");
	deque_print(((t_state *)state)->deque_a);
	deque_print(((t_state *)state)->deque_b);
	deque_print(((t_state *)state)->ops);
}

t_state	*new_state(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	t_state	*state;

	state = malloc(sizeof(*state));
	state->deque_a = deque_copy(deque_a);
	state->deque_b = deque_copy(deque_b);
	state->ops = deque_copy(ops);
	return (state);
}

t_ddeque_node	*new_state_node(t_deque *deque_a, t_deque *deque_b,
		t_deque *ops)
{
	t_state			*state;
	t_ddeque_node	*node;

	state = malloc(sizeof(*state));
	state->deque_a = deque_a;
	state->deque_b = deque_b;
	state->ops = ops;
	node = malloc(sizeof(*node));
	node->data = state;
	return (node);
}

void	op_ra(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	(void)deque_b;
	deque_rotate(deque_a, 1);
	deque_push_value_bottom(ops, OP_RA);
}

void	op_rb(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	(void)deque_a;
	deque_rotate(deque_b, 1);
	deque_push_value_bottom(ops, OP_RB);
}

void	op_rr(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	deque_rotate(deque_a, 1);
	deque_rotate(deque_b, 1);
	deque_push_value_bottom(ops, OP_RR);
}

void	op_rra(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	(void)deque_b;
	deque_rotate(deque_a, -1);
	deque_push_value_bottom(ops, OP_RRA);
}

void	op_rrb(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	(void)deque_a;
	deque_rotate(deque_b, -1);
	deque_push_value_bottom(ops, OP_RRB);
}

void	op_rrr(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	deque_rotate(deque_a, -1);
	deque_rotate(deque_b, -1);
	deque_push_value_bottom(ops, OP_RRR);
}

void	op_sa(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	(void)deque_b;
	deque_swap(deque_a);
	deque_push_value_bottom(ops, OP_SA);
}

void	op_sb(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	(void)deque_a;
	deque_swap(deque_b);
	deque_push_value_bottom(ops, OP_SB);
}

void	op_ss(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	deque_swap(deque_a);
	deque_swap(deque_b);
	deque_push_value_bottom(ops, OP_SS);
}

void	op_pa(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	deque_push_node_top(deque_a, deque_pop_top(deque_b));
	deque_push_value_bottom(ops, OP_PA);
}

void	op_pb(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	deque_push_node_top(deque_b, deque_pop_top(deque_a));
	deque_push_value_bottom(ops, OP_PB);
}

/* only brute-forcing with 6 out of 11 instructions since 6^n << 11^n */
t_deque	*generate_next_states(t_ddeque *deques, t_deque *deque_a,
		t_deque *deque_b, t_deque *ops, t_deque *sorted_a)
{
	static void	(*insts[])(t_deque *, t_deque *, t_deque *) = {op_ra, op_rb,
		op_sa, op_sb, op_pa, op_pb};
	t_deque		*copy_a;
	t_deque		*copy_b;
	t_deque		*ops_copy;
	int			i;

	i = -1;
	while (++i < (int)(sizeof(insts)/sizeof(insts[0])))
	{
		copy_a = deque_copy(deque_a);
		copy_b = deque_copy(deque_b);
		ops_copy = deque_copy(ops);
		insts[i](copy_a, copy_b, ops_copy);
		if (deque_equal(deque_a, copy_a) && deque_equal(deque_b, copy_b))
			continue ;
		if (deque_equal(copy_a, sorted_a) && (deque_free(copy_a), 1))
			return (deque_free(copy_b), ops_copy);
		ddeque_push_node_bottom(deques,
			new_state_node(copy_a, copy_b, ops_copy));
	}
	return (deque_init());
}

void	free_state(void	*state)
{
	deque_free(((t_state *)state)->deque_a);
	deque_free(((t_state *)state)->deque_b);
	deque_free(((t_state *)state)->ops);
	free(state);
}

t_deque	*brute_force(t_deque *deque_a)
{
	t_ddeque	*deques;
	t_deque		*sorted_a;
	t_deque		*deque_b;
	t_deque		*ops;

	deques = ddeque_init();
	deque_b = deque_init();
	ops = deque_init();
	ddeque_push_value_bottom(deques, new_state(deque_a, deque_b, ops));
	sorted_a = deque_copy(deque_a);
	deque_sort(sorted_a, cmp_int_asc);
	if (deque_equal(sorted_a, deque_a) && (deque_free(sorted_a), 1))
		return (ddeque_free(deques, free_state), ops);
	while (!ops->head)
	{
		deque_free(deque_a);
		deque_free(deque_b);
		deque_free(ops);
		deque_a = ((t_state *)deques->head->data)->deque_a;
		deque_b = ((t_state *)deques->head->data)->deque_b;
		ops = ((t_state *)deques->head->data)->ops;
		free((free(deques->head->data), ddeque_pop_top(deques)));
		ops = generate_next_states(deques, deque_a, deque_b, ops, sorted_a);
	}
	deque_free(deque_a);
	deque_free(deque_b);
	ddeque_free(deques, free_state);
	return (deque_free(sorted_a), ops);
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
