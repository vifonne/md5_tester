/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:41:18 by vifonne           #+#    #+#             */
/*   Updated: 2018/11/08 14:54:08 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_nlen(int nb)
{
	size_t	i;

	i = 0;
	if (nb <= 0)
		i++;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char		*str;
	size_t		i;
	long long	nbr;
	size_t		tmp;

	nbr = (long long)n;
	i = ft_nlen(n);
	tmp = i;
	if (!(str = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	if (nbr == 0)
		str[0] = 48;
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	while (nbr)
	{
		str[i - 1] = (nbr % 10) + 48;
		nbr /= 10;
		i--;
	}
	str[tmp] = '\0';
	return (str);
}
