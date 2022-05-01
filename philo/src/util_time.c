/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 05:22:35 by coder             #+#    #+#             */
/*   Updated: 2022/05/01 05:23:22 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	msleep(int time_in_ms)
{
	long long	end_time;

	end_time = timestamp() + time_in_ms;
	while (timestamp() < end_time)
		usleep(10);
}

long long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	timenow(long long firstamp)
{
	return (timestamp() - firstamp);
}
