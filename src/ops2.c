/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:56:06 by tosuman           #+#    #+#             */
/*   Updated: 2024/01/16 12:56:28 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"

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
