/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:18:45 by mabouce           #+#    #+#             */
/*   Updated: 2018/12/30 15:55:38 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_tab_int(int *tab, int len)
{
	int	i;

	i = 0;
	ft_putchar('|');
	while (i < len)
	{
		ft_putnbr(tab[i]);
		ft_putchar('|');
		i++;
	}
	ft_putchar('\n');
}
