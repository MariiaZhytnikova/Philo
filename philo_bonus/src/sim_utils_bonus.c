/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:13:11 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/23 09:51:46 by mzhitnik         ###   ########.fr       */
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
	if (philo->meals_eaten < philo->data->meals_num)
	{
		sem_post(philo->data->dead_lock);
		return (1);
	}
	return (0);
}

int	data_init(t_data *data)
{
	int	i;

	data->ps_start = get_current_time();
	if (semaphores(data))
		return (1);
	i = 0;
	while (i < data->ph_num)
	{
		data->philos[i].time_last_meal = data->ps_start;
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		i++;
	}
	return (0);
}

void	rip(t_philo *philo)
{
	int	i;

	i = 0;
	printf("%zu %d %s", get_current_time()
		- philo->data->ps_start, philo->id, "died\n");
	while (i < philo->data->ph_num)
	{
		sem_post(philo->data->done);
		i++;
	}
}
