/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 09:31:56 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/23 09:52:11 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	semaphores_two(t_data *data)
{
	data->dead_lock = sem_open("/dead", O_CREAT | O_EXCL, 0666, 1);
	if (data->dead_lock == SEM_FAILED)
	{
		sem_unlink("/dead");
		data->dead_lock = sem_open("/dead", O_CREAT | O_EXCL, 0666, 1);
		if (data->dead_lock == SEM_FAILED)
			return (error_msg("Semaphores open failed\n"), 1);
	}
	data->done = sem_open("/done", O_CREAT | O_EXCL, 0666, 0);
	if (data->done == SEM_FAILED)
	{
		sem_unlink("/done");
		data->done = sem_open("/done", O_CREAT | O_EXCL, 0666, 0);
		if (data->done == SEM_FAILED)
			return (error_msg("Semaphores open failed\n"), 1);
	}
	return (0);
}

int	semaphores(t_data *data)
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

void	parent(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->ph_num)
		sem_wait(data->done);
	i = 0;
	while (i < data->ph_num)
	{
		if (kill(data->philos[i].pid, 0) == 0)
		{
			kill(data->philos[i].pid, SIGKILL);
			wait(NULL);
		}
		i++;
	}
}

void	child(t_data *data, int i)
{
	if (pthread_create(&data->philos[i].observer, NULL,
			monitoring, &data->philos[i]) != 0)
	{
		error_msg("Observer thread creation failed\n");
		sem_post(data->done);
	}
	pthread_detach(data->philos[i].observer);
	routine(&data->philos[i]);
	exit(0);
}

void	simulation(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->ph_num)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
		{
			sem_post(data->done);
			return (error_msg("Fork open failed\n"));
		}
		if (data->philos[i].pid == 0)
			child(data, i);
		i++;
	}
	parent(data);
}
