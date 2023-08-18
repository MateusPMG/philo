/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:51:59 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/18 11:44:00 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	timestamp(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, 0);
	return (start_time.tv_sec * 1000 + (start_time.tv_usec / 1000));
}

int	free_data(t_data *data)
{
	free(data->philo);
	free(data->pid);
	sem_close(data->check_death);
	sem_close(data->writing);
	sem_close(data->forks);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	signal;
	int	final;

	i = 0;
	signal = 1;
	final = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
		{
			signal *= -1;
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		final = final * 10 + (nptr[i] - '0');
		i++;
	}
	return (final * signal);
}

int	check_int(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
		}
	}
	return (0);
}
