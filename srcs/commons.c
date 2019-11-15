/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:35:08 by vifonne           #+#    #+#             */
/*   Updated: 2019/11/15 12:24:46 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	read_from_fd(int fd, t_msg *msg, t_functions *fct_table)
{
	size_t	ret;
	char	read_buffer[READ_BUFF_SIZE];

	while ((ret = read(fd, read_buffer, READ_BUFF_SIZE)) > 0)
	{
		write(1, read_buffer, ret);
		msg->original_len += ret;
		fct_table->string((uint8_t *)read_buffer, ret, msg, fct_table);
	}
	ft_putchar('\n');
	fct_table->preparation(msg, fct_table);
}

ssize_t	basic_string(uint8_t *str, ssize_t length, t_msg *msg, t_functions *fct_table)
{
	int cpy_len;
	cpy_len = MD5_BUFF_SIZE - msg->internal_buffer_len;
	if (length < cpy_len)
		cpy_len = length;
	ft_memcpy(msg->internal_buffer + msg->internal_buffer_len, str, cpy_len);
	msg->internal_buffer_len += cpy_len;
	length -= cpy_len;
	if (msg->internal_buffer_len == MD5_BUFF_SIZE)
	{
		fct_table->loop((uint32_t *)msg->internal_buffer, msg, fct_table);
		msg->internal_buffer_len = 0;
	}
	return (length);
}

void	init_md_buffer(t_msg *msg)
{
	if (msg->algo_choosen == 0)
	{
		msg->md_buffer.h[0] = 0x67452301;
		msg->md_buffer.h[1] = 0xEFCDAB89;
		msg->md_buffer.h[2] = 0x98BADCFE;
		msg->md_buffer.h[3] = 0x10325476;
	}
	else if (msg->algo_choosen == 1)
	{
		msg->md_buffer.h[0] = 0x6a09e667;
		msg->md_buffer.h[1] = 0xbb67ae85;
		msg->md_buffer.h[2] = 0x3c6ef372;
		msg->md_buffer.h[3] = 0xa54ff53a;
		msg->md_buffer.h[4] = 0x510e527f;
		msg->md_buffer.h[5] = 0x9b05688c;
		msg->md_buffer.h[6] = 0x1f83d9ab;
		msg->md_buffer.h[7] = 0x5be0cd19;
	}
}

void	init_hash(t_msg *msg)
{
	msg->hash.a = msg->md_buffer.h[0];
	msg->hash.b = msg->md_buffer.h[1];
	msg->hash.c = msg->md_buffer.h[2];
	msg->hash.d = msg->md_buffer.h[3];
	if (msg->algo_choosen == 1)
	{
		msg->hash.e = msg->md_buffer.h[4];
		msg->hash.f = msg->md_buffer.h[5];
		msg->hash.g = msg->md_buffer.h[6];
		msg->hash.h = msg->md_buffer.h[7];
	}
}

void	add_hash(t_msg *msg)
{
	msg->md_buffer.h[0] += msg->hash.a;
	msg->md_buffer.h[1] += msg->hash.b;
	msg->md_buffer.h[2] += msg->hash.c;
	msg->md_buffer.h[3] += msg->hash.d;
	if (msg->algo_choosen == 1)
	{
		msg->md_buffer.h[4] += msg->hash.e;
		msg->md_buffer.h[5] += msg->hash.f;
		msg->md_buffer.h[6] += msg->hash.g;
		msg->md_buffer.h[7] += msg->hash.h;
	}
}

void	preparation(t_msg *msg, t_functions *fct_table)
{
	*(msg->internal_buffer + msg->internal_buffer_len) = 1 << 7;
	msg->internal_buffer_len += 1;
	ft_bzero(msg->internal_buffer + msg->internal_buffer_len,
			MD5_BUFF_SIZE - msg->internal_buffer_len);
	if (msg->internal_buffer_len > 56)
	{
		fct_table->loop((uint32_t *)msg->internal_buffer, msg, fct_table);
		msg->internal_buffer_len = 0;
		ft_bzero(msg->internal_buffer, MD5_BUFF_SIZE);
	}
	if (msg->algo_choosen == 1)
	{
	*(uint64_t *)(msg->internal_buffer + (MD5_BUFF_SIZE - sizeof(uint64_t))) =
		__builtin_bswap64((uint64_t)(msg->original_len * 8));
	}
	else if (msg->algo_choosen == 0)
	{
		*(uint64_t *)(msg->internal_buffer + (MD5_BUFF_SIZE - sizeof(uint64_t))) =
		(uint64_t)(msg->original_len * 8);
	}
	fct_table->loop((uint32_t *)msg->internal_buffer, msg, fct_table);
}
