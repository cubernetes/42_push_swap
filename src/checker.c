/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:04:00 by tosuman           #+#    #+#             */
/*   Updated: 2024/01/16 17:33:09 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/checker.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_ddeque	*init_all_ops_deque(void)
{
	t_ddeque	*all_ops;

	all_ops = ddeque_init();
	ddeque_push_value_bottom(all_ops, ft_strdup("ra\n"));
	ddeque_push_value_bottom(all_ops, ft_strdup("rra\n"));
	ddeque_push_value_bottom(all_ops, ft_strdup("rb\n"));
	ddeque_push_value_bottom(all_ops, ft_strdup("rrb\n"));
	ddeque_push_value_bottom(all_ops, ft_strdup("rr\n"));
	ddeque_push_value_bottom(all_ops, ft_strdup("rrr\n"));
	ddeque_push_value_bottom(all_ops, ft_strdup("sa\n"));
	ddeque_push_value_bottom(all_ops, ft_strdup("sb\n"));
	ddeque_push_value_bottom(all_ops, ft_strdup("ss\n"));
	ddeque_push_value_bottom(all_ops, ft_strdup("pa\n"));
	ddeque_push_value_bottom(all_ops, ft_strdup("pb\n"));
	return (all_ops);
}

t_deque	*parse_input(void)
{
	char		*inst;
	t_deque		*ops;
	t_ddeque	*all_ops;
	int			idx;
	int			i;

	all_ops = init_all_ops_deque();
	ops = deque_init();
	i = 0;
	while (++i)
	{
		inst = get_next_line(0);
		if (!inst)
			break ;
		idx = ddeque_index(all_ops, inst, (int (*)(void *, void *))ft_streq);
		if (idx == -1 && (ddeque_free(all_ops, free), 1))
			(deque_free(ops), ft_printf("Error: %s\n", inst), free(inst), exit(3));
		free(inst);
		deque_push_value_bottom(ops, idx);
	}
	return (ddeque_free(all_ops, free), ops);
}

void	simulate(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	static void	(*insts[])(t_deque *, t_deque *, t_deque *) = {op_ra, op_rra,
		op_rb, op_rrb, op_rr, op_rrr, op_sa, op_sb, op_ss, op_pa, op_pb};
	t_deque		*ops_null;

	ops_null = deque_init();
	while (ops->head)
	{
		insts[ops->head->data](deque_a, deque_b, ops_null);
		free(deque_pop_top(ops));
	}
}

int	main(int argc, char **argv)
{
	t_deque	*deque_a;
	t_deque	*deque_b;
	t_deque	*ops;
	t_deque	*sorted_a;

	deque_a = parse_args(argc, argv);
	deque_b = deque_init();
	sorted_a = deque_copy(deque_a);
	deque_sort(sorted_a, cmp_int_asc);
	ops = parse_input();
	simulate(deque_a, deque_b, ops);
	if (deque_equal(sorted_a, deque_a))
		return (ft_printf("OK\n"), 0);
	else
		return (ft_printf("KO\n"), 4);
}
