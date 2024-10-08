/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:30:30 by lucas             #+#    #+#             */
/*   Updated: 2024/09/07 18:18:49 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ./philo nb ttdie tteat ttsleep [max meal]*/
static bool inline	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static bool inline	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*is_valid(const char *str)
{
	int	len_str;
	const char	*nbr;
	
	len_str = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
		error_exit("don't feed with negative values");
	if (!is_digit(*str))
		error_exit("input is not a correct digit");
	nbr = str;
	while (is_digit(*str++))
		len_str++;
	if (len_str > 10)
		error_exit("INT MAX is the limit");
	return (nbr);
}

static long    ft_atol(const char *str)
{
	int	num;

	num = 0;
	str = is_valid(str);
	while (is_digit(*str))
		num = num * 10 + *str++ - '0';
	if (num > INT_MAX)
		error_exit("INT MAX is the limit");
	return (num);
}
void    parsing(t_data *data, char **av)
{
	data->nb_philo = ft_atol(av[1]);
	data->ttdie = ft_atol(av[2]) * 1e3;
	data->tteat = ft_atol(av[3]) * 1e3;
	data->ttsleep = ft_atol(av[4]) * 1e3;
	if (data->ttdie < 6e4 || data->tteat < 6e4 || data->ttsleep < 6e4) // 6e4 = 60K = 60ms
		error_exit("Timestamps must be major than 60ms");
	if (av[5])
		data->max_meal = atol(av[5]);
	else
		data->max_meal = -1; // use as a flag
}