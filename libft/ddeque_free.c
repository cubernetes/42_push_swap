/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddeque_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:37:19 by tischmid          #+#    #+#             */
/*   Updated: 2024/01/15 15:47:51 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ddeque_free(t_ddeque *ddeque, void (free_data)(void *))
{
	t_ddeque_node	*head;
	t_ddeque_node	*tail;

	head = ddeque->head;
	if (!head)
		return ;
	tail = head->prev;
	while (head != tail)
	{
		head = head->next;
		free_data(head->prev->data);
		free(head->prev);
	}
	free_data(head->data);
	free(head);
	free(ddeque);
}
