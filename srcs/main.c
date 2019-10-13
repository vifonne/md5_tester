/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:17:48 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/13 16:23:42 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

char	*g_algo_name_tab[3] = {"md5", "sha256", 0};
int		(*g_algo_fct_tab[2]) (char **av) = {&md5, &sha256};

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

int		main(int ac, char **av)
{
	int	algo_choosen;

	if (ac > 2)
	{
		algo_choosen = algo_finder(av[1]);
		if (algo_choosen == -1)
		{
			ft_error(-1);
		}
		else
		{
			if (!g_algo_fct_tab[algo_choosen](av + 2))
				ft_error(-1);
		}
	}
	return (0);
}
