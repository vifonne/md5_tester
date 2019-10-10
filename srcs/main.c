/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:17:48 by vifonne           #+#    #+#             */
/*   Updated: 2019/10/10 21:20:01 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ssl_md5.h"

int		main(int ac, char **av)
{
	t_msg	*msg;

	if (!(msg = (t_msg *)ft_memalloc(sizeof(t_msg))))
		return (0);
	if (ac > 1)
	{
		msg->content = (uint8_t *)av[1];
		md5_preparation(msg);
	}
	return (0);
}
