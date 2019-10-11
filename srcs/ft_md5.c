/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:52:55 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/11 11:58:39 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

#include <stdio.h>

uint32_t		g_sintab[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
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

uint32_t		g_tab[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
				5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4,
				11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6,
				10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

size_t	md5_padding_calc(t_msg *msg)
{
	size_t	to_be_add;

	to_be_add = 0;
	if (msg->length > 56 && msg->length < 64)
	{
		msg->length += (64 - msg->length);
		to_be_add = (64 - msg->length);
		printf("SpecialCase: %li\n", to_be_add);
	}
	if (msg->length < 64)
		to_be_add += (448 - (msg->length * 8)) / 8;
	else
		to_be_add += (((msg->length * 8)
			+ (448 - ((msg->length * 8) % 512))) / 8) - msg->length;
	return (to_be_add);
}

int		md5_append_padding(t_msg *msg)
{
	size_t	to_be_add;
	uint8_t	*tmp;

	msg->length = ft_strlen((char *)msg->content);
	msg->content_length = ft_strlen((char *)msg->content);
	if (!(tmp = (uint8_t *)malloc(msg->length + 1)))
		return (0);
	ft_memcpy(tmp, msg->content, msg->length);
	*(tmp + msg->length) = 1 << 7;
	msg->length += 1;
	to_be_add = md5_padding_calc(msg);
	if (!(msg->content_prepared = (uint8_t *)ft_memalloc(msg->length + to_be_add)))
		return (0);
	msg->length += to_be_add;
	ft_memcpy(msg->content_prepared, tmp, msg->length - to_be_add);
	free(tmp);
	return (1);
}

int		md5_append_length(t_msg *msg)
{
	uint8_t	*tmp;

	if (!(tmp = (uint8_t *)ft_memalloc(msg->length + sizeof(uint64_t))))
		return (0);
	ft_memcpy(tmp, msg->content_prepared, msg->length);
	*(uint64_t *)(tmp + msg->length) = (uint64_t)msg->content_length;
	free(msg->content_prepared);
	msg->content_prepared = tmp;
	print_bits(msg->content, msg->content_length);
	print_bits(msg->content_prepared, msg->length + sizeof(uint64_t));
	msg->length += sizeof(uint64_t);
	return (1);
}

int		md5_preparation(t_msg *msg)
{
	md5_append_padding(msg);
	md5_append_length(msg);
	md5_loop(msg);
	return (1);
}

int		md5_loop(t_msg *msg)
{
	size_t		block_index;
	size_t		idx;
	uint64_t	tmp;
	t_hash		hash;

	block_index = 0;
	msg->md_buffer.h0 = 0x67452301;
	msg->md_buffer.h1 = 0xEFCDAB89;
	msg->md_buffer.h2 = 0x98BADCFE;
	msg->md_buffer.h3 = 0x10325476;
	while (block_index < msg->length)
	{
		hash.a = msg->md_buffer.h0;
		hash.b = msg->md_buffer.h1;
		hash.c = msg->md_buffer.h2;
		hash.d = msg->md_buffer.h3;
		idx = 0;
		while (idx < 64)
		{
			if (idx < 16)
			{
				hash.f = (hash.b & hash.c) | ((~hash.b) & hash.d);
				hash.g = idx;
			}
			else if (idx > 15 && idx < 32)
			{
				hash.f = (hash.d & hash.b) | ((~hash.d) & hash.c);
				hash.g = (5 * idx + 1) % 16;
			}
			else if (idx > 31 && idx < 48)
			{
				hash.f = hash.b ^ hash.c ^ hash.d;
				hash.g = (3 * idx + 5) % 16;
			}
			else if (idx > 47 && idx < 64)
			{
				hash.f = hash.c ^ (hash.b | (~hash.d));
				hash.g = (7 * idx) % 16;
			}
			tmp = hash.d;
			hash.d = hash.c;
			hash.c = hash.b;
			hash.b = ((hash.a + hash.f + g_sintab[idx] + *(msg->content_prepared + block_index + hash.g)) << g_tab[idx]) + hash.b;
			hash.a = tmp;
			idx++;
		}
		msg->md_buffer.h0 += hash.a;
		msg->md_buffer.h1 += hash.b;
		msg->md_buffer.h2 += hash.c;
		msg->md_buffer.h3 += hash.d;
		block_index += 64;
	}
	printf("%x%x%x%x\n", msg->md_buffer.h0, msg->md_buffer.h1, msg->md_buffer.h2, msg->md_buffer.h3); 
	return (1);
}
