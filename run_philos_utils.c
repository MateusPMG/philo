/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:08:23 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/10 15:13:57 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// checks wether someone died or they all ate x nb of times
// and changes the respective flag
void	printer(t_data	*data, int id, char *str)
{
	int	t;

	t = timestamp() - data->time_start;
	if (check_died(data))
		return ;
	pthread_mutex_lock(&(data->writing));
	printf("%i philo %i %s\n", t, id, str);
	pthread_mutex_unlock(&(data->writing));
	return ;
}

void	single(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	printer(data, philo->id, "has taken a fork");
	usleep(data->time_die);
	printer(data, philo->id, "has died");
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
}

int	died(t_data *data)
{
	pthread_mutex_lock(&(data->check_death));
	data->died = 1;
	pthread_mutex_unlock(&(data->check_death));
	return (1);
}

int	check_died(t_data *data)
{
	pthread_mutex_lock(&(data->check_death));
	if (data->died)
	{
		pthread_mutex_unlock(&(data->check_death));
		return (1);
	}
	pthread_mutex_unlock(&(data->check_death));
	return (0);
}

// checks wether someone died or they all ate x nb of times
void	supervisor(t_data *data)
{
	int	i;
	int	a;

	ft_sync(data);
	while (1)
	{
		i = -1;
		a = 1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(&(data->l_ate));
			//printf("%li and %li\n", (timestamp() - data->philo[i].t_last_ate), data->time_die2);
			if ((data->time_die / 1000) <= timestamp() - data->philo[i].t_last_ate)
			{
				printer(data, data->philo[i].id, "has died");
				died(data);
				pthread_mutex_unlock(&(data->l_ate));
				return ;
			}
			pthread_mutex_unlock(&(data->l_ate));
			if (data->nb_eat == -1)
				continue ;
			if (data->philo[i].nb_ate < data->nb_eat)
				a = 0;
		}
		if (data->nb_eat != -1 && a && died(data))
			return ;
	}
}
