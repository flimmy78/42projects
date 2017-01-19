/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 15:34:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 19:23:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (dst == NULL || src == NULL)
		return (0);
	i = ft_strlen(dst);
	j = 0;
	if (size > i)
	{
		while (src[j] && (i + j) < size - 1)
		{
			dst[i + j] = src[j];
			++j;
		}
		return (ft_strlen(src) + i);
	}
	return (ft_strlen(src) + size);
}
