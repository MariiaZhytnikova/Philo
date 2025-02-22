/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:17:05 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/22 11:41:07 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->fork_one = &philo->data->forks[philo->id];
		philo->fork_two = &philo->data->forks[(philo->id + 1) / philo->data->ph_num];
	}
	else
	{
		philo->fork_one = &philo->data->forks[(philo->id + 1) / philo->data->ph_num];
		philo->fork_two = &philo->data->forks[philo->id];
	}
}

static void	forks_init(t_data *data)
{
	int	i;
	
	i = 1;
	while (i <= data->ph_num)
	{
		data->forks[i].fork_id = i;
		if(pthread_mutex_init(&data->forks[i].fork_mut, NULL) != 0)
			return (error_msg("Fork mutex initialization failed\n"));
		i++;
	}
}

static void	philo_init(t_data *data)
{
	int	i;
	
	i = 1;
	while (i <= data->ph_num)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		assign_forks(&data->philos[i]);
		if(pthread_mutex_init(&data->philos[i].philo_lock, NULL) != 0)
			return (error_msg("Philo mutex initialization failed\n"));
		i++;
	}
}

void	data_init(t_data *data)
{
	data->philos = (t_philo *)ft_calloc(data->ph_num, sizeof(t_philo));
	if (!data->philos)
		return (error_msg("Philos array allocation failed\n"));
	data->forks = (t_fork *)ft_calloc(data->ph_num, sizeof(t_fork));
	if (!data->forks)
		return (error_msg("Forks array allocation failed\n"));
	forks_init(data);
	philo_init(data);
	if(pthread_mutex_init(&data->data_lock, NULL) != 0)
			return (error_msg("Data mutex initialization failed\n"));
	if(pthread_mutex_init(&data->print_lock, NULL) != 0)
			return (error_msg("Write mutex initialization failed\n"));
}
