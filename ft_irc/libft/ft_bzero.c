/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 17:50:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/10 14:02:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		ft_bzero(void *s, size_t n)
{
	char	*x;
	size_t	i;

	i = 0;
	if (n && s)
	{
		x = s;
		while (i++ < n)
			*x++ = 0;
	}
}