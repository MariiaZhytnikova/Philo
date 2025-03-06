/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 09:31:56 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/06 10:42:22 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	semaphores(t_data *data)
{
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0666, data->ph_num);
	if (data->forks == SEM_FAILED)
	{
		sem_unlink("/forks");
		data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0666, data->ph_num);
		if (data->forks == SEM_FAILED)
			return (error_msg("Semaphores open failed\n"));
	}
	data->print_lock = sem_open("/print", O_CREAT | O_EXCL, 0666, 1);
	if (data->print_lock == SEM_FAILED)
	{
		sem_unlink("/print");
		data->print_lock = sem_open("/print", O_CREAT | O_EXCL, 0666, 1);
		if (data->print_lock == SEM_FAILED)
			return (error_msg("Semaphores open failed\n"));
	}
	data->dead_lock = sem_open("/dead", O_CREAT | O_EXCL, 0666, 1);
	if (data->dead_lock == SEM_FAILED)
	{
		sem_unlink("/dead");
		data->dead_lock = sem_open("/dead", O_CREAT | O_EXCL, 0666, 1);
		if (data->dead_lock == SEM_FAILED)
			return (error_msg("Semaphores open failed\n"));
	}
}

void	data_init(t_data *data)
{
	int	i;

	data->is_dead = false;
	data->ps_start = get_current_time();
	data->philos = (t_philo *)ft_calloc(data->ph_num, sizeof(t_philo));
	if (!data->philos)
		return (error_msg("Philos array allocation failed\n"));
	semaphores(data);
	i = 0;
	while (i < data->ph_num)
	{
		data->philos[i].time_last_meal = get_current_time();
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		i++;
	}
}

void	parent(t_data *data)
{
	int		i;
	int		j;
	int		status;
	pid_t	dead_pid;

	i = 0;
	j = 0;
	while (i < data->ph_num)
	{
		dead_pid = waitpid(-1, &status, 0);
		while (j < data->ph_num && data->is_dead == false)
		{
			if (data->philos[j].pid > 0)
			{
				if (data->philos[j].pid == dead_pid && WEXITSTATUS(status))
					write_msg("died\n", &data->philos[j]);
				kill(data->philos[j].pid, SIGTERM);
			}
			j++;
		}
		data->is_dead = true;
		i++;
	}
	destroy(data);
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
