/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_original.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:36:14 by snovaes           #+#    #+#             */
/*   Updated: 2022/05/01 02:16:02 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	pickup_fork(t_philo *philo);
static void	eat(t_philo *philo);
static void	sleeping(t_philo *philo);
static void	think(t_philo *philo);

void	*philo(void *argv)
{
	t_philo	*philo;

	philo = argv;
	if (philo->n % 2)
		usleep(philo->info->time_to_eat);
	while (!has_finished(philo->info))
	{
		if (pickup_fork(philo))
		{
			usleep(philo->info->time_to_die * 1000);
			return (NULL);
		}
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

static int	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_philo_msg(philo, "has taken a fork to the right");
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	print_philo_msg(philo, "has taken a fork to the left");
	return (0);
}

static void	eat(t_philo *philo)
{
	long long	ms;

	pthread_mutex_lock(&philo->check_lock);
	philo->last_time_to_eat = timestamp();
	ms = philo->last_time_to_eat - philo->info->create_at;
	pthread_mutex_lock(&philo->info->finish_mutex);
	if (!philo->info->finish)
		printf("%3lld %3d %s\n", ms, philo->n + 1, "is eating");
	philo->num_of_eat += 1;
	if (philo->num_of_eat == philo->info->num_of_must_eat)
		philo->info->num_of_philo_finished_eat += 1;
	pthread_mutex_unlock(&philo->info->finish_mutex);
	msleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->check_lock);
}

static void	sleeping(t_philo *philo)
{
	print_philo_msg(philo, "is sleeping");
	msleep(philo->info->time_to_sleep);
}

static void	think(t_philo *philo)
{
	print_philo_msg(philo, "is thinking");
	msleep(1);
}