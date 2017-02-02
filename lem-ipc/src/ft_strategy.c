/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strategy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 16:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/22 14:03:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <stdio.h>

static void		ft_get_players_position(void)
{
	int			i;

	ft_memset(e.ally, -1, sizeof(*e.ally) * TEAM_1);
	ft_memset(e.ennemy, -1, sizeof(*e.ennemy) * TEAM_2);
	ft_bzero(e.players, sizeof(int) * 2);
	i = 0;
	while (i < WIDTH * HEIGTH)
	{
		if (e.map[i] == e.team)
		{
			e.ally[e.players[0]].y = i / WIDTH;
			e.ally[e.players[0]].x = i % WIDTH;
			printf("Allied #%d in x:%d y:%d\n", e.players[0], e.ally[e.players[0]].x + 1, e.ally[e.players[0]].y + 1);
			e.players[0]++;
		}
		else if (e.map[i] != 0)
		{
			e.ennemy[e.players[1]].y = i / WIDTH;
			e.ennemy[e.players[1]].x = i % WIDTH;
			printf("Ennemy #%d in x:%d y:%d\n", e.players[1], e.ennemy[e.players[1]].x + 1, e.ennemy[e.players[1]].y + 1);
			e.players[1]++;
		}
		i++;
	}
}

static void		ft_get_distance(void)
{
	int			i;
	int			last;

	i = 0;
	last = WIDTH * HEIGTH;
	ft_bzero(&e.snd, sizeof(e.snd));
	while (i < e.players[1])
	{
		e.ennemy[i].dist = (e.x > e.ennemy[i].x) ?
			e.x - e.ennemy[i].x : e.ennemy[i].x - e.x;
		e.ennemy[i].dist += (e.y > e.ennemy[i].y) ?
			e.y - e.ennemy[i].y : e.ennemy[i].y - e.y;
		e.ennemy[i].dist -= 2;
		printf("Ennemy #%d dist: %d\n", i, e.ennemy[i].dist);
		if (e.ennemy[i].dist < last)
		{
			e.snd.ennemy.x = e.ennemy[i].x;
			e.snd.ennemy.y = e.ennemy[i].y;
			e.snd.ennemy.dist = e.ennemy[i].dist;
			last = e.ennemy[i].dist;
		}
		i++;
	}
}

void			ft_strategy(void)
{
	ft_get_players_position();
	ft_get_distance();
	printf("I'm attacking ennemy in x:%d y:%d\n", e.snd.ennemy.x, e.snd.ennemy.y);
	ft_rcvmsg();
	ft_sendmsg();
}