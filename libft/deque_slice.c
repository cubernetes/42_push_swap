/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_slice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:39:06 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/22 14:49:22 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_deque	*deque_slice(t_deque *deque, int start, int end, int step)
{
	t_deque_node	*head;
	t_deque			*slice;
	int				size;
	int				orig_start;

	slice = deque_init();
	size = (int)deque_size(deque);
	orig_start = start;
	if (start < 0)
		start = ft_max(start + size, 0);
	start = ft_min(start, size - 1);
	if (end < 0)
		end = ft_max(end + size, 0);
	end = ft_min(end, size);
	if (orig_start < 0 && end == 0 && step > 0)
		end = size;
	else if ((end - start) * step <= 0)
		return (slice);
		/* return (slice->size = , slice); */ /* set the slice size!!! */
	head = deque->head;
	size = start;
	while (size--)
		head = head->next;
	while ((step > 0 && start < end) || (step < 0 && start > end))
	{
		deque_push_value_bottom(slice, head->data);
		size = (int)ft_abs(step);
		while (size--)
		{
			if (step > 0)
				head = head->next;
			else
				head = head->prev;
		}
		start += step;
	}
	return (slice);
}
