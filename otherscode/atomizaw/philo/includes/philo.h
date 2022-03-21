/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:52:20 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/19 14:43:28 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define NO_VAL -1
# define DEAD 1
# define CONTINUE 2
# define BREAK	3
# define SATISFIED -1
typedef enum e_monitor
{
	RUNNING,
	STOP,
	END
}	t_monitor;

typedef struct s_info
{
	long	die;
	long	eat;
	long	sleep;
	long	number_philo;
	long	must_eat_count;
}	t_info;

typedef enum e_philo_status
{
	EAT,
	SLEEP,
	THINK,
	FULL,
	DIE
}	t_philo_status;

typedef enum e_fork_status
{
	TABLE,
	LEFT_HAND,
	RIGHT_HAND
}	t_fork_status;

typedef struct s_philo_mutex
{
	enum e_philo_status	status;
	pthread_mutex_t		*mutex;
}	t_philo_mutex;

typedef struct s_elapsed_time
{
	long			ms;
	pthread_mutex_t	*mutex;
}	t_elapsed_time;

typedef struct s_fork_mutex
{
	enum e_fork_status		status;
	pthread_mutex_t			*mutex;
}	t_fork_mutex;

typedef struct s_philo
{
	int							idx;
	struct s_philo_mutex		*status;
	struct s_info				*info;
	struct s_elapsed_time		*elapsed_time;
	int							must_eat_count;
	struct s_fork_mutex			*fork_left;
	struct s_fork_mutex			*fork_right;
	struct s_philo				*philo_left;
	struct s_philo				*philo_right;
	pthread_mutex_t				*mutex_write;
}	t_philo;

typedef struct s_system
{
	struct s_philo	*philo;
}	t_system;

void	argument_set(int argc, char **argv, t_info *action_time);
void	philo_init(t_info *info, t_philo *nil_philo);
t_philo	*philo_nil_init(void);
int		is_arg_ok(int argc, char **argv);
int		ft_atoi(const char *str);
int		ft_isspace(const char *str);
void	philo_start(t_philo *nil, long number_philo);
void	monitor_start(t_philo *nil);
void	philo_put_message(t_philo *philo, t_philo_status status);
int		philo_take_left(t_philo *philo);
int		philo_action(t_philo *philo, pthread_mutex_t *mutex_fork);
int		wait_moment(t_philo *philo);
int		take_fork_right(t_philo *philo);
int		take_fork_left(t_philo *philo);
int		is_hungry(t_philo *philo, int idx);
void	*philo_operate(void *philo_void);
int		philo_takeleft(t_philo *philo);
int		philo_takeright(t_philo *philo);
int		philo_takeleft_again(t_philo *philo);
void	philo_usleep(long usleep_time);
int		philo_start_eat(t_philo *philo);
void	philo_putright(t_philo *philo);
void	philo_putleft(t_philo *philo);
void	philo_satisfied(t_philo *philo);
void	philo_stop(t_philo *nil, t_philo *philo, int philo_number);
int		is_stop(t_monitor action, t_philo *nil, t_philo *philo, long end);
void	philo_start(t_philo *nil, long num_philo);
int		philo_start_sleep(t_philo *philo, int next_think);
void	philo_destory(t_philo *nil);
void	create_status(t_philo *new, int idx);
void	create_elapsed_time(t_philo *new);
void	create_fork_left(t_philo *new);
t_philo	*philo_create(int idx, t_info *info, pthread_mutex_t *mutex_write);
int		only_1_philo(t_philo *philo);
int		is_digit(int argc, char **argv);
#endif