/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:35:28 by tischmid          #+#    #+#             */
/*   Updated: 2024/01/16 12:02:42 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

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

/* "6" for a 16GB RAM + 8GB swap system, "7" may freeze your system!!!*/
# define MAX_BRUTE_FORCE 6

typedef struct s_state
{
	t_deque	*deque_a;
	t_deque	*deque_b;
	t_deque	*ops;
}			t_state;

typedef struct s_bucket_data
{
	t_deque	*slice;
	t_deque	*h_slice;
	t_deque	*ops;
	size_t	n;
	size_t	buck_siz;
	size_t	min_buck_siz;
	double	factor;
	double	bst_factor;
}			t_bucket_data;

int		validate_arguments(char **list);
t_deque	*parse_args(int argc, char **argv);

#endif
