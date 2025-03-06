/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:17:05 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/05 10:18:54 by mzhitnik         ###   ########.fr       */
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

static void	forks_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		data->forks[i].fork_id = i + 1;
		if (pthread_mutex_init(&data->forks[i].fork_lock, NULL) != 0)
			return (error_msg("Fork mutex initialization failed\n"));
		i++;
	}
}

static void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].time_last_meal = get_current_time();
		data->philos[i].data = data;
		assign_forks(&data->philos[i]);
		i++;
	}
}

void	data_init(t_data *data)
{
	data->ps_start = get_current_time();
	data->philos = (t_philo *)ft_calloc(data->ph_num, sizeof(t_philo));
	if (!data->philos)
		return (error_msg("Philos array allocation failed\n"));
	data->forks = (t_fork *)ft_calloc(data->ph_num, sizeof(t_fork));
	if (!data->forks)
		return (error_msg("Forks array allocation failed\n"));
	forks_init(data);
	philo_init(data);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (error_msg("Write mutex initialization failed\n"));
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (error_msg("Write mutex initialization failed\n"));
}

void	simulation_start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ph_num)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine, \
			&data->philos[i]) != 0)
			return (error_msg("Philo thread creation failed\n"));
		i++;
	}
	i = 0;
	if (pthread_create(&data->observer, NULL, monitoring, data) != 0)
		return (error_msg("Observer thread creation failed\n"));
	while (i < data->ph_num)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (error_msg("Thread join failed\n"));
		i++;
	}
	if (pthread_join(data->observer, NULL) != 0)
		error_msg("Observer thread join failed\n");
}
