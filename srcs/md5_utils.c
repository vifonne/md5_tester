/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:29:05 by vifonne           #+#    #+#             */
/*   Updated: 2019/11/15 12:25:34 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	md5_preparation(t_msg *msg, t_functions *fct_table)
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
	*(uint64_t *)(msg->internal_buffer + (MD5_BUFF_SIZE - sizeof(uint64_t))) =
		(uint64_t)(msg->original_len * 8);
	fct_table->loop((uint32_t *)msg->internal_buffer, msg, fct_table);
}
