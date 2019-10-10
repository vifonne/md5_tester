/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:36:58 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/02 18:00:51 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ltoi(const char *str)
{
	int					neg;
	unsigned long long	nbr;

	neg = 1;
	nbr = 0;
	while (*str == '\b' || *str == '\f' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\r' || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			neg = -1;
	while (*str > 47 && *str < 58)
	{
		nbr = nbr * 10 + *str++ - 48;
		if (nbr > 2147483648)
		{
			write(2, "Error\n", 6);
			exit(0);
		}
	}
	return (neg * nbr);
}
