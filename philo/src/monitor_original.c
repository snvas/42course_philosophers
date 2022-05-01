/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_original.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:21:34 by snovaes           #+#    #+#             */
/*   Updated: 2022/05/01 02:01:16 by coder            ###   ########.fr       */
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
	long long		now;
	long long		msec;

	philo = argv;
	while (!has_finished(philo->info))
	{
		pthread_mutex_lock(&philo->check_lock);
		pthread_mutex_lock(&philo->info->finish_mutex);
		msec = timenow(philo->last_time_to_eat);
		//gettimeofday(&now, NULL);
	//	msec = time_to_ms(now) - time_to_ms(philo->last_time_to_eat);
	//	gettimeofday(&now, NULL);
		if (msec >= philo->info->time_to_die && philo->info->finish == 0)
		{
			now = timenow(philo->info->create_at);
			printf("%lld\t%d\t %s\n", now, philo->n + 1, " died");
			philo->info->finish = 1;
		}
		pthread_mutex_unlock(&philo->info->finish_mutex);
		pthread_mutex_unlock(&philo->check_lock);
		msleep(1);
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
