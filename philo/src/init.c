/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:17:05 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/13 13:44:17 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo)
{
	int	ph_num;

	ph_num = philo->data->ph_num;
	if (philo->id % 2 == 0)
	{
		philo->fork_one = &philo->data->forks[philo->id - 1];
		philo->fork_two = &philo->data->forks[(philo->id) % ph_num];
	}
	else
	{
		philo->fork_one = &philo->data->forks[(philo->id) % ph_num];
		philo->fork_two = &philo->data->forks[philo->id - 1];
	}
}

static int	forks_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		data->forks[i].fork_id = i + 1;
		if (pthread_mutex_init(&data->forks[i].fork_lock, NULL) != 0)
			return (error_msg("Fork mutex initialization failed"), 1);
		i++;
	}
	return (0);
}

static void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].time_last_meal = data->ps_start;
		data->philos[i].time_next_meal = data->ps_start;
		data->philos[i].data = data;
		assign_forks(&data->philos[i]);
		i++;
	}
}

int	data_init(t_data *data)
{
	data->ps_start = get_current_time() + 10;
	if (forks_init(data))
		return (1);
	philo_init(data);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (error_msg("Write mutex initialization failed"), 1);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (error_msg("Write mutex initialization failed"), 1);
	return (0);
}

int	alloc(t_data *data)
{
	data->philos = (t_philo *)ft_calloc(data->ph_num, sizeof(t_philo));
	if (!data->philos)
		return (error_msg("Philos array allocation failed"), 1);
	data->forks = (t_fork *)ft_calloc(data->ph_num, sizeof(t_fork));
	if (!data->forks)
		return (free(data->philos), error_msg("Array allocation failed"), 1);
	return (0);
}
