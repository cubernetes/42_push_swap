/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:04:57 by tosuman           #+#    #+#             */
/*   Updated: 2024/01/16 13:05:19 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
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
	static char	*ops_strs[] = {RA, RRA, RB, RRB, RR, RRR, SA, SB, SS, PA, PB};
	int			count;

	count = 0;
	while (ops && ops->head)
	{
		count += print_op(ops_strs[ops->head->data], 1);
		free(deque_pop_top(ops));
	}
	return (count);
}

void	print_state(void *state, int first)
{
	if (!first)
		ft_printf("\n");
	deque_print(((t_state *)state)->deque_a);
	deque_print(((t_state *)state)->deque_b);
	deque_print(((t_state *)state)->ops);
}
