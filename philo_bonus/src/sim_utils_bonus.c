/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:13:11 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/08 16:31:48 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_msg("gettimeofday() error");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(200);
}

int	meals_eaten(t_philo *philo)
{
	if (philo->meals_eaten - 1 < philo->data->meals_num)
	{
		sem_post(philo->data->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitoring(void *param)
{
	t_philo	*philo;
	size_t	elapse;

	philo = (t_philo *)param;
	while (1)
	{
		sem_wait(philo->data->dead_lock);
		elapse = get_current_time() - philo->time_last_meal;
		if (elapse > philo->data->time_die)
		{
			printf("%zu %d %s", get_current_time() \
					- philo->data->ps_start, philo->id, "died\n");
			sem_post(philo->data->done);
			return (NULL);
		}
		if (philo->data->meals_num > 0 && !meals_eaten(philo))
		{
			sem_post(philo->data->done);
			return (NULL);
		}
		sem_post(philo->data->dead_lock);
		ft_usleep (5);
	}
	return (NULL);
}
