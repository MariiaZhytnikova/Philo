/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:54:55 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/23 18:51:04 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	mini_atoi(const char *str)
{
	size_t	i;
	size_t	num;

	if (!str)
		return (0);
	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}

static void	get_numbers(t_data *data, char **array)
{
	data->ph_num = mini_atoi(array[0]);
	data->time_die = mini_atoi(array[1]);
	data->time_eat = mini_atoi(array[2]);
	data->time_sleep = mini_atoi(array[3]);
	if (array[4])
	{
		data->meals_num = mini_atoi(array[4]);
	}
}

static char *get_args(char **argv)
{
	int		i;
	char	*str;
	char	*temp;

	i = 1;
	str = NULL;
	while (argv[i])
	{
		temp = ft_strjoin(str, argv[i++]);
		free(str);
		str = temp;
		temp = ft_strjoin(str, " ");
		free(str);
		str = temp;
	}
	return (str);
}

int	parce_args(t_data *data, int argc, char **argv)
{
	char	*str;
	char	**array;
	int		args_num;

	str = get_args(argv);
	args_num = word_count(str);
	if (args_num != 4 && args_num != 5)
		return (error_msg(USAGE), 1);
	array = (char **)ft_calloc(args_num + 1, sizeof(char *));
	if (!array)
		return (free(str), 1);
	split_args(array, str, 0);
	if (!array[0])
		return (free(str), free(array), 1);
	free(str);
	get_numbers(data, array);
	if (data->ph_num < 1 || data->time_die < 1 || data->time_eat < 1
		|| data->time_sleep < 1 || data->meals_num < 0)
		return (error_msg("Wrong arguments"), 1);
	if (args_num == 4)
		data->meals_num = -1;
	free_arr(array);
	return (0);
}
