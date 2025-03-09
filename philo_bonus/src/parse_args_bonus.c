/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:54:55 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/08 18:22:37 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <limits.h>

static int	mini_atoi(const char *str)
{
	size_t		i;
	long long	num;
	int			j;

	if (!str)
		return (0);
	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	j = i;
	while (str[j])
	{
		if (!(str[j] >= '0' && str[j] <= '9'))
			return (-1);
		j++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}

static int	get_numbers(t_data *data, char **array)
{
	int	time_die;
	int	time_eat;
	int	time_sleep;

	time_die = mini_atoi(array[1]);
	time_eat = mini_atoi(array[2]);
	time_sleep = mini_atoi(array[3]);
	data->ph_num = mini_atoi(array[0]);
	if (array[4])
		data->meals_num = mini_atoi(array[4]);
	if (data->ph_num < 1 || time_die < 1 || time_eat < 1
		|| time_sleep < 1 || data->meals_num < 0)
		return (1);
	data->time_die = (size_t)time_die;
	data->time_eat = (size_t)time_eat;
	data->time_sleep = (size_t)time_sleep;
	return (0);
}

static int	str_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != ' '
			&& str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_args(char **argv)
{
	int		i;
	char	*str;
	char	*temp;

	i = 1;
	str = NULL;
	while (argv[i])
	{
		temp = ft_strjoin(str, argv[i++]);
		if (!temp)
			return (NULL);
		free(str);
		str = temp;
		temp = ft_strjoin(str, " ");
		if (!temp)
			return (free(str), NULL);
		free(str);
		str = temp;
	}
	if (str_check(str))
		return (free(str), NULL);
	return (str);
}

int	parse_args(t_data *data, char **argv)
{
	char	*str;
	char	**array;
	int		args_num;

	str = get_args(argv);
	if (!str)
		return (error_msg("Something wrong"), 1);
	args_num = word_count(str);
	if (args_num != 4 && args_num != 5)
		return (error_msg(USAGE), 1);
	array = (char **)ft_calloc(args_num + 1, sizeof(char *));
	if (!array)
		return (error_msg("Something wrong"), free(str), 1);
	split_args(array, str, 0);
	if (!array || !array[0])
		return (error_msg("Error"), free(str), free(array), 1);
	free(str);
	if (get_numbers(data, array))
		return (error_msg("Wrong arguments"), 1);
	if (args_num == 4)
		data->meals_num = -1;
	free_arr(array);
	return (0);
}
