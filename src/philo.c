/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:36:14 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/18 13:51:07 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	pickup_fork(t_philo *philo);
static void	eat(t_philo *philo);
static void	sleeping(t_philo *philo);
static void	think(t_philo *philo);

void	*philo(void *argv)
{
	t_philo	*philo;

	philo = argv;
	if (philo->n % 2 == 0)
		usleep(philo->info->time_to_eat * 1000);
	while (!philo->info->finish)
	{
		pickup_fork(philo);
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

static void	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_philo_msg(philo, "has taken a fork to the right");
	pthread_mutex_lock(philo->left_fork);
	print_philo_msg(philo, "has taken a fork to the left");
}

static void	eat(t_philo *philo)
{
	long long	ms;

	pthread_mutex_lock(&philo->lock);
	gettimeofday(&philo->last_time_to_eat, NULL);
	ms = time_to_ms(philo->last_time_to_eat) - \
		time_to_ms(philo->info->create_at);
	pthread_mutex_lock(&philo->info->finish_mutex);
	if (!philo->info->finish)
		printf("%lld\t%d\t %s\n", ms, philo->n, "is eating");
	philo->num_of_eat += 1;
	if (philo->num_of_eat == philo->info->num_of_must_eat)
		philo->info->num_of_eat_finish_philo += 1;
	pthread_mutex_unlock(&philo->info->finish_mutex);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->lock);
}

static void	sleeping(t_philo *philo)
{
	print_philo_msg(philo, "is sleeping");
	usleep(philo->info->time_to_sleep * 1000);
}

static void	think(t_philo *philo)
{
	print_philo_msg(philo, "is thinking");
}
