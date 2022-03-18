/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:02:23 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/18 12:02:18 by snovaes          ###   ########.fr       */
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
	pthread_mutex_t	lock;
	pthread_t		thread;
	struct s_info	*info;
	struct timeval	last_time_to_eat;
}	t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				num_of_eat_finish_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				finish;
	pthread_mutex_t	finish_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	struct timeval	create_at;
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

#endif