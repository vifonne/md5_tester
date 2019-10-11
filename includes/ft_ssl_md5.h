/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:53:12 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/11 11:50:04 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H
# include "libft.h"
# include <stdint.h>
# include <stdlib.h>

typedef struct	s_init
{
	uint64_t		h0;
	uint64_t		h1;
	uint64_t		h2;
	uint64_t		h3;
}				t_init;

typedef struct	s_hash
{
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
}				t_hash;

typedef struct	s_msg
{
	uint8_t		*content;
	uint8_t		*content_prepared;
	size_t		content_length;
	size_t		length;
	t_init		md_buffer;
}				t_msg;

size_t			md5_padding_calc(t_msg *msg);
int				md5_append_padding(t_msg *msg);
int				md5_preparation(t_msg *msg);
int				md5_loop(t_msg *msg);

// UTILS
void		print_bits(uint8_t *msg, size_t length);
#endif
