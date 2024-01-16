/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:55:32 by tosuman           #+#    #+#             */
/*   Updated: 2024/01/16 12:55:57 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"

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
