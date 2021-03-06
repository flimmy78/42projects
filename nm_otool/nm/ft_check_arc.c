/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 09:44:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 11:20:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void				ft_check_arc(void *file, t_base *env, void *start)
{
	t_arc			*tmp;
	t_arc			*new;
	char			*name;
	size_t			len;

	tmp = env->arc;
	while (tmp && file < env->file + env->file_size)
	{
		env->ar_hdr = (struct ar_hdr *)file;
		ft_ar_name(env->ar_hdr, &name, &len);
		if (ft_strcmp(tmp->name, name) != 0 && ft_strncmp(name, ARMAG, SARMAG))
		{
			new = ft_init_plus(start, file, tmp);
			ft_ar_name(env->ar_hdr, &new->name, &new->len);
			if (tmp->prev)
				tmp->prev->next = new;
			else
				env->arc = new;
			tmp->prev = new;
		}
		else if (tmp->next)
			tmp = tmp->next;
		file += (ft_atoi(env->ar_hdr->ar_size) + sizeof(*env->ar_hdr));
	}
}

void				ft_double_check_arc(void *file, t_base *env, void *start)
{
	t_arc			*tmp;
	char			*name;
	size_t			len;

	env->arc = ft_init_miss(start, file, NULL);
	ft_ar_name(file, &env->arc->name, &env->arc->len);
	tmp = env->arc;
	while (file < env->file + env->file_size)
	{
		env->ar_hdr = (struct ar_hdr *)file;
		ft_ar_name(env->ar_hdr, &name, &len);
		if (ft_strcmp(tmp->name, name) != 0 && ft_strncmp(name, ARMAG, SARMAG))
		{
			tmp->next = ft_init_miss(start, file, tmp);
			ft_ar_name(env->ar_hdr, &tmp->next->name, &tmp->next->len);
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		file += (ft_atoi(env->ar_hdr->ar_size) + sizeof(*env->ar_hdr));
	}
}
