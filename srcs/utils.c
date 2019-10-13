/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:48:45 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/13 13:39:03 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include <stdio.h>

void	print_byte(t_msg *msg)
{
	uint8_t	to_print[16];
	int		idx;

	idx = 0;
	ft_memcpy(to_print, msg->md_buffer.h, 16);
	while (idx < 16)
	{
		printf("%02x", to_print[idx]);
		idx++;
	}
	printf("\n");
}

void	print_bits(uint8_t *msg, size_t length)
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
