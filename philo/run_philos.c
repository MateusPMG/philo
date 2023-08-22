/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:01:14 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/22 16:04:35 by mpatrao          ###   ########.fr       */
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
	pthread_mutex_lock(&(phil->l_ate));
	phil->t_last_ate = timestamp();
	pthread_mutex_unlock(&(phil->l_ate));
	printer(data, phil->id, "is eating");
	usleep(data->time_eat);
	pthread_mutex_lock(&(phil->check_meal));
	(phil->nb_ate)++;
	pthread_mutex_unlock(&(phil->check_meal));
	pthread_mutex_unlock(&(data->forks[phil->left_fork]));
	pthread_mutex_unlock(&(data->forks[phil->right_fork]));
}

void	think(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->l_ate);
	time_to_think = (philo->data->time_die
			- (timestamp() - philo->t_last_ate)
			- philo->data->time_eat) / 2;
	if (!(philo->nb_ate == philo->data->nb_eat))
		printer(philo->data, philo->id, "is thinking");
	pthread_mutex_unlock(&philo->l_ate);
	if (time_to_think <= 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	usleep(time_to_think * 1000);
}

int	eat_check(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->check_meal);
	if (philo->nb_ate < data->nb_eat)
	{
		pthread_mutex_unlock(&philo->check_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->check_meal);
	return (0);
}

void	*routine(void *phil)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)phil;
	data = philo->data;
	ft_sync(data);
	if (data->nb_philos == 1)
	{
		single(philo, data);
		return (0);
	}
	if (philo->id % 2)
		usleep(1000);
	while (!check_died(data, philo))
	{
		eat(philo);
		printer(data, philo->id, "is sleeping");
		usleep(data->time_sleep);
		think(philo);
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
		ph[i].t_last_ate = data->time_start;
		if (pthread_create(&(ph[i].thread_id), NULL, routine, &(ph[i])))
			return (1);
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
