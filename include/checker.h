/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:09:46 by tosuman           #+#    #+#             */
/*   Updated: 2024/01/16 16:13:47 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "../libft/libft.h"

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

#endif
