/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:47:03 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/22 05:13:36 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>

int	validate_deque(t_deque *deque)
{
	(void)deque;
	return (1);
}

t_deque	*parse_args(int argc, char **argv)
{
	char	**list;
	char	**orig_list;
	t_deque	*deque;

	if (argc < 2)
		exit(1);
	if (argc == 2)
	{
		list = ft_split(argv[1], ' ');
		orig_list = list;
		deque = array_list_to_deque(list);
		while (*list)
		{
			free(*list);
			++list;
		}
		free(orig_list);
	}
	else
		deque = array_list_to_deque(argv + 1);
	if (!validate_deque(deque) && ft_dprintf(2, "Error\n"))
		exit(2);
	return (deque);
}
