/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:21:34 by snovaes           #+#    #+#             */
/*   Updated: 2022/04/30 02:45:34 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*monitor_each_must_eat(void *argv)
{
	t_info	*info;

	info = argv;
	while (!has_finished(info))
	{
		pthread_mutex_lock(&info->finish_mutex);
		if (info->num_of_philo_finished_eat == info->num_of_philo)
			info->finish = 1;
		pthread_mutex_unlock(&info->finish_mutex);
	}
	return (NULL);
}

void	*monitor(void *argv)
{
	t_philo			*philo;
	struct timeval	now;
	long long		msec;
	long long 		current_time;
	long 			time_to_die;

	philo = argv;
	time_to_die = philo->info->time_to_die;
	while (!has_finished(philo->info))
	{
		pthread_mutex_lock(&philo->check_lock);
		pthread_mutex_lock(&philo->info->finish_mutex);
//		gettimeofday(&now, NULL);
		current_time = timestamp();
//		msec = time_to_ms(now) - time_to_ms(philo->last_time_to_eat);
		msec = current_time - philo->lasttimetoeat;
		gettimeofday(&now, NULL);
		current_time = timestamp();
		if (msec >= time_to_die && philo->info->finish == 0)
		{
			philo->info->finish = 1;
			print_action(philo, DIED);
		}
		pthread_mutex_unlock(&philo->info->finish_mutex);
		pthread_mutex_unlock(&philo->check_lock);
	}
	msleep(1);
	printf("finished: %d\n", philo->n + 1);
	return (NULL);
}

int	has_finished(t_info *info)
{
	int	finish;

	pthread_mutex_lock(&info->finish_mutex);
	finish = info->finish;
	pthread_mutex_unlock(&info->finish_mutex);
	return (finish);
}
