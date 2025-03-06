/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:53:36 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/05 16:54:38 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_msg(char *msg)
{
	size_t	len;

	len = 0;
	while (msg[len] != '\0')
		len++;
	write(2, "Error\n", 6);
	write(2, msg, len);
	write(2, "\n", 1);
}

void	destroy(t_data *data)
{
	if (sem_close(data->forks))
		error_msg("Semaphores close failed");
	if (sem_close(data->print_lock))
		error_msg("Semaphores close failed");
	if (sem_close(data->dead_lock))
		error_msg("Semaphores close failed");
	if (sem_unlink("/forks") == -1)
		error_msg("Semaphores unlink failed");
	if (sem_unlink("/print") == -1)
		error_msg("Semaphores unlink failed");
	if (sem_unlink("/dead") == -1)
		error_msg("Semaphores unlink failed");
	free(data->philos);
	free(data);
	printf("     Cleaning done \n");
	printf("       ¯\\_(ツ)_/¯\n");
	exit(0);
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
	if (data->ph_num == 1)
	{
		data->ps_start = get_current_time();
		printf("%zu 1 is thinking\n", get_current_time() - data->ps_start);
		printf("%zu 1 has taken a fork\n", get_current_time() - data->ps_start);
		ft_usleep(data->time_die);
		printf("%zu 1 died\n", get_current_time() - data->ps_start);
		return (free(data), 0);
	}
	data_init(data);
	simulation(data);
	return (0);
}
