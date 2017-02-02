/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 14:54:34 by root              #+#    #+#             */
/*   Updated: 2016/12/22 14:02:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# include <sys/shm.h>
# include <term.h>

# define WIDTH			10
# define HEIGTH			10
# define MIN_PLAYERS	4
# define TEAM_1			e.data->connected[0]
# define TEAM_2			e.data->connected[1]
# define TEAMS_SUMM		(TEAM_1 + TEAM_2)

/*
** Don't change the order of the members in the s_data structure
*/

typedef struct		s_data
{
	int				end;
	int				connected[2];
	int				game_in_process;
}					t_data;

typedef struct		s_player
{
	int				x;
	int				y;
	int				dist;
}					t_player;

typedef struct		s_msg
{
	int				x;
	int				y;
	int				dist;
}					t_msg;

typedef	struct		s_msgbuf
{
	long			mtype;
	t_msg			ennemy;
}					t_msgbuf;

typedef struct		s_env
{
	char			*prog;
	struct termios	term;
	int				team;
	key_t			key;
	size_t			size;
	int				shmid;
	t_data			*data;
	char			*map;
	int				semid;
	int				msgqid;
	int				x;
	int				y;
	t_player		*ally;
	t_player		*ennemy;
	int				players[2];
	t_msgbuf		snd;
	t_msgbuf		rcv;
}					t_env;

t_env				e;

void				ft_termcaps(char **env);
void				ft_restore_term(void);
void				ft_termdo(char *doit);
void				ft_signal(void);
void				ft_exit_server(int print_err, char *err);
void				ft_exit_client(int print_err, char *err);
void				ft_exit(int print_err, char *err);
void				ft_create_game(void);
void				ft_join_game(void);
void				ft_lock(void);
void				ft_unlock(void);
void				ft_wait_players(void);
void				ft_launch_game(void);
void				ft_strategy(void);
void				print_map(void);
void				ft_sendmsg(void);
void				ft_rcvmsg(void);

#endif