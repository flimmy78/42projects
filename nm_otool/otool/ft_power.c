/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 15:35:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/14 19:01:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int				ft_power(int nb, int power)
{
	int			ret;

	ret = 1;
	while (power--)
		ret *= nb;
	return (ret);
}
