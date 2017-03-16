/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_connect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 00:30:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/16 02:52:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** CONNECT is not implemented in this version (1.0)
*/

void			sv_connect(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || !*cmds[1] || !cmds[2] || !*cmds[2])
		return (sv_err(ERR_NEEDMOREPARAMS, "CONNECT", NULL, cl, e));
	if (cl->reg.umode & IRC_OPERATOR)
		return ;
	sv_err(ERR_NOPRIVILEGES, cmds[0], NULL, cl, e);
}