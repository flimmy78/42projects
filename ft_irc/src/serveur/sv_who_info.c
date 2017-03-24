/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_who_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 13:30:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 20:29:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_info_next(t_fd *user, t_fd *cl)
{
	t_listin	*li;
	char		**tmp;

	li = user->chans;
	if (user->reg.umode & USR_OP || user->reg.umode & USR_LOCALOP)
		sv_cl_write("*", &cl->wr);
	if (li && li->mode & CHFL_CHANOP)
		sv_cl_write("@", &cl->wr);
	if (li && li->mode & CHFL_VOICE)
		sv_cl_write("+", &cl->wr);
	sv_cl_write(" :0", &cl->wr);
	tmp = user->reg.realname;
	while (tmp && *tmp)
	{
		sv_cl_write(" ", &cl->wr);
		sv_cl_write(*tmp, &cl->wr);
		tmp++;
	}
	sv_cl_write(END_CHECK, &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
}

void			sv_who_info(t_fd *us, t_fd *cl, t_env *e)
{
	sv_cl_write(e->name, &cl->wr);
	sv_cl_write(" 352 ", &cl->wr);
	sv_cl_write(cl->reg.nick, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	if (us->chans)
		sv_cl_write(((t_chan *)us->chans->is)->name, &cl->wr);
	else
		sv_cl_write("*", &cl->wr);
	sv_cl_write(" ~", &cl->wr);
	sv_cl_write(us->reg.username, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(us->addr, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(e->name + 1, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(us->reg.nick, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	if (us->reg.umode & USR_AWAY)
		sv_cl_write("G", &cl->wr);
	else
		sv_cl_write("H", &cl->wr);
	sv_info_next(us, cl);
}
