/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute_force_states.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:58:58 by tosuman           #+#    #+#             */
/*   Updated: 2024/01/16 13:05:25 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <stdlib.h>

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

/* only brute-forcing with 6 out of 11 instructions since 6^n << 11^n */
t_deque	*generate_next_states(t_ddeque *deques, t_deque *deque_a_b[2],
		t_deque *ops, t_deque *sorted_a)
{
	static void	(*insts[])(t_deque *, t_deque *, t_deque *) = {op_ra, op_rb,
		op_sa, op_sb, op_pa, op_pb};
	t_deque		*copy_a;
	t_deque		*copy_b;
	t_deque		*ops_copy;
	int			i;

	i = -1;
	while (++i < (int)(sizeof(insts) / sizeof(insts[0])))
	{
		copy_a = deque_copy(deque_a_b[0]);
		copy_b = deque_copy(deque_a_b[1]);
		ops_copy = deque_copy(ops);
		insts[i](copy_a, copy_b, ops_copy);
		if (deque_equal(deque_a_b[0], copy_a) && deque_equal(deque_a_b[1],
				copy_b)
			&& (deque_free(copy_a), 1) && (deque_free(copy_b), 1)
			&& (deque_free(ops_copy), 1))
			continue ;
		if (deque_equal(copy_a, sorted_a) && (deque_free(copy_a), 1))
			return (deque_free(copy_b), deque_free(ops), ops_copy);
		ddeque_push_node_bottom(deques,
			new_state_node(copy_a, copy_b, ops_copy));
	}
	return (deque_free(ops), deque_init());
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
	t_deque		*deque_a_b[2];
	t_deque		*ops;

	deques = ddeque_init();
	deque_a_b[1] = deque_init();
	ops = deque_init();
	ddeque_push_value_bottom(deques, new_state(deque_a, deque_a_b[1], ops));
	sorted_a = deque_copy(deque_a);
	(deque_sort(sorted_a, cmp_int_asc), deque_a_b[0] = deque_a);
	if (deque_equal(sorted_a, deque_a_b[0]) && (deque_free(sorted_a), 1))
		return (ddeque_free(deques, free_state), ops);
	while (!ops->head)
	{
		(deque_free(deque_a_b[0]), deque_free(deque_a_b[1]), deque_free(ops));
		deque_a_b[0] = ((t_state *)deques->head->data)->deque_a;
		deque_a_b[1] = ((t_state *)deques->head->data)->deque_b;
		ops = ((t_state *)deques->head->data)->ops;
		free((free(deques->head->data), ddeque_pop_top(deques)));
		ops = generate_next_states(deques, deque_a_b, ops, sorted_a);
	}
	(deque_free(deque_a_b[0]), deque_free(deque_a_b[1]));
	ddeque_free(deques, free_state);
	return (deque_free(sorted_a), ops);
}
