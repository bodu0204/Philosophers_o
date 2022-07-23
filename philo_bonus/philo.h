/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:22:15 by blyu              #+#    #+#             */
/*   Updated: 2022/07/23 12:47:11 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdlib.h>
//semmame
# define QUOTASEM "QUOTA_sem"
# define FORKSEM "FORK_sem"
//is it clear number_of_times_each_philosopher_must_eat
# define NOTYET 0
# define FINISH 1
//end status
# define NORMAL 0
# define ERROR -1
//flag about what philo doing
# define THINK0 0
# define THINK 1
# define DIE 2
# define EAT 3
# define SLEEP 4
# define FORK 5
//convert unit
# define S_US 1000000
# define S_MS 1000
# define MS_US 1000
//log format
# define LOGFMT "%06u_in_ms %u %s\n"

typedef struct s_info
{
	unsigned int		n;
	unsigned int		d;
	unsigned int		e;
	unsigned int		s;
	unsigned int		me;
}	t_info;

typedef struct s_quota
{
	sem_t			*s;
	int				*f;
	unsigned int	pn;
	unsigned int	me;
}	t_quota;

typedef struct s_hand
{
	int		*req;
	int		*res;
	sem_t	*f;
}	t_hand;

typedef struct s_acsess
{
	int		*req;
	int		*res;
}	t_acsess;

typedef struct s_sems
{
	sem_t	*f;
	sem_t	*q;
}	t_sems;

typedef struct s_schedule
{
	unsigned long int	et;
	unsigned long int	st;
	unsigned long int	tt;
	unsigned long int	dt;
}	t_schedule;
//main.c
int				set_args(t_info *i, int argc, char *argv[]);
void			*main_quota(void *vp);
void			mkphilo_and_exe(t_info *i, int *quota);
void			exe(t_info *i, int *quota);
//philo_main.c
void			philo(t_info *i);
void			*philo_hand(void *vp);
void			philo_main(t_info *i, t_acsess *acs, t_sems *se);
void			thinking(t_info *i, t_schedule *sc, t_acsess *acs, t_sems *se);
void			eating(t_info *i, t_schedule *sc, unsigned int *eat, \
	t_sems *se);
void			sleeping(t_info *i, t_schedule *sc);
//philo_util.c
void			philolog(t_info *i, int d);
void			get_schedule(t_info *i, t_schedule	*s);
unsigned long	now(void);
//tool.c
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				set_args(t_info *i, int argc, char *argv[]);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				set_uint(char	*s, unsigned int *u);
#endif
