/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 09:31:56 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/22 11:45:57 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"




size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}



void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;

	printf("%zu %d is thinking\n", get_current_time(), philo->id);
	ft_usleep(10);
	printf("%zu %d is eating\n", get_current_time(), philo->id);
	ft_usleep(10);
	printf("%zu %d is sleeping\n", get_current_time(), philo->id);
	ft_usleep(10);

	return (NULL);
}

simulation_start(t_data *data)
{
	
}
