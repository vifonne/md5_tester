/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:17:48 by vifonne           #+#    #+#             */
/*   Updated: 2019/11/15 13:33:44 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

char	*g_algo_name_tab[3] = {"md5", "sha256", 0};


int		algo_finder(char *algo_name)
{
	size_t	idx;

	idx = 0;
	while (g_algo_name_tab[idx] != NULL)
	{
		if (ft_strequ(algo_name, g_algo_name_tab[idx]) == 1)
			return (idx);
		idx++;
	}
	return (-1);
}

int		no_options(t_options opt)
{
	if (opt.p == 0 && opt.q == 0 && opt.r == 0 && opt.s == 0)
		return (1);
	return (0);
}

t_functions	set_fct_table(int algo_choosen)
{
	t_functions		fct_table;

	fct_table.hash_main = hash_main;
	fct_table.basic_string = basic_string;
	fct_table.read_from_fd = read_from_fd;
	fct_table.init_md_buffer = init_md_buffer;
	fct_table.init_hash = init_hash;
	fct_table.add_hash = add_hash;
	fct_table.preparation = preparation;
	if (algo_choosen == 0)
	{
		fct_table.string = md5_string;
		fct_table.loop = md5_loop;
	}
	else
	{
		fct_table.string = sha256_string;
		fct_table.loop = sha256_loop;
	}
	return (fct_table);
}

int		parse_opt(char *str, t_options *opt)
{
	char		*opts;
	size_t		idx;

	idx = 0;
	opts = "pqrs";
	while (str[idx] != '\0')
	{
		if (ft_strchr(opts, str[idx]) != 0)
		{
			if (str[idx] == 's')
			{
				opt->s = 1;
				if (idx + 1 < ft_strlen(str))
					return (idx);
				else
					return (0);
			}
			else if (str[idx] == 'p')
				opt->p = 1;
			else if (str[idx] == 'q')
				opt->q = 1;
			else if (str[idx] == 'r')
				opt->r = 1;
			else
				return (-1);
		}
		idx++;
	}
	return (0);
}

int		get_opt(int ac, char **av, int algo_choosen)
{
	size_t		arg_idx;
	int			tmp;
	int			s_tmp;
	t_options	opt;
	t_functions	fct_table;

	arg_idx = 0;
	opt = (t_options){0, 0, 0, 0};
	fct_table = set_fct_table(algo_choosen);
	while (arg_idx < (size_t)ac)
	{
		if (av[arg_idx][0] == '-')
		{
			tmp = parse_opt(av[arg_idx], &opt);
			if (opt.p == 1)
			{
				s_tmp = opt.s;
				opt.s = 0;
				fct_table.hash_main(NULL, &fct_table, opt, algo_choosen);
				opt.p = 0;
				opt.s = s_tmp;
			}
			if (tmp > 0)
			{
				fct_table.hash_main(av[arg_idx] + tmp + 1, &fct_table, opt, algo_choosen);
				opt.s = 0;
			}
		}
		else
		{
			fct_table.hash_main(av[arg_idx], &fct_table, opt, algo_choosen);
			opt.p = 0;
			opt.s = 0;
		}
		arg_idx++;
	}
	return (1);
}

int		main(int ac, char **av)
{
	int			algo_choosen;

	if (ac > 1)
	{
		algo_choosen = algo_finder(av[1]);
		if (algo_choosen == -1)
			ft_error(-1);
		else
			get_opt(ac - 1, av + 1, algo_choosen);
	}
	return (0);
}
