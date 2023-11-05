/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:25:38 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/05 01:46:35 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"
#include "../libft/libft.h"
#include <stdlib.h>

/* frees array_list afterwards */
t_deque	*array_list_to_deque(char **array_list)
{
	t_deque	*deque;
	char	**orig_array_list;

	deque = deque_init();
	orig_array_list = array_list;
	while (*array_list)
	{
		deque_push_right(deque, (t_deque_type)ft_atoi(*array_list));
		free(*array_list);
		++array_list;
	}
	free(orig_array_list);
	return (deque);
}

void	deque_print(t_deque *deque)
{
	t_deque_node	*head;
	t_deque_node	*orig_head;

	head = deque->head;
	orig_head = head;
	if (head)
		ft_printf("%d", head->data);
	else
	{
		ft_printf("Empty deque.\n");
		return ;
	}
	while (head->next != orig_head)
	{
		ft_printf(" -> %d", head->next->data);
		head = head->next;
	}
	ft_printf("\n");
}

void	deque_free(t_deque *deque)
{
	t_deque_node	*head;
	t_deque_node	*tail;

	head = deque->head;
	if (!head)
		return ;
	tail = head->prev;
	while (head != tail)
	{
		head = head->next;
		free(head->prev);
	}
	free(head);
	free(deque);
}

t_deque	*deque_init(void)
{
	t_deque	*deque;

	deque = malloc(sizeof(*deque));
	deque->head = NULL;
	return (deque);
}
