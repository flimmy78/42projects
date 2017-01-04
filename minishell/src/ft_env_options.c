/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 21:50:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/04 21:49:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**ft_new_env(t_opt *opt, int k)
{
	char		**new;
	int			i;

	if ((new = (char **)malloc(ft_tablen(opt->cpy) - 1)) == NULL)
		return (NULL);
	i = 0;
	while (opt->cpy && opt->cpy[i])
	{
		if (i < k)
			new[i] = opt->cpy[i];
		else if (i > k)
			new[i - 1] = opt->cpy[i];
		i++;
	}
	if (i > 0)
		new[i - 1] = NULL;
	else
		new[i] = NULL;
	return (new);
}

int				ft_opt_u(t_opt *opt)
{
	int			i;
	int			j;

	i = 0;
	if (opt->ptr == NULL || opt->ptr[0] == '\0')
		return (ft_enverror("option requires an argument", 'u', opt));
	while (opt->ptr[i])
	{
		if (opt->v)
		{
			ft_putstr("#env unset:\t");
			ft_putendl(opt->ptr[i]);
		}
		j = 0;
		while (opt->cpy && opt->cpy[j])
		{
			if (ft_strcmp(opt->cpy[j], opt->ptr[i]) == '=' &&
				(opt->cpy = ft_new_env(opt, i)) == NULL)
				return (ft_enverror("malloc failed", 0, opt));
			j++;
		}
		i++;
	}
	return (0);
}

int				ft_opt_i(t_opt *opt)
{
	if (opt->v)
		ft_putendl("#env clearing environ");
	ft_free(&opt->cpy);
	return (0);
}

static char		*ft_search_path(char *cmd, t_opt *opt)
{
	struct stat	buffer;
	char		**paths;
	char		*tmp;
	int			i;

	if ((paths = ft_strsplit(opt->path, ':')) == NULL)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = (paths[i][ft_strlen(paths[i]) - 1] != '/') ?
			ft_strjoin(paths[i], "/") : ft_strdup(paths[i]);
		cmd = ft_strjoin(tmp, cmd);
		if (tmp)
			free(tmp);
		if (stat(cmd, &buffer) != -1 && access(cmd, F_OK) == 0)
			break ;
		free(cmd);
		cmd = NULL;
		i++;
	}
	ft_free(&paths);
	return (cmd);
}

int				ft_opt_p(t_opt *opt, char **cmd)
{
	int			i;

	i = 0;
	if (opt->path == NULL || opt->path[0] == '\0')
		return (ft_enverror("option requires an argument", 'P', opt));
	if ((opt->cmd = ft_search_path(cmd[0], opt)) == NULL)
		return (ft_enverror("No such file or directory", 0, opt));
	free(cmd[0]);
	cmd[0] = opt->cmd;
	opt->cmd = NULL;
	if (opt->v)
	{
		ft_putstr("#env executing: ");
		ft_putendl(cmd[i]);
		while (cmd[i])
		{
			ft_putstr("#env\targ[");
			ft_putnbr(i);
			ft_putstr("]= '");
			ft_putstr(cmd[i]);
			ft_putendl("'");
			i++;
		}
	}
	return (0);
}
