/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:53:36 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/13 16:27:38 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_msg(char *msg)
{
	size_t	len;

	len = 0;
	while (msg[len] != '\0')
		len++;
	write(2, msg, len);
	write(2, "\n", 1);
}

void	destroy(t_data *data)
{
	if (sem_close(data->forks))
		error_msg("Fork semaphores close failed");
	if (sem_close(data->dead_lock))
		error_msg("Death semaphores close failed");
	if (sem_close(data->done))
		error_msg("Done semaphores close failed");
	if (sem_close(data->fifo))
		error_msg("Done semaphores close failed");
	if (sem_unlink("/forks") == -1)
		error_msg("Fork semaphores unlink failed");
	if (sem_unlink("/dead") == -1)
		error_msg("Death semaphores unlink failed");
	if (sem_unlink("/done") == -1)
		error_msg("Done semaphores unlink failed");
	if (sem_unlink("/fifo") == -1)
		error_msg("Done semaphores unlink failed");
	if (data->philos)
		free(data->philos);
	if (data)
		free(data);
	printf("       ¯\\_(ツ)_/¯\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 2)
		return (error_msg(USAGE), 1);
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (error_msg("Something wrong"), 1);
	if (parse_args(data, argv))
		return (free(data), 1);
	data->philos = (t_philo *)ft_calloc(data->ph_num, sizeof(t_philo));
	if (!data->philos)
		return (error_msg("Something wrong"), 1);
	if (data_init(data) == 1)
		return (destroy(data), 1);
	simulation(data);
	destroy(data);
	return (0);
}
