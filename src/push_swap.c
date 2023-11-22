/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:19:44 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/22 04:21:05 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"
#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* MAX_BUCKET_SIZE = 60; */

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

t_deque	*push_buckets(t_deque *deque_a, t_deque *deque_b, size_t bucket_size, double factor)
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
	half_slice = deque_slice(sorted_deque, n - bucket_size, n - bucket_size / 2,
			1);
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
				bucket_size = ft_max(bucket_size * factor, 1);
				n += bucket_size;
				slice = deque_slice(sorted_deque, n - bucket_size, n, 1);
				half_slice = deque_slice(sorted_deque, n - bucket_size, n // bucket division is not strict here!
						- bucket_size / 2, 1);
			}
		}
		else
		{
			if (deque_b->head && deque_index(half_slice, deque_b->head->data) != -1) // bucket division is not strict here!
				(deque_push_value_bottom(ops, OP_RR), deque_rotate(deque_a, 1), deque_rotate(deque_b, 1));
			else
				(deque_push_value_bottom(ops, OP_RA), deque_rotate(deque_a, 1));
		}
	}
	deque_free(slice);
	deque_free(half_slice);
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

t_deque	*push_back_sorted_new(t_deque *deque_a, t_deque *deque_b)
{
	int		idx_max;
	int		i;
	size_t	size;
	t_deque	*ops;

	ops = deque_init();
	while (deque_b->head /*|| (deque_a->head
			&& deque_a->head->prev->data > deque_argmax(deque_b, &idx_max)
			&& deque_a->head->prev->data < deque_a->head->data)*/)
	{
		/* if (deque_a->head && deque_a->head->prev->data > deque_argmax(deque_b, */
				/* &idx_max) && deque_a->head->prev->data < deque_a->head->data) */
		/* { */
			/* deque_push_value_bottom(ops, OP_RRA); */
			/* deque_rotate(deque_a, -1); */
			/* continue ; */
		/* } */
		deque_argmax(deque_b, &idx_max);
		size = deque_size(deque_b);
		i = -1;
		if (size - idx_max < idx_max)
		{
			while (++i < size - idx_max)
			{
				deque_push_value_bottom(ops, OP_RRB);
				deque_rotate(deque_b, -1);
				/* if (deque_b->head */
					/* && (deque_b->head->data > deque_a->head->prev->data */
						/* || (deque_a->head->prev->data > deque_argmax(deque_b, */
								/* NULL) */
							/* && deque_a->head->prev->data == deque_argmax(deque_a, */
								/* NULL)))) */
				/* { */
					/* deque_push_value_bottom(ops, OP_PA); */
					/* deque_push_value_bottom(ops, OP_RA); */
					/* deque_push_node_bottom(deque_a, deque_pop_top(deque_b)); */
				/* } */
			}
		}
		else
		{
			while (++i < idx_max)
			{
				/* if (deque_b->head */
					/* && (deque_b->head->data > deque_a->head->prev->data */
						/* || (deque_a->head->prev->data > deque_argmax(deque_b, */
								/* NULL) */
							/* && deque_a->head->prev->data == deque_argmax(deque_a, */
								/* NULL)))) */
				/* { */
					/* deque_push_value_bottom(ops, OP_PA); */
					/* deque_push_value_bottom(ops, OP_RA); */
					/* deque_push_node_bottom(deque_a, deque_pop_top(deque_b)); */
				/* } */
				/* else */
				/* { */
					deque_push_value_bottom(ops, OP_RB);
					deque_rotate(deque_b, 1);
				/* } */
			}
		}
		if (deque_b->head)
		{
			deque_push_value_bottom(ops, OP_PA);
			deque_push_node_top(deque_a, deque_pop_top(deque_b));
		}
	}
	return (ops);
}
































