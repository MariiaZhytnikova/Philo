/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 09:31:56 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/25 11:03:57 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		usleep(100);
}

int	meals_eaten(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		if (data->philos[i].meals_eaten < data->meals_num)
			return (1);
		i++;
	}
	return (0);
}

void	*monitoring(void *param)
{
	t_data	*data;
	size_t	elapse;
	int		i;

	data = (t_data *)param;
	i = 0;
	while (data->is_dead == false)
	{
		ft_usleep(10);
		i = 0;
		while (i < data->ph_num)
		{
			elapse = get_current_time() - data->philos[i].time_last_meal;
			//printf("at %zu for %d - elapse is: %zu\n", get_current_time() - data->ps_start, data->philos[i].id, elapse);
			if (elapse > data->time_die)
			{
				write_msg("died\n", &data->philos[i]);
				data->is_dead = true;
				//return (release_forks(&data->philos[i]), NULL);
			}
			if (data->meals_num != -1 && !meals_eaten(data))
			{
				data->is_dead = true;
				//return (release_forks(&data->philos[i]), NULL);
			}
			i++;
		}
	}
	return (NULL);
}
