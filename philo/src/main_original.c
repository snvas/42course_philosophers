/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:09:01 by snovaes           #+#    #+#             */
/*   Updated: 2022/04/30 00:28:26 by snovaes          ###   ########.fr       */
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
	pthread_t	th_id;

	gettimeofday(&info->create_at, NULL);
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].last_time_to_eat = info->create_at;
		pthread_create(&info->philos[i].th_id, NULL, philo, &info->philos[i]);
		pthread_create(&th_id, NULL, monitor, &info->philos[i]);
		pthread_detach(th_id);
		++i;
	}
	if (info->num_of_must_eat != 0)
	{
		pthread_create(&th_id, NULL, monitor_each_must_eat, info);
		pthread_detach(th_id);
	}
}

static void	join_and_free_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(info->philos[i].th_id, NULL);
		pthread_mutex_destroy(&info->philos[i].check_lock);
		i++;
	}
	free(info->philos);
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	free(info->forks);
}
