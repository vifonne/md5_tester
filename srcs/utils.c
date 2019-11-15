/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:48:45 by vifonne           #+#    #+#             */
/*   Updated: 2019/11/15 14:39:12 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include <stdio.h>

void		print_bits(uint8_t *msg, size_t length)
{
	int		i;
	size_t	msg_index;
	size_t	print_index;

	msg_index = 0;
	print_index = 1;
	while (msg_index < length)
	{
		i = 256;
		while (i >>= 1)
		{
			(msg[msg_index] & (uint8_t)i) ? write(1, "1", 1) : write(1, "0", 1);
			if (print_index % 4 == 0)
				write(1, " ", 1);
			print_index++;
		}
		msg_index++;
	}
	write(1, "\n", 1);
}

void		print_output_full(t_msg *msg, int s, int r)
{
	if (r == 0)
	{
		ft_putstr(msg->algo_name);
		ft_putstr(" (");
		if (s == 1)
			ft_putchar('"');
		ft_putstr(msg->filename);
		if (s == 1)
			ft_putchar('"');
		ft_putstr(") = ");
	}
	print_byte(msg);
	if (r == 1)
	{
		ft_putchar(' ');
		if (s == 1)
			ft_putchar('"');
		ft_putstr(msg->filename);
		if (s == 1)
			ft_putchar('"');
	}
}

void		print_output(t_msg *msg, t_options opt)
{
	if (opt.q == 1)
		print_byte(msg);
	else
		print_output_full(msg, opt.s, opt.r);
	ft_putchar('\n');
}
