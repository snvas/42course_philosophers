/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:27:15 by snovaes           #+#    #+#             */
/*   Updated: 2022/05/01 04:27:33 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void		parsing_arg(t_info *info, int argc, char *argv[]);
static int		check_info(t_info *info, int argc);
static int		init_philos(t_info *info);

int	init(t_info *info, int argc, char *argv[])
{
	parsing_arg(info, argc, argv);
	if (check_info(info, argc))
		return (1);
	if (init_philos(info))
		return (1);
	return (0);
}

static void	parsing_arg(t_info *info, int argc, char *argv[])
{
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[5]);
}

static int	check_info(t_info *info, int argc)
{
	if (argc == 6 && info->num_of_must_eat <= 0)
		return (ft_puterror("ERROR: num of must eat must be > 0\n"));
	if (info->num_of_philo < 0)
		return (ft_puterror("ERROR: num of philo must be > 0\n"));
	if (info->time_to_die < 0)
		return (ft_puterror("ERROR: time to die must be > 0\n"));
	if (info->time_to_eat < 0)
		return (ft_puterror("ERROR: time to eat must be > 0\n"));
	if (info->time_to_sleep < 0)
		return (ft_puterror("ERROR: time to sleep must be > 0\n"));
	return (0);
}

static int	init_philos(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->finish_mutex, NULL);
	if (ft_malloc(&info->philos, sizeof(t_philo) * info->num_of_philo) || \
		ft_malloc(&info->forks, sizeof(pthread_mutex_t) * info->num_of_philo) || \
		ft_malloc(&info->lock_print, sizeof(pthread_mutex_t)))
		return (ft_puterror("ERROR: malloc failed\n"));
	if (info->num_of_philo == 1)
		info->alone = 1;
	else
		info->alone = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].n = i;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].check_lock, NULL);
		if (i == 0)
			info->philos[i].left_fork = &info->forks[info->num_of_philo - 1];
		else
			info->philos[i].left_fork = &info->forks[i - 1];
		info->philos[i].right_fork = &info->forks[i];
		info->philos[i].info = info;
		++i;
	}
	return (0);
}
