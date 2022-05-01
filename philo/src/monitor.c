/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:21:34 by snovaes           #+#    #+#             */
/*   Updated: 2022/05/01 00:52:30 by snovaes          ###   ########.fr       */
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
		if (info->had_dinner == info->num_of_philo)
			info->finish = 1;
		pthread_mutex_unlock(&info->finish_mutex);
		usleep(500);
	}
	return (NULL);
}

void	*monitor(void *argv)
{
	t_philo			*philo;
	long long		now;
	long long		msec;

	philo = argv;
	while (!has_finished(philo->info))
	{
		pthread_mutex_lock(&philo->check_lock);
		pthread_mutex_lock(&philo->info->finish_mutex);
		msec = timenow(philo->last_time_to_eat);
		if ((msec > philo->info->time_to_die && philo->info->finish == 0) \
			|| philo->info->alone == 1)
		{
			now = timenow(philo->info->create_at);
			printf("%5lld %3d %s\n", now, philo->n + 1, " died");
			philo->info->finish = 1;
		}
		pthread_mutex_unlock(&philo->info->finish_mutex);
		pthread_mutex_unlock(&philo->check_lock);
		usleep(1000);
	}
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
