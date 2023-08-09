/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:01:14 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/09 16:12:45 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *phil)
{
	t_data	*data;

	data = phil->data;
	pthread_mutex_lock(&(data->forks[phil->left_fork]));
	printer(data, phil->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[phil->right_fork]));
	printer(data, phil->id, "has taken a fork");
	printer(data, phil->id, "is eating");
	usleep(data->time_eat);
	phil->t_last_ate = timestamp();
	pthread_mutex_lock(&(data->check_meal));
	(phil->nb_ate)++;
	pthread_mutex_unlock(&(data->check_meal));
	pthread_mutex_unlock(&(data->forks[phil->left_fork]));
	pthread_mutex_unlock(&(data->forks[phil->right_fork]));
}

void	*routine(void *phil)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)phil;
	data = philo->data;
	ft_sync(data);
	if (data->nb_philos)
	{
		single(philo, data);
		return (0);
	}
	while (!(data->died))
	{
		eat(philo);
		printer(data, philo->id, "is sleeping");
		usleep(data->time_sleep);
		printer(data, philo->id, "is thinking");
	}
	return (0);
}

int	run_philos(t_data *data)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = data->philo;
	data->time_start = timestamp() + (data->nb_philos * 2);
	while (i < data->nb_philos)
	{
		if (pthread_create(&(ph[i].thread_id), NULL, routine, &(ph[i])))
			return (1);
		ph[i].t_last_ate = data->time_start;
		i++;
	}
	if (data->nb_philos > 1)
		supervisor(data);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join((ph[i].thread_id), NULL))
			return (1);
		i++;
	}
	return (0);
}
