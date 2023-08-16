/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:58:55 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/16 13:11:34 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(data->philo[i].check_meal));
		pthread_mutex_destroy(&(data->philo[i].l_ate));
	}
	pthread_mutex_destroy(&(data->writing));
	pthread_mutex_destroy(&(data->check_death));
	free(data->philo);
	free(data->forks);
	return (1);
}

void	ft_sync(t_data *data)
{
	time_t	time;

	time = data->time_start - timestamp();
	if (time > 0)
		usleep(time * 1000);
}

time_t	timestamp(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, 0);
	return (start_time.tv_sec * 1000 + (start_time.tv_usec / 1000));
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
