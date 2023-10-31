/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:19:44 by tischmid          #+#    #+#             */
/*   Updated: 2023/11/01 00:40:22 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../include/deque.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	rot_pb_buckets(t_deque *deque_a, t_deque *deque_b, int n_buckets)
{
	t_deque_node	*top;

	while (deque_a->head)
	{
		top = deque_pop_right(deque_a);
		deque_push_right(deque_b, top->data);
		free(top);
	}
}

void	push_swap(t_deque *deque_a)
{
	t_deque	*deque_b;
	int		n_buckets;

	deque_b = deque_init();
	n_buckets = 4;
	(void)n_buckets;
	(void)deque_a;
	(void)deque_b;
	rot_pb_buckets(deque_a, deque_b, n_buckets);
	ft_printf("After:\n");
	deque_print(deque_a);
	deque_print(deque_b);
}

	/* deque_a = parse_args(argc, argv); */
int	main(int argc, char **argv)
{
	t_deque	*deque_a;

	(void)argc;
	(void)argv;
	deque_a = deque_init();
	deque_push_right(deque_a, 100);
	deque_push_right(deque_a, 99);
	deque_push_right(deque_a, 98);
	deque_push_right(deque_a, 97);
	deque_push_right(deque_a, 96);
	deque_push_right(deque_a, 95);
	deque_push_right(deque_a, 94);
	deque_push_right(deque_a, 93);
	deque_push_right(deque_a, 92);
	deque_push_right(deque_a, 91);
	deque_push_right(deque_a, 90);
	deque_push_right(deque_a, 89);
	deque_push_right(deque_a, 88);
	deque_push_right(deque_a, 87);
	deque_push_right(deque_a, 86);
	deque_push_right(deque_a, 85);
	deque_push_right(deque_a, 84);
	deque_push_right(deque_a, 83);
	deque_push_right(deque_a, 82);
	deque_push_right(deque_a, 81);
	deque_push_right(deque_a, 80);
	deque_push_right(deque_a, 79);
	deque_push_right(deque_a, 78);
	deque_push_right(deque_a, 77);
	deque_push_right(deque_a, 76);
	deque_push_right(deque_a, 75);
	deque_push_right(deque_a, 74);
	deque_push_right(deque_a, 73);
	deque_push_right(deque_a, 72);
	deque_push_right(deque_a, 71);
	deque_push_right(deque_a, 70);
	deque_push_right(deque_a, 69);
	deque_push_right(deque_a, 68);
	deque_push_right(deque_a, 67);
	deque_push_right(deque_a, 66);
	deque_push_right(deque_a, 65);
	deque_push_right(deque_a, 64);
	deque_push_right(deque_a, 63);
	deque_push_right(deque_a, 62);
	deque_push_right(deque_a, 61);
	deque_push_right(deque_a, 60);
	deque_push_right(deque_a, 59);
	deque_push_right(deque_a, 58);
	deque_push_right(deque_a, 57);
	deque_push_right(deque_a, 56);
	deque_push_right(deque_a, 55);
	deque_push_right(deque_a, 54);
	deque_push_right(deque_a, 53);
	deque_push_right(deque_a, 52);
	deque_push_right(deque_a, 51);
	deque_push_right(deque_a, 50);
	deque_push_right(deque_a, 49);
	deque_push_right(deque_a, 48);
	deque_push_right(deque_a, 47);
	deque_push_right(deque_a, 46);
	deque_push_right(deque_a, 45);
	deque_push_right(deque_a, 44);
	deque_push_right(deque_a, 43);
	deque_push_right(deque_a, 42);
	deque_push_right(deque_a, 41);
	deque_push_right(deque_a, 40);
	deque_push_right(deque_a, 39);
	deque_push_right(deque_a, 38);
	deque_push_right(deque_a, 37);
	deque_push_right(deque_a, 36);
	deque_push_right(deque_a, 35);
	deque_push_right(deque_a, 34);
	deque_push_right(deque_a, 33);
	deque_push_right(deque_a, 32);
	deque_push_right(deque_a, 31);
	deque_push_right(deque_a, 30);
	deque_push_right(deque_a, 29);
	deque_push_right(deque_a, 28);
	deque_push_right(deque_a, 27);
	deque_push_right(deque_a, 26);
	deque_push_right(deque_a, 25);
	deque_push_right(deque_a, 24);
	deque_push_right(deque_a, 23);
	deque_push_right(deque_a, 22);
	deque_push_right(deque_a, 21);
	deque_push_right(deque_a, 20);
	deque_push_right(deque_a, 19);
	deque_push_right(deque_a, 18);
	deque_push_right(deque_a, 17);
	deque_push_right(deque_a, 16);
	deque_push_right(deque_a, 15);
	deque_push_right(deque_a, 14);
	deque_push_right(deque_a, 13);
	deque_push_right(deque_a, 12);
	deque_push_right(deque_a, 11);
	deque_push_right(deque_a, 10);
	deque_push_right(deque_a, 9);
	deque_push_right(deque_a, 8);
	deque_push_right(deque_a, 7);
	deque_push_right(deque_a, 6);
	deque_push_right(deque_a, 5);
	deque_push_right(deque_a, 4);
	deque_push_right(deque_a, 3);
	deque_push_right(deque_a, 2);
	deque_push_right(deque_a, 1);
	ft_printf("Initial deque:\n");
	deque_print(deque_a);
	push_swap(deque_a);
	deque_free(deque_a);
	return (0);
}
