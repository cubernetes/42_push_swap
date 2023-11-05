/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:35:28 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/05 02:01:00 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./deque.h"

int		validate_arguments(char **list);
t_deque	*parse_args(int argc, char **argv);
int		cmp_int_asc(t_deque_type a, t_deque_type b);
int		cmp_int_desc(t_deque_type a, t_deque_type b);

#endif
