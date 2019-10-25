/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:53:12 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/25 21:36:38 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H
# include "libft.h"
# include <stdint.h>
# include <stdlib.h>
# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

typedef struct	s_init
{
	uint32_t	h[4];
}				t_init;

typedef struct	s_hash
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
}				t_hash;

typedef struct	s_msg
{
	uint8_t		*content;
	uint8_t		*content_prepared;
	size_t		content_length;
	size_t		length;
	t_init		md_buffer;
	char		*algo_name;
}				t_msg;

typedef struct	s_options
{
	int			p;
	int			q;
	int			r;
	int			s;
	int			start_ac;
	int			is_file;
}				t_options;

/*
**	PARSING
*/
int				algo_finder(char *algo_name);
t_options		parse_options(int ac, char **av);

/*
**	MD5
*/
size_t			md5_padding_calc(t_msg *msg);
int				md5_append_padding(t_msg *msg);
int				md5_append_length(t_msg *msg);
int				md5_preparation(t_msg *msg);
int				md5(uint8_t *content, t_options opt);
void			md5_init_md_buffer(t_msg *msg);
void			md5_loop(t_msg *msg, t_hash *hash, size_t block_index);

/*
**	SHA256
*/
int				sha256(uint8_t *content, t_options opt);

/*
**	UTILS
*/
void			print_output(t_msg *msg, t_options opt);
void			ft_error(int error_code);
void			print_bits(uint8_t *msg, size_t length);
void			print_byte(t_msg *msg);
#endif
