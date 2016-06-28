/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:44:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/27 18:07:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static void		cl_prompt(t_client *cl)
{
	ft_putstr(cl->name);
	ft_putstr(" \e[31m>\e[0m");
}

static int		cl_check_end(t_client *cl)
{
	char		*buf;
	int			i;

	i = 0;
	buf = cl->wr.head;
	while (i < END_CHECK_LEN)
	{
		if (*buf != END_CHECK[i])
			break ;
		buf++;
		if (buf >= cl->wr.end)
			buf = cl->wr.start;
		i++;
	}
	if (i == END_CHECK_LEN)
	{
		*cl->wr.head += 1;
		*cl->read = 0;
		return (1);
	}
	return (0);
}

void			cl_loop(t_client *cl)
{
	int			max;

	while (42)
	{
		FD_ZERO(&cl->fds);
		if (cl->sock > -1)
			FD_SET(cl->sock, &cl->fds);
		FD_SET(STDIN_FILENO, &cl->fds);
		if (*cl->read == '\0' || cl_check_end(cl))
			cl_prompt(cl);
		max = (cl->sock > STDIN_FILENO) ? cl->sock : STDIN_FILENO;
		if (select(max + 1, &cl->fds, NULL, NULL, NULL) == -1)
			cl_error("Client: select() failed.", cl);
		if (cl->sock > -1 && FD_ISSET(cl->sock, &cl->fds))
			read_server(cl);
		if (FD_ISSET(STDIN_FILENO, &cl->fds))
			read_client(cl);
	}
}
