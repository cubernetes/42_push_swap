/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:29:25 by tosuman           #+#    #+#             */
/*   Updated: 2023/10/19 11:14:32 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_putnbr(int nb)
{
	int	count;

	count = 0;
	if (nb > 9)
	{
		count += ft_putnbr(nb / 10);
		count += ft_putchar(nb % 10 + '0');
	}
	else if (nb == INT_MIN)
	{
		count += ft_putnbr(nb / 10);
		count += ft_putnbr(-(nb % 10));
	}
	else if (nb < 0)
	{
		count += ft_putchar('-');
		count += ft_putnbr(-nb);
	}
	else
		count += ft_putchar(nb % 10 + '0');
	return (count);
}
