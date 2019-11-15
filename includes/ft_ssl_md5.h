/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:53:12 by vifonne           #+#    #+#             */
/*   Updated: 2019/11/15 14:13:46 by vifonne          ###   ########.fr       */
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
# define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32-(n))))
# define MD5_BUFF_SIZE 64
# define READ_BUFF_SIZE 4096

typedef struct	s_init
{
	uint32_t	h[8];
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
	uint32_t	h;
}				t_hash;

typedef struct	s_msg
{
	uint8_t		internal_buffer[256];
	size_t		internal_buffer_len;
	size_t		original_len;
	char		*algo_name;
	int			algo_choosen;
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

typedef struct	s_functions
{
	int			(*hash_main)(char *str, struct s_functions *fct_table, t_options opt, int algo_choosen);
	ssize_t		(*basic_string)(uint8_t *str, ssize_t lenbth, t_msg *msg, struct s_functions *fct_table);
	void		(*read_from_fd)(int fd, t_msg *msg, struct s_functions *fct_table, t_options opt);
	void		(*init_md_buffer)(t_msg *msg);
	void		(*init_hash)(t_msg *msg);
	void		(*add_hash)(t_msg *msg);
	void		(*preparation)(t_msg *msg, struct s_functions *fct_table);
	void		(*string)(uint8_t *str, ssize_t length, t_msg *msg, struct s_functions *fct_table);
	void		(*loop)(uint32_t *buffer, t_msg *msg, struct s_functions *fct_table);
}				t_functions;

/*
**	COMMON
*/
void			read_from_fd(int fd, t_msg *msg, t_functions *fct_table, t_options opt);
ssize_t			basic_string(uint8_t *str, ssize_t length, t_msg *msg, t_functions *fct_table);
void			init_md_buffer(t_msg *msg);
void			init_hash(t_msg *msg);
void			add_hash(t_msg *msg);
void			preparation(t_msg *msg, t_functions *fct_table);
int				hash_main(char *str, t_functions *fct_table, t_options opt, int algo_choosen);
/*
**	PARSING
*/
int				algo_finder(char *algo_name);
t_options		parse_options(int ac, char **av);

/*
**	MD5
*/
void			md5_string(uint8_t *str, ssize_t length, t_msg *msg, t_functions *fct_table);
void			md5_loop(uint32_t *buffer, t_msg *msg, t_functions *fct_table);

/*
**	SHA256
*/
void			sha256_string(uint8_t *str, ssize_t length, t_msg *msg, t_functions *fct_table);
void			sha256_loop(uint32_t *buffer, t_msg *msg, t_functions *fct_table);

/*
**	UTILS
*/
uint32_t		bswap_32(uint32_t bytes);
uint64_t		bswap_64(uint64_t bytes);
void			print_output(t_msg *msg, t_options opt);
void			ft_error(int error_code);
void			print_bits(uint8_t *msg, size_t length);
void			print_byte(t_msg *msg);
void			print_byte_256(t_msg *msg);
#endif
