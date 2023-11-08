/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:35:28 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/08 04:40:19 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./deque.h"

# define OP_RA   0
# define OP_RRA  1
# define OP_RB   2
# define OP_RRB  3
# define OP_RR   4
# define OP_RRR  5
# define OP_SA   6
# define OP_SB   7
# define OP_SS   8
# define OP_PA   9
# define OP_PB   10

int		validate_arguments(char **list);
t_deque	*parse_args(int argc, char **argv);
int		cmp_int_asc(t_deque_type a, t_deque_type b);
int		cmp_int_desc(t_deque_type a, t_deque_type b);
int		ft_max(int a, int b);
int		ft_min(int a, int b);

#endif