int	B_top_is_bigger_than_A_bottom(t_deque *deque_a, t_deque *deque_b)
{
	t_deque_type	b_top;
	t_deque_type	a_bottom;
	t_deque_type	a_max;
	t_deque_type	a_max_idx;
	t_deque_type	b_max_idx;
	t_deque_type	max;

	if (!deque_a->head) // A is empty, always push B top
		return (1);
	if (!deque_b->head) // B is empty, cannot push
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
	size_t	size;

	ops = deque_init(); // empty list of operations
	while (deque_b->head)
	{
		while (bottom_element_of_A_should_be_rotated(deque_a, deque_b))
		{
			deque_push_value_bottom(ops, OP_RRA);
			deque_rotate(deque_a, -1);
		}
		deque_argmax(deque_b, &idx_max); // save the index of the biggest element in B in idx_max
		size = deque_size(deque_b); // number of elements in B
		i = -1;
		if (size - idx_max < idx_max) // if biggest element is closer to the bottom of B do (size - idx_max) RRBs
		{
			while (++i < size - idx_max)
			{
				deque_push_value_bottom(ops, OP_RRB); // add RRB to ops
				deque_rotate(deque_b, -1); // perform RRB
			}
		}
		else // if biggest element is closer to the top of B do (idx_max) RBs
		{
			while (++i < idx_max)
			{
				if (B_top_is_bigger_than_A_bottom(deque_a, deque_b))
				{
					deque_push_value_bottom(ops, OP_PA); // B's top element is worth pushing over. add "PA" to ops
					deque_push_value_bottom(ops, OP_RA); // rotate new top element of A to the bottom, "RA"
					deque_push_node_bottom(deque_a, deque_pop_top(deque_b)); // pop top from B and push to BOTTOM of A
				}
				else
				{
					deque_push_value_bottom(ops, OP_RB); // add RB to ops
					deque_rotate(deque_b, 1); // perform RB
				}
			}
		}
		// we don't need to check if B is empty, because BLANK
		deque_push_value_bottom(ops, OP_PA); // the biggest element is now the top of B, add "PA" to ops
		deque_push_node_top(deque_a, deque_pop_top(deque_b)); // pop top from B and push to A
	}
	while (bottom_element_of_A_should_be_rotated(deque_a, deque_b))
	{
		deque_push_value_bottom(ops, OP_RRA);
		deque_rotate(deque_a, -1);
	}
	return (ops); // return the operations that were made to later print them
}



























void	push_swap(t_deque *deque_a)
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
	// 500 -> 80 -- 120 and 0.79 to 0.91
	while (++bucket_size < ft_min(300, ft_max(100, deque_size(deque_a))))
	{
		factor = 1.0;
		while (factor > 0.50)
		{
			deque_free(ops);
			deque_free(deques[0]);
			deque_free(deques[1]);
			ops = deque_init();
			deques[0] = deque_copy(deque_a);
			deques[1] = deque_init();
			deque_extend_free(ops, push_buckets(deques[0], deques[1], bucket_size, factor));
			deque_extend_free(ops, push_back_sorted(deques[0], deques[1]));
			if (deque_size(ops) < min_ops)
			{
				min_bucket_size = bucket_size;
				best_factor = factor;
				min_ops = deque_size(ops);
			}
			factor -= 0.05;
			/* factor -= 0.005; */
		}
	}
	/* min_bucket_size = 3; */
	printf("Buckets: %zu\nFactor: %.10f\n", min_bucket_size, best_factor);
	fflush(stdout);
	deque_free(ops);
	deque_free(deques[0]);
	deque_free(deques[1]);
	ops = deque_init();
	deques[0] = deque_copy(deque_a);
	deques[1] = deque_init();
	deque_extend_free(ops, push_buckets(deques[0], deques[1], min_bucket_size, best_factor));
	deque_extend_free(ops, push_back_sorted(deques[0], deques[1]));
	print_ops(ops);
}

/* void	push_swap_benchmark(t_deque *deque_a) */
/* { */
	/* t_size	bucket_size; */
	/* t_deque	*operations; */
	/* t_deque	*minimal_operations; */
/*  */
	/* deque_size = deque_size(deque_a); */
	/* minimal_operations = NULL; */
	/* bucket_size = 0; */
	/* while (++bucket_size < ft_min(MAX_BUCKET_SIZE, deque_a.size)) */
	/* { */
		/* minimal_operations = push_swap_pass(bucket_size); */
	/* } */
	/* print_ops(minimal_operations); */
/* } */

int	main(int argc, char **argv)
{
	t_deque	*deque_a;
	t_deque	*ops;

	deque_a = parse_args(argc, argv);
	push_swap(deque_a);
	/* ops = bucket_sort_benchmark(deque_a); */
	/* print_ops(ops); */
	/* deque_free(ops); */
	deque_free(deque_a);
	return (0);
}
