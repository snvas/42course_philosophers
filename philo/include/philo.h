/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:02:23 by snovaes           #+#    #+#             */
/*   Updated: 2022/05/01 05:11:36 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define TOOK_A_FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

typedef struct s_philo
{
	int				n;
	int				num_of_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	check_lock;
	pthread_t		th_id;
	struct s_info	*info;
	long long		last_time_to_eat;
}	t_philo;

typedef struct s_info
{
	int				alone;
	int				num_of_philo;
	int				had_dinner;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				finish;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t	*lock_print;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	long long		create_at;
}	t_info;

int			ft_puterror(char *str);
int			ft_atoi(const char *nptr);
int			ft_malloc(void *dst, size_t size);
int			init(t_info *info, int argc, char *argv[]);
void		*monitor(void *argv);
void		*monitor_each_must_eat(void *argv);
void		*philo(void *argv);
int			has_finished(t_info *info);
long long	timenow(long long firststamp);
long long	timestamp(void);
void		msleep(int time_in_ms);
void		print_action(t_philo *philo, int action);
void		*go_eat_alone(t_philo *philo);

#endif