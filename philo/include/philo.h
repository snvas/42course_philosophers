/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:02:23 by snovaes           #+#    #+#             */
/*   Updated: 2022/04/29 23:36:43 by snovaes          ###   ########.fr       */
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

typedef struct s_philo
{
	int				n;
	int				num_of_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	check_lock;
	pthread_t		th_id;
	struct s_info	*info;
	struct timeval	last_time_to_eat;
	long			lasttimetoeat;
}	t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				num_of_philo_finished_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				finish;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	struct timeval	create_at;
	long			firststamp;
}	t_info;

int			ft_puterror(char *str);
int			ft_atoi(const char *nptr);
int			ft_malloc(void *dst, size_t size);
long long	time_to_ms(struct timeval now);

int			init(t_info *info, int argc, char *argv[]);
void		*monitor(void *argv);
void		*monitor_each_must_eat(void *argv);
void		*philo(void *argv);
void		print_philo_msg(t_philo *philo, char *str);
int			has_finished(t_info *info);
long		timenow(long firststamp);
long		timestamp(void);
void		msleep(int time_in_ms);
#endif