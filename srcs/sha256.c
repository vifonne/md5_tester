/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:02:10 by vifonne           #+#    #+#             */
/*   Updated: 2019/11/10 16:35:13 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

uint32_t	g_sha256_sintab[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf,
	0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74,
	0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc,
	0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85,
	0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb,
	0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70,
	0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3,
	0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
	0xc67178f2};

void		sha256_word_extend(uint32_t *buffer)
{
	size_t		idx;
	uint32_t	ss0;
	uint32_t	ss1;

	idx = 0;
	while (idx < 16)
	{
		buffer[idx] = __builtin_bswap32(buffer[idx]);
		idx++;
	}
	while (idx < 64)
	{
		ss0 = ROTATE_RIGHT(buffer[idx - 15], 7) ^ ROTATE_RIGHT(buffer[idx - 15], 18) ^ (buffer[idx - 15] >> 3);
		ss1 = ROTATE_RIGHT(buffer[idx - 2], 17) ^ ROTATE_RIGHT(buffer[idx - 2], 19) ^ (buffer[idx - 2] >> 10);
		buffer[idx] = buffer[idx - 16] + ss0 + buffer[idx - 7] + ss1;
		idx++;
	}
}

uint32_t	s1(t_msg *msg)
{
	return (ROTATE_RIGHT(msg->hash.e, 6) ^ ROTATE_RIGHT(msg->hash.e, 11) ^ ROTATE_RIGHT(msg->hash.e, 25));
}

uint32_t	ch(t_msg *msg)
{
	return ((msg->hash.e & msg->hash.f) ^ ((~msg->hash.e) & msg->hash.g));
}

uint32_t	temp1(t_msg *msg, uint32_t s1, uint32_t ch, uint32_t *buffer, size_t idx)
{
	return (msg->hash.h + s1 + ch + g_sha256_sintab[idx] + buffer[idx]);
}

uint32_t	s0(t_msg *msg)
{
	return (ROTATE_RIGHT(msg->hash.a, 2) ^ ROTATE_RIGHT(msg->hash.a, 13) ^ ROTATE_RIGHT(msg->hash.a, 22));
}

uint32_t	maj(t_msg *msg)
{
	return ((msg->hash.a & msg->hash.b) ^ (msg->hash.a & msg->hash.c) ^ (msg->hash.b & msg->hash.c));
}

uint32_t	temp2(uint32_t s0, uint32_t maj)
{
	return (s0 + maj);
}

void		sha256_loop(uint32_t *buffer, t_msg *msg)
{
	uint32_t	tmp1;
	uint32_t	tmp2;
	size_t		idx;

	idx = 0;
	sha256_word_extend(buffer);
	sha256_init_hash(msg);
	while (idx < 64)
	{
		tmp1 = temp1(msg, s1(msg), ch(msg), buffer, idx);
		tmp2 = temp2(s0(msg), maj(msg));
		msg->hash.h = msg->hash.g;
		msg->hash.g = msg->hash.f;
		msg->hash.f = msg->hash.e;
		msg->hash.e = msg->hash.d + tmp1;
		msg->hash.d = msg->hash.c;
		msg->hash.c = msg->hash.b;
		msg->hash.b = msg->hash.a;
		msg->hash.a = tmp1 + tmp2;
		idx++;
	}
	sha256_add_hash(msg);
}

void		sha256_read_from_fd(int fd, t_msg *msg)
{
	ssize_t	ret;
	char	read_buffer[READ_BUFF_SIZE];

	while ((ret = read(fd, read_buffer, READ_BUFF_SIZE)) > 0)
	{
		write(1, read_buffer, ret);
		msg->original_len += ret;
		sha256_string((uint8_t *)read_buffer, ret, msg);
	}
	ft_putchar('\n');
	sha256_preparation(msg);
}

void		sha256_string(uint8_t *str, ssize_t length, t_msg *msg)
{
	ssize_t		cpy_len;
	uint32_t	sha_buff[64];

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
			sha256_loop((uint32_t *)msg->internal_buffer, msg);
			msg->internal_buffer_len = 0;
		}
	}
	while (length >= 64)
	{
		ft_memcpy(sha_buff, str, 64);
		sha256_loop(sha_buff, msg);
		str += 64;
		length -= 64;
	}
	if (length > 0)
	{
		ft_memcpy(msg->internal_buffer, str, length);
		msg->internal_buffer_len = length;
	}
}

int		sha256(char *str, t_options opt)
{
	int		fd;
	t_msg	*msg;

	if (!(msg = (t_msg *)ft_memalloc(sizeof(t_msg))))
		return (0);
	msg->algo_name = "SHA256";
	msg->filename = str;
	sha256_init_md_buffer(msg);
	if (opt.s == 1)
	{
		msg->original_len += ft_strlen(str);
		sha256_string((uint8_t *)str, (ssize_t)msg->original_len, msg);
		sha256_preparation(msg);
	}
	else
	{
		if (str == NULL)
		{
			fd = 0;
		}
		else
		{
			fd = open(str, O_RDONLY);
			if (fd < 0)
			{
				free(msg);
				return (0);
			}
		}
		sha256_read_from_fd(fd, msg);
		close(fd);
	}
	print_byte_256(msg);
	free(msg);
	return (1);
}
