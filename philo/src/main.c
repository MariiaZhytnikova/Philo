/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:53:36 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/23 20:05:19 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



// Compile with the -pthread flag to link the pthread library.

#include "philo.h"

void	error_msg(char *msg)
{
	size_t	len;

	len = 0;
	while (msg[len++] != '\0');
	write(2, "Error\n", 6);
	write(2, msg, len);
	write(2, "\n", 1);
}

void	destroy(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_lock);
	
	while (i < data->ph_num)
	{
		pthread_mutex_destroy(&data->philos[i].philo_lock);
		pthread_mutex_destroy(&data->philos[i].fork_one->fork_lock);
		pthread_mutex_destroy(&data->philos[i].fork_two->fork_lock);
		i++;
	}
	free(data->forks);
	free(data->philos);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (parce_args(data, argc, argv))
		return (free(data), 1);
	data_init(data);
	simulation_start(data);
	destroy(data);
	return (0);
}
