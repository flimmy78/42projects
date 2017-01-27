/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:44:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 02:12:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_hist			*new_hist(void)
{
	t_hist		*new;

	if (e.hist == NULL || e.hist->next == NULL)
	{
		new = (t_hist *)malloc(sizeof(*new));
		if (new == NULL)
			return (NULL);
		new->prev = e.hist;
		new->cmd = (char *)malloc(sizeof(*new->cmd) * CMD_SIZE);
		if (new->cmd == NULL)
		{
			free(new);
			return (NULL);
		}
		ft_bzero(new->cmd, CMD_SIZE);
		new->cmd_size = CMD_SIZE;
		new->next = NULL;
		return (new);
	}
	while (e.hist->next)
		e.hist = e.hist->next;
	return (e.hist);
}


void			historic_command(void)
{
	int			y;

	if (K_UP && e.hist->prev)
	{
		e.hist = e.hist->prev;
		e.cpy.cpy = 0;
		e.pos.x = ft_strlen(e.hist->cmd);
		tputs(ft_tgetstr("rc"), 1, ft_pchar);
		y = e.pos.y;
		while (y--)
			tputs(ft_tgetstr("up"), 1, ft_pchar);			
		tputs(ft_tgetstr("cd"), 1, ft_pchar);
		write(e.fd, e.hist->cmd, e.pos.x);
	}
	else if (K_DOWN && e.hist->next)
	{
		e.hist = e.hist->next;
		e.cpy.cpy = 0;
		e.pos.x = ft_strlen(e.hist->cmd);
		tputs(ft_tgetstr("rc"), 1, ft_pchar);
		y = e.pos.y;
		while (y--)
			tputs(ft_tgetstr("up"), 1, ft_pchar);			
		tputs(ft_tgetstr("cd"), 1, ft_pchar);
		write(e.fd, e.hist->cmd, e.pos.x);
	}
}
