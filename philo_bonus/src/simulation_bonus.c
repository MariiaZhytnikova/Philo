/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 09:31:56 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/08 17:09:52 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	semaphores_two(t_data *data)
{
	data->dead_lock = sem_open("/dead", O_CREAT | O_EXCL, 0666, 1);
	if (data->dead_lock == SEM_FAILED)
	{
		sem_unlink("/dead");
		data->dead_lock = sem_open("/dead", O_CREAT | O_EXCL, 0666, 1);
		if (data->dead_lock == SEM_FAILED)
			return (error_msg("Semaphores open failed\n"), 1);
	}
	data->done = sem_open("/done", O_CREAT | O_EXCL, 0666, 1);
	if (data->done == SEM_FAILED)
	{
		sem_unlink("/done");
		data->done = sem_open("/done", O_CREAT | O_EXCL, 0666, 1);
		if (data->done == SEM_FAILED)
			return (error_msg("Semaphores open failed\n"), 1);
	}
	return (0);
}

static int	semaphores(t_data *data)
{
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0666, data->ph_num);
	if (data->forks == SEM_FAILED)
	{
		sem_unlink("/forks");
		data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0666, data->ph_num);
		if (data->forks == SEM_FAILED)
			return (error_msg("Semaphores open failed\n"), 1);
	}
	data->fifo = sem_open("/fifo", O_CREAT | O_EXCL, 0666, 1);
	if (data->fifo == SEM_FAILED)
	{
		sem_unlink("/fifo");
		data->fifo = sem_open("/fifo", O_CREAT | O_EXCL, 0666, 1);
		if (data->fifo == SEM_FAILED)
			return (error_msg("Semaphores open failed\n"), 1);
	}
	if (semaphores_two(data))
		return (1);
	return (0);
}

int	data_init(t_data *data)
{
	int	i;

	data->philos = (t_philo *)ft_calloc(data->ph_num, sizeof(t_philo));
	if (!data->philos)
		return (1);
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

void	parent(t_data *data)
{
	int	i;

	i = 0;
	sem_wait(data->done);
	sem_wait(data->done);
	while (i < data->ph_num)
	{
		kill(data->philos[i].pid, SIGTERM);
		i++;
	}
}

void	simulation(t_data *data)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < data->ph_num)
	{
		pid = fork();
		if (pid == -1)
			return (error_msg("Fork open failed\n"));
		if (pid == 0)
		{
			routine(&data->philos[i]);
			exit(0);
		}
		else
			data->philos[i].pid = pid;
		i++;
	}
	parent(data);
}
