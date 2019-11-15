/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:48:45 by vifonne           #+#    #+#             */
/*   Updated: 2019/11/15 14:11:04 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include <stdio.h>

uint32_t	bswap_32(uint32_t bytes)
{
	bytes = ((bytes >> 24) & 0xFF)
		| ((bytes << 8) & 0xFF0000)
		| ((bytes >> 8) & 0xFF00)
		| ((bytes << 24) & 0xFF000000);
	return (bytes);
}

uint64_t	bswap_64(uint64_t bytes)
{
	bytes = (bytes & 0x00000000FFFFFFFF) << 32
		| (bytes & 0xFFFFFFFF00000000) >> 32;
	bytes = (bytes & 0x0000FFFF0000FFFF) << 16
		| (bytes & 0xFFFF0000FFFF0000) >> 16;
	bytes = (bytes & 0x00FF00FF00FF00FF) << 8
		| (bytes & 0xFF00FF00FF00FF00) >> 8;
	return (bytes);
}

void		print_byte(t_msg *msg)
{
	uint8_t		to_print[32];
	uint32_t	tmp;
	int			idx;
	int			size;

	idx = 0;
	if (msg->algo_choosen == 1)
	{
		size = sizeof(uint32_t) * 8;
		while (idx < 8)
		{
			tmp = bswap_32(msg->md_buffer.h[idx]);
			ft_memcpy(to_print + idx * sizeof(uint32_t), &tmp, sizeof(uint32_t));
			idx++;
		}
		idx = 0;
	}
	else
	{
		size = 16;
		ft_memcpy(to_print, msg->md_buffer.h, size);
	}
	while (idx < size)
	{
		printf("%02x", to_print[idx]);
		idx++;
	}
	fflush(stdout);
}

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
