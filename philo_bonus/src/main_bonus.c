/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:53:36 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/08 17:00:00 by mzhitnik         ###   ########.fr       */
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

static void	one_philo(t_data *data)
{
	data->ps_start = get_current_time();
	printf("%zu 1 is thinking\n", get_current_time() - data->ps_start);
	printf("%zu 1 has taken a fork\n", get_current_time() - data->ps_start);
	ft_usleep(data->time_die);
	printf("%zu 1 died\n", get_current_time() - data->ps_start);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	(void)argc;
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (0);
	if (parce_args(data, argv))
		return (free(data), 1);
	if (data->ph_num == 1 || data->meals_num == 0)
		return (one_philo(data), free(data), 0);
	if (data_init(data))
		return (destroy(data), 1);
	simulation(data);
	destroy(data);
	return (0);
}
