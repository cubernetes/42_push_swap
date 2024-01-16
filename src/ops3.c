/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:56:54 by tosuman           #+#    #+#             */
/*   Updated: 2024/01/16 12:57:13 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"

void	op_pb(t_deque *deque_a, t_deque *deque_b, t_deque *ops)
{
	deque_push_node_top(deque_b, deque_pop_top(deque_a));
	deque_push_value_bottom(ops, OP_PB);
}
