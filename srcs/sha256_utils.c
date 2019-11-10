/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 13:52:26 by vifonne           #+#    #+#             */
/*   Updated: 2019/11/10 17:30:02 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	sha256_init_md_buffer(t_msg *msg)
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

void	sha256_init_hash(t_msg *msg)
{
	msg->hash.a = msg->md_buffer.h[0];
	msg->hash.b = msg->md_buffer.h[1];
	msg->hash.c = msg->md_buffer.h[2];
	msg->hash.d = msg->md_buffer.h[3];
	msg->hash.e = msg->md_buffer.h[4];
	msg->hash.f = msg->md_buffer.h[5];
	msg->hash.g = msg->md_buffer.h[6];
	msg->hash.h = msg->md_buffer.h[7];
}

void	sha256_add_hash(t_msg *msg)
{
	msg->md_buffer.h[0] += msg->hash.a;
	msg->md_buffer.h[1] += msg->hash.b;
	msg->md_buffer.h[2] += msg->hash.c;
	msg->md_buffer.h[3] += msg->hash.d;
	msg->md_buffer.h[4] += msg->hash.e;
	msg->md_buffer.h[5] += msg->hash.f;
	msg->md_buffer.h[6] += msg->hash.g;
	msg->md_buffer.h[7] += msg->hash.h;
}

void	sha256_preparation(t_msg *msg)
{
	*(msg->internal_buffer + msg->internal_buffer_len) = 1 << 7;
	msg->internal_buffer_len += 1;
	ft_bzero(msg->internal_buffer + msg->internal_buffer_len,
			MD5_BUFF_SIZE - msg->internal_buffer_len);
	if (msg->internal_buffer_len > 56)
	{
		sha256_loop((uint32_t *)msg->internal_buffer, msg);
		msg->internal_buffer_len = 0;
		ft_bzero(msg->internal_buffer, MD5_BUFF_SIZE);
	}
	*(uint64_t *)(msg->internal_buffer + (MD5_BUFF_SIZE - sizeof(uint64_t))) =
		__builtin_bswap64((uint64_t)(msg->original_len * 8));
	sha256_loop((uint32_t *)msg->internal_buffer, msg);
}
