/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:47:03 by tischmid          #+#    #+#             */
/*   Updated: 2023/10/19 09:47:38 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"
#include "../libft/libft.h"
#include <stdlib.h>

int	validate_arguments(char **list)
{
	return (1);
}

t_deque	parse_args(int argc, char **argv)
{
	char	**list;

	if (argc < 2)
	{
		ft_dprintf(2, "Error\n");
		exit(1);
	}
	if (argc == 2)
	{
		list = ft_split(argv[1], ' ');
		if (!validate_arguments(list))
		{
			ft_dprintf(2, "Error\n");
			exit(2);
		}
		return (list_to_deque(list));
	}
	if (!validate_arguments(argv + 1))
	{
		ft_dprintf(2, "Error\n");
		exit(2);
	}
	return (list_to_deque(argv + 1));
}
