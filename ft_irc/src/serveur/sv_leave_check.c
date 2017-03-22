/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_leave_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:41:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 20:47:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_send_more(char **cmd, t_fd *us)
{
	send(us->fd, ":", 1, 0);
	send(us->fd, *cmd, ft_strlen(*cmd), 0);
	cmd++;
	while (*cmd)
	{
		send(us->fd, " ", 1, 0);
		send(us->fd, *cmd, ft_strlen(*cmd), 0);
		cmd++;
	}
}

static void		sv_send_leavemsg(char **cmd, t_chan *chan, t_fd *cl)
{
	t_listin	*list;
	t_fd		*us;

	list = chan->users;
	while (list)
	{
		us = (t_fd *)list->is;
		if (!(chan->cmode & CHFL_QUIET) || us->fd == cl->fd)
		{
			send(us->fd, ":", 1, 0);
			send(us->fd, cl->reg.nick, NICK_LEN, 0);
			send(us->fd, "!~", 2, 0);
			send(us->fd, cl->reg.username, USERNAME_LEN, 0);
			send(us->fd, "@", 1, 0);
			send(us->fd, cl->addr, ADDR_LEN, 0);
			send(us->fd, " LEAVE ", 7, 0);
			send(us->fd, chan->name, CHANNAME_LEN, 0);
			if (*cmd)
				sv_send_more(cmd, us);
			send(us->fd, END_CHECK, END_CHECK_LEN, 0);
		}
		list = list->next;
	}
}

static void		sv_find_chaninuser(t_chan *chan, t_fd *cl)
{
	t_listin	*tmp;

	tmp = cl->chans;
	while (tmp && sv_strcmp(((t_chan *)tmp->is)->name, chan->name))
		tmp = tmp->next;
	if (tmp == NULL)
		return (sv_err(ERR_NOTONCHANNEL, chan->name, NULL, cl));
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		cl->chans = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	tmp->is = NULL;
	free(tmp);
	tmp = NULL;
}

void			sv_find_userinchan(char **cmd, t_chan *chan, t_fd *cl)
{
	t_listin	*tmp;

	tmp = chan->users;
	while (tmp && sv_strcmp(((t_fd *)tmp->is)->reg.nick, cl->reg.nick))
		tmp = tmp->next;
	if (tmp == NULL)
		return (sv_err(ERR_NOTONCHANNEL, chan->name, NULL, cl));
	chan->nbusers--;
	cl->chansnb--;
	sv_send_leavemsg(cmd, chan, cl);
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		chan->users = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	tmp->is = NULL;
	free(tmp);
	tmp = NULL;
	sv_find_chaninuser(chan, cl);
}