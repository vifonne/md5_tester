/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:24:29 by vifonne           #+#    #+#             */
/*   Updated: 2019/01/14 17:45:37 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_list(t_list **begin_list)
{
	t_list	*tmp;

	tmp = *begin_list;
	if (tmp)
	{
		while (tmp)
		{
			ft_putendl(tmp->data);
			tmp = tmp->next;
		}
		ft_putchar('\n');
	}
}
