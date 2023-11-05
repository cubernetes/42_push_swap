/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 01:22:11 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/05 01:22:26 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/deque.h"

int	cmp_int_asc(t_deque_type a, t_deque_type b)
{
	return (a > b);
}

int	cmp_int_desc(t_deque_type a, t_deque_type b)
{
	return (a < b);
}
