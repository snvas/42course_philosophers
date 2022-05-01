/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:36:14 by snovaes           #+#    #+#             */
/*   Updated: 2022/05/01 00:52:24 by snovaes          ###   ########.fr       */
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
	if (philo->n == 1)
		philo->info->create_at = timestamp();
	if (philo->n % 2)
		usleep(philo->info->time_to_eat);
	if (philo->info->alone)
		return (go_eat_alone(philo));
	while (!has_finished(philo->info))
	{
		pickup_fork(philo);
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

static int	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, TOOK_A_FORK);
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, TOOK_A_FORK);
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
		printf("%5lld %3d %s\n", ms, philo->n + 1, "is eating");
	philo->num_of_eat += 1;
	if (philo->num_of_eat == philo->info->num_of_must_eat)
		philo->info->had_dinner += 1;
	pthread_mutex_unlock(&philo->info->finish_mutex);
	msleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->check_lock);
}

static void	sleeping(t_philo *philo)
{
	print_action(philo, SLEEPING);
	msleep(philo->info->time_to_sleep);
}

static void	think(t_philo *philo)
{
	print_action(philo, THINKING);
	usleep(100);
}
