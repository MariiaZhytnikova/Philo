/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:52:01 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/23 18:46:17 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	*ft_calloc(size_t num, size_t size)
{
	size_t			byte_size;
	size_t			i;
	unsigned char	*object;

	byte_size = num * size;
	if (byte_size == 0)
		return (NULL);
	if (size != 0 && num != byte_size / size)
		return (NULL);
	object = malloc(byte_size);
	if (!object)
		return (NULL);
	i = 0;
	while (i < byte_size)
	{
		object[i] = 0;
		i++;
	}
	return ((void *)object);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*res;
	size_t	i;

	res = NULL;
	s1_len = 0;
	s2_len = 0;
	if (s1)
		while (s1[s1_len])
			s1_len++;
	if (s2)
		while (s2[s2_len])
			s2_len++;
	res = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < s1_len)
		res[i++] = *s1++;
	while (i < s1_len + s2_len)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

size_t	word_count(char *str)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == ' ')
			in_word = 0;
		str++;
	}
	return (count);
}

void	split_args(char **res, char *args, int k)
{
	int	i;
	int	start;
	int	end;

	start = 0;
	while (args[start] && args[start] == ' ')
		start++;
	if (!args[start])
		return ;
	end = start;
	while (args[end] && args[end] != ' ')
		end++;
	res[k] = (char *)ft_calloc(end - start + 1, sizeof(char));
	if (!res[k])
		return (free_arr(res));
	i = 0;
	while (start < end)
		res[k][i++] = args[start++];
	res[k][i] = 0;
	if (args[end])
		split_args(res, &args[end], k + 1);
}