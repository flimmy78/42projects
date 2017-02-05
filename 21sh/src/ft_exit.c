/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 12:41:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/05 01:10:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		free_and_exit(char **args)
{
	update_history();
	ft_free(&e.env);
	ft_free(&e.path);
	ft_free_hist(&e.hist);
	ft_free(&args);
	if (e.histpath)
		free(e.histpath);
	if (e.cpy.str)
		free(e.cpy.str);
	restore_term();
	ft_bzero(&e, sizeof(e));
	ft_putendl_fd("exit", e.fd);
	exit(e.ret);
}

int				ft_exit(char **args, char ***env)
{
	(void)env;
	if (!args || !args[1])
		free_and_exit(args);
	if (args[2])
		ft_putendl_fd("exit: Too many arguments.", 2);
	else
	{
		e.ret = ft_atoi(args[1]);
		free_and_exit(args);
	}
	return (-1);
}
