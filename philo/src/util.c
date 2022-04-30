/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:11:53 by snovaes           #+#    #+#             */
/*   Updated: 2022/04/30 02:47:41 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_puterror(char *str)
{
	char	*s;
	int		i;

	s = str;
	i = 0;
	while (*s++)
		i++;
	write(2, str, i);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;

	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	num = 0;
	while ('0' <= *nptr && *nptr <= '9')
	{
		num *= 10;
		num += sign * (*nptr - '0');
		nptr++;
	}
	return (num);
}

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (1);
	memset(*(void **)dst, 0, size);
	return (0);
}

void msleep(int time_in_ms)
{
	long long	start_time;
	start_time = timestamp();
	while (timestamp() - start_time < (long)time_in_ms)
		usleep(10);
}

long long	time_to_ms(struct timeval now)
{
	long long	milisec;

	milisec = now.tv_sec * 1000;
	milisec += now.tv_usec / 1000;
	return (milisec);
} 

long long timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long timenow(long firstamp)
{
	return (timestamp() - firstamp);
}

void	print_philo_msg(t_philo *philo, char *str)
{
	long long		milisec;
	struct timeval	now;

	pthread_mutex_lock(&philo->info->finish_mutex);
	gettimeofday(&now, NULL);
	milisec = time_to_ms(now) - time_to_ms(philo->info->create_at);
	if (!philo->info->finish)
		printf("%lld\t%d\t %s\n", milisec, philo->n + 1, str);
	pthread_mutex_unlock(&philo->info->finish_mutex);
}


void	print_action(t_philo *philo, int action)
{
	long	current_time;

	pthread_mutex_lock(philo->info->lock_print);
	current_time = timenow(philo->info->createat);
	if (action == TOOK_A_FORK && !has_finished(philo->info))
		printf("%5ld %3d has taken a fork\n", current_time, philo->n + 1);
	else if (action == EATING && !has_finished(philo->info))
		printf("%5ld %3d is eating\n", current_time, philo->n + 1);
	else if (action == SLEEPING && !has_finished(philo->info))
		printf("%5ld %3d is sleeping\n", current_time, philo->n + 1);
	else if (action == THINKING && !has_finished(philo->info))
		printf("%5ld %3d is thinking\n", current_time, philo->n + 1);
	else if (action == DIED)
		printf("%5ld %3d died\n", current_time, philo->n + 1);
	pthread_mutex_unlock(philo->info->lock_print);
}