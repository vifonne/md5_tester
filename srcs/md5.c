/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:52:55 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/27 16:02:09 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include <stdio.h>

uint32_t	g_sintab[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

uint32_t	g_tab[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4,
	11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6,
	10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

void		md5_if_forest(t_msg *msg, size_t idx)
{
	if (idx < 16)
	{
		msg->hash.f = (msg->hash.b & msg->hash.c) | ((~msg->hash.b) & msg->hash.d);
		msg->hash.g = idx;
	}
	else if (idx < 32)
	{
		msg->hash.f = (msg->hash.d & msg->hash.b) | ((~msg->hash.d) & msg->hash.c);
		msg->hash.g = (5 * idx + 1) % 16;
	}
	else if (idx < 48)
	{
		msg->hash.f = msg->hash.b ^ msg->hash.c ^ msg->hash.d;
		msg->hash.g = (3 * idx + 5) % 16;
	}
	else if (idx < 64)
	{
		msg->hash.f = msg->hash.c ^ (msg->hash.b | (~msg->hash.d));
		msg->hash.g = (7 * idx) % 16;
	}
}

void		md5_loop(uint32_t *buffer, t_msg *msg)
{
	uint32_t	tmp;
	size_t		idx;

	idx = 0;
	md5_init_hash(msg);
	while (idx < 64)
	{
		md5_if_forest(msg, idx);
		tmp = msg->hash.d;
		msg->hash.d = msg->hash.c;
		msg->hash.c = msg->hash.b;
		msg->hash.b = ROTATE_LEFT((msg->hash.a + msg->hash.f + g_sintab[idx]
					+ *(buffer + msg->hash.g)), g_tab[idx])
			+ msg->hash.b;
		msg->hash.a = tmp;
		idx++;
	}
	md5_add_hash(msg);
}

void		read_from_fd(int fd, t_msg *msg)
{
	ssize_t	ret;
	char	read_buffer[READ_BUFF_SIZE];

	while ((ret = read(fd, read_buffer, READ_BUFF_SIZE)) > 0)
	{
		msg->original_len += ret;
		md5_string((uint8_t *)read_buffer, ret, msg);
	}
	md5_preparation(msg);
}

void		md5_string(uint8_t *str, ssize_t length, t_msg *msg)
{
	ssize_t 	cpy_len;

	if (msg->internal_buffer_len > 0)
	{
		cpy_len = MD5_BUFF_SIZE - msg->internal_buffer_len;
		if (length < cpy_len)
			cpy_len = length;
		ft_memcpy(msg->internal_buffer + msg->internal_buffer_len, str, cpy_len);
		msg->internal_buffer_len += cpy_len;
		length -= cpy_len;
		if (msg->internal_buffer_len == MD5_BUFF_SIZE)
		{
			md5_loop((uint32_t *)msg->internal_buffer, msg);
			msg->internal_buffer_len = 0;
		}
	}
	while (length >= 64)
	{
		md5_loop((uint32_t *)str, msg);
		str += 64;
		length -= 64;
	}
	if (length > 0)
	{
		ft_memcpy(msg->internal_buffer, str, length);
		msg->internal_buffer_len = length;
	}
}

int			md5(char *str, t_msg *msg, t_options opt)
{
	int	fd;

	fd = 0;
	msg->algo_name = "MD5";
	msg->filename = str;
	md5_init_md_buffer(msg);
	if (opt.s == 1)
	{
		msg->original_len += ft_strlen(str);
		md5_string((uint8_t *)str, (ssize_t)msg->original_len, msg);
		md5_preparation(msg);
	}
	else
	{
		if (opt.is_stdin == 0)
		{
			fd = open(str, O_RDONLY);
			if (fd < 0)
				return (0);
		}
		read_from_fd(fd, msg);
		close(fd);
	}
	print_output(msg, opt);
	return (1);
}
