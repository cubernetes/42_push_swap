/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:35:28 by tischmid          #+#    #+#             */
/*   Updated: 2024/01/16 13:10:28 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

# define OP_RA 0
# define OP_RRA 1
# define OP_RB 2
# define OP_RRB 3
# define OP_RR 4
# define OP_RRR 5
# define OP_SA 6
# define OP_SB 7
# define OP_SS 8
# define OP_PA 9
# define OP_PB 10

# define RA "ra"
# define RRA "rra"
# define RB "rb"
# define RRB "rrb"
# define RR "rr"
# define RRR "rrr"
# define SA "sa"
# define SB "sb"
# define SS "ss"
# define PA "pa"
# define PB "pb"

/* "6" for a 16GB RAM + 8GB swap system, "7" may freeze your system!!!*/
# define MAX_BRUTE_FORCE 6

typedef struct s_state
{
	t_deque		*deque_a;
	t_deque		*deque_b;
	t_deque		*ops;
}				t_state;

typedef struct s_bucket_data
{
	t_deque		*slice;
	t_deque		*h_slice;
	t_deque		*ops;
	size_t		n;
	size_t		buck_siz;
	size_t		min_buck_siz;
	double		factor;
	double		bst_factor;
}				t_bucket_data;

int				validate_arguments(char **list);
t_deque			*parse_args(int argc, char **argv);

void			op_ra(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
void			op_rb(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
void			op_rr(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
void			op_rra(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
void			op_rrb(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
void			op_rrr(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
void			op_sa(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
void			op_sb(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
void			op_ss(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
void			op_pa(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
void			op_pb(t_deque *deque_a, t_deque *deque_b, t_deque *ops);

void			print_state(void *state, int first);
t_state			*new_state(t_deque *deque_a, t_deque *deque_b, t_deque *ops);
t_ddeque_node	*new_state_node(t_deque *deque_a, t_deque *deque_b,
					t_deque *ops);
t_deque			*generate_next_states(t_ddeque *deques, t_deque *deque_a_b[2],
					t_deque *ops, t_deque *sorted_a);
void			free_state(void *state);
t_deque			*brute_force(t_deque *deque_a);
int				print_op(char *op, int amount);
int				print_ops(t_deque *ops);
void			push_bucket(t_deque *deque_a, t_deque *deque_b,
					t_deque *sorted_deque, t_bucket_data *d);
t_deque			*push_buckets(t_deque *deque_a, t_deque *deque_b,
					t_bucket_data d);
int				b_top_is_bigger_than_a_bottom(t_deque *deque_a,
					t_deque *deque_b);
int				bottom_element_of_a_should_be_rotated(t_deque *deque_a,
					t_deque *deque_b);
void			rev_rotate_b(int idx_max, t_deque *deque_b, t_deque *ops);
void			rotate_b(int idx_max, t_deque *deque_a, t_deque *deque_b,
					t_deque *ops);

#endif
