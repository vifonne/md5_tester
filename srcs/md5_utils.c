/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:29:05 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/27 16:00:36 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	md5_init_md_buffer(t_msg *msg)
{
	msg->md_buffer.h[0] = 0x67452301;
	msg->md_buffer.h[1] = 0xEFCDAB89;
	msg->md_buffer.h[2] = 0x98BADCFE;
	msg->md_buffer.h[3] = 0x10325476;
}

void		md5_init_hash(t_msg *msg)
{
	msg->hash.a = msg->md_buffer.h[0];
	msg->hash.b = msg->md_buffer.h[1];
	msg->hash.c = msg->md_buffer.h[2];
	msg->hash.d = msg->md_buffer.h[3];
}

void		md5_add_hash(t_msg *msg)
{
	msg->md_buffer.h[0] += msg->hash.a;
	msg->md_buffer.h[1] += msg->hash.b;
	msg->md_buffer.h[2] += msg->hash.c;
	msg->md_buffer.h[3] += msg->hash.d;
}

void	md5_preparation(t_msg *msg)
{
	*(msg->internal_buffer + msg->internal_buffer_len) = 1 << 7;
	msg->internal_buffer_len += 1;
	ft_bzero(msg->internal_buffer + msg->internal_buffer_len,
			MD5_BUFF_SIZE - msg->internal_buffer_len);
	if (msg->internal_buffer_len > 56)
	{
		md5_loop((uint32_t *)msg->internal_buffer, msg);
		msg->internal_buffer_len = 0;
		ft_bzero(msg->internal_buffer, MD5_BUFF_SIZE);
	}
	*(uint64_t *)(msg->internal_buffer + (MD5_BUFF_SIZE - sizeof(uint64_t))) =
		(uint64_t)(msg->original_len * 8);
	md5_loop((uint32_t *)msg->internal_buffer, msg);
}
