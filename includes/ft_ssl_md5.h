/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:53:12 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/10 21:34:12 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H
# include "libft.h"
# include <stdint.h>
# include <stdlib.h>

typedef struct	s_msg
{
	uint8_t		*content;
	uint8_t		*content_prepared;
	size_t		content_length;
	size_t		length;
}				t_msg;

size_t			md5_padding_calc(t_msg *msg);
int				md5_append_padding(t_msg *msg);
int				md5_preparation(t_msg *msg);

// UTILS
void		print_bits(uint8_t *msg, size_t length);
#endif
