/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:11:53 by snovaes           #+#    #+#             */
/*   Updated: 2022/04/29 23:37:51 by snovaes          ###   ########.fr       */
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
	long	start_time;
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

long timestamp(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (time_to_ms(now));
}

long timenow(long firstamp)
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
