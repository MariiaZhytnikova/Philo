/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 09:31:56 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/13 13:46:40 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_death(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->is_dead = true;
	pthread_mutex_unlock(&data->dead_lock);
}

int	meals_eaten(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (data->philos[i].meals_eaten < data->meals_num)
		{
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		i++;
		pthread_mutex_unlock(&data->dead_lock);
	}
	return (0);
}

void	*monitoring(void *param)
{
	t_data	*data;
	size_t	elapse;
	int		i;

	data = (t_data *)param;
	sim_start(data->ps_start);
	while (checker(data))
	{
		i = -1;
		while (++i < data->ph_num)
		{
			pthread_mutex_lock(&data->dead_lock);
			elapse = get_current_time() - data->philos[i].time_last_meal;
			pthread_mutex_unlock(&data->dead_lock);
			if (elapse > data->time_die)
			{
				write_msg("died\n", &data->philos[i]);
				set_death(data);
			}
			if (data->meals_num > 0 && !meals_eaten(data))
				set_death(data);
			ft_usleep(5);
		}
	}
	return (NULL);
}

void	thread_join(t_data *data, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			error_msg("Thread join failed\n");
		i++;
	}
}

void	simulation_start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]) != 0)
		{
			set_death(data);
			thread_join(data, i);
			return (error_msg("Philo thread creation failed\n"));
		}
		i++;
	}
	if (pthread_create(&data->observer, NULL, monitoring, data) != 0)
	{
		set_death(data);
		thread_join(data, data->ph_num);
		return (error_msg("Observer thread creation failed\n"));
	}
	thread_join(data, data->ph_num);
	if (pthread_join(data->observer, NULL) != 0)
		error_msg("Observer thread join failed\n");
}
