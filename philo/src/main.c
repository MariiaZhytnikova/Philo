/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:53:36 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/06 10:27:03 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->ph_num)
	{
		pthread_mutex_destroy(&data->forks[i].fork_lock);
		i++;
	}
	free(data->forks);
	free(data->philos);
	free(data);
	printf("       ¯\\_(ツ)_/¯\n");
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 2)
		return (error_msg(USAGE), 0);
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
	simulation_start(data);
	destroy(data);
	return (0);
}
