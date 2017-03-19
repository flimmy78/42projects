/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 05:18:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/19 05:17:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void			search_channel(char **cmds, t_fd *cl, t_env *e)
{
	t_chan			*ch;

	ch = e->chans;
	while (ch)
	{
		if (!sv_strcmp(ch->name, cmds[1]))
			return (sv_channel_mode(cmds + 2, ch, cl));
		ch = ch->next;
	}
	sv_err(ERR_NOSUCHCHANNEL, cmds[1], NULL, cl);
}

static void			search_user(char **cmds, t_fd *cl, t_env *e)
{
	t_fd			*us;

	us = e->fds;
	while (us)
	{
		if (!sv_strcmp(us->reg.nick, cmds[1]))
			return (sv_user_mode(cmds + 2, us, cl));
		us = us->next;
	}
	sv_err(ERR_NOSUCHCHANNEL, cmds[1], NULL, cl);
}

void				sv_mode(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || !cmds[2])
		return (sv_err(ERR_NEEDMOREPARAMS, "MODE", NULL, cl));
	if (ISCHAN(*cmds[1]))
		search_channel(cmds, cl, e);
	else
		search_user(cmds, cl, e);
}
