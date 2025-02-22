/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:54:55 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/22 10:32:37 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	mini_atoi(const char *str)
{
	size_t	i;
	size_t	num;

	if (!str)
		return (0);
	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}

void	data_init(t_data *data, char **array)
{
	data->ph_num = mini_atoi(array[0]);
	data->time_die = mini_atoi(array[1]);
	data->time_eat = mini_atoi(array[2]);
	data->time_sleep = mini_atoi(array[3]);
	if (array[4])
		data->meals_num = mini_atoi(array[4]);
}

int	args_check(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		if (array[i][j] == '+')
			j++;
		while(array[i][j])
		{
			if (!(array[i][j] >= '0' && array[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	if (i != 4 && i != 5)
		return (1);
	return(0);
}

char *get_args(char **argv)
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

	if (argc < 2)
		return (error_msg(USAGE), 1);
	str = get_args(argv);
	array = (char **)ft_calloc(ft_word_count(str) + 1, sizeof(char *));
	if (!array)
		return (free(str), 1);
	split_args(array, str, 0);
	if (!array[0])
		return (free(str), free(array), 1);
	free(str);
	if (args_check(array))
		return (free_arr(array), error_msg("Wrong arguments"), 1);
	data_init(data, array);
	free_arr(array);
	if (data->ph_num < 1 || data->time_die < 1 || data->time_eat < 1
		|| data->time_sleep < 1|| data->meals_num < 0)
		return (error_msg("Wrong arguments"), 1);
	return (0);
}
