/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_alone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 05:10:08 by coder             #+#    #+#             */
/*   Updated: 2022/05/01 05:21:20 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*go_eat_alone(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, TOOK_A_FORK);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}
