/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:53:12 by vifonne           #+#    #+#             */
/*   Updated: 2019/11/08 11:52:25 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H
# include "libft.h"
# include <stdint.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# define MD5_BUFF_SIZE 64
# define READ_BUFF_SIZE 4096

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
	uint8_t		internal_buffer[MD5_BUFF_SIZE];
	size_t		internal_buffer_len;
	size_t		original_len;
	char		*algo_name;
	char		*filename;
	t_init		md_buffer;
	t_hash		hash;
}				t_msg;

typedef struct	s_options
{
	int			p;
	int			q;
	int			r;
	int			s;
}				t_options;

/*
**	PARSING
*/
int				algo_finder(char *algo_name);
t_options		parse_options(int ac, char **av);

/*
**	MD5
*/
void			md5_init_md_buffer(t_msg *msg);
void			md5_init_hash(t_msg *msg);
void			md5_add_hash(t_msg *msg);
void			md5_preparation(t_msg *msg);
void			md5_string(uint8_t *str, ssize_t length, t_msg *msg);
void			md5_loop(uint32_t *buffer, t_msg *msg);
int				md5(char *str, t_options opt);

/*
**	SHA256
*/
int				sha256(char *str, t_options opt);

/*
**	UTILS
*/
void			print_output(t_msg *msg, t_options opt);
void			ft_error(int error_code);
void			print_bits(uint8_t *msg, size_t length);
void			print_byte(t_msg *msg);
#endif
