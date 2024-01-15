/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:47:03 by tischmid          #+#    #+#             */
/*   Updated: 2024/01/15 11:52:41 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>

int	validate_deque(t_deque *deque, int status)
{
	t_deque			*sorted_deque;
	t_deque_type	prev_value;
	t_deque_type	value;
	int				i;

	if (status == -1)
		return (0);
	sorted_deque = deque_copy(deque);
	deque_sort(sorted_deque, cmp_int_asc);
	i = 0;
	prev_value = *&prev_value;
	while (sorted_deque->head)
	{
		value = deque_pop_top(sorted_deque)->data;
		if (i > 0 && prev_value == value)
			return (0);
		prev_value = value;
		++i;
	}
	return (1);
}

t_deque	*parse_args(int argc, char **argv)
{
	char	**list;
	char	**orig_list;
	t_deque	*deque;
	int		status;

	if (argc < 1)
		exit(1);
	if (argc == 1)
		exit(0);
	if (argc == 2)
	{
		list = ft_split(argv[1], ' ');
		orig_list = list;
		deque = array_list_to_deque(list, &status);
		while (*list)
		{
			free(*list);
			++list;
		}
		free(orig_list);
	}
	else
		deque = array_list_to_deque(argv + 1, &status);
	if (!validate_deque(deque, status) && ft_dprintf(2, "Error\n"))
		exit(2);
	return (deque);
}
