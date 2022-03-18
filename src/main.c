/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:09:01 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/18 13:51:55 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	join_and_free_philos(t_info *info);
static void	create_philos(t_info *info);

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(info));
	if (argc != 5 && argc != 6)
		return (ft_puterror("ERROR: you should specify \
num of philo, time to die, time to eat, time to sleep\n"));
	if (init(&info, argc, argv))
		return (1);
	create_philos(&info);
	join_and_free_philos(&info);
	return (0);
}

static void	create_philos(t_info *info)
{
	int			i;
	pthread_t	thread;

	gettimeofday(&info->create_at, NULL);
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].last_time_to_eat = info->create_at;
		pthread_create(&info->philos[i].thread, NULL, philo, &info->philos[i]);
		pthread_create(&thread, NULL, &monitor, &info->philos[i]);
		pthread_detach(thread);
		++i;
	}
	if (info->num_of_must_eat != 0)
	{
		pthread_create(&thread, NULL, monitor_each_must_eat, info);
		pthread_detach(thread);
	}
}

static void	join_and_free_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		pthread_mutex_destroy(&info->philos[i++].lock);
	}
	free(info->philos);
	i = 0;
	while (i < info->num_of_philo)
		pthread_mutex_destroy(&info->forks[i++]);
	free(info->forks);
}
