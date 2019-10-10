/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:53:12 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/10 15:55:47 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H
# include "libft.h"
# include <stdint.h>
# include <stdlib.h>

uint8_t		*md5_padding(uint8_t *msg);
uint8_t		*md5(uint8_t *msg);

// UTILS
void		print_bits(uint8_t *msg, size_t length);
#endif
