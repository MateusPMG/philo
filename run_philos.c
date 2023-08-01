/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:01:14 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/01 15:51:39 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *phil)
{
	t_data	*data;

	data = phil->data;
	pthread_mutex_lock(&(data->forks[phil->left_fork]));
	printer(\\ include x grabbed a fork msg);
	pthread_mutex_lock(&(data->forks[phil->right_fork]));
	printer(\\ include x grabbed a fork msg);
	printer(\\ include x is eating);
	phil->t_last_ate = timestamp();
	sleep_func(\\ when should he eat?);
	(phil->nb_ate)++;
	pthread_mutex_unlock(&(data->forks[phil->left_fork]));
	pthread_mutex_unlock(&(data->forks[phil->right_fork]));
	
}

void	routine(void *phil)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)phil;
	data = philo->data;
	if (\\ what condition???)
		sleep_func();
	while (!(data->died))
	{
		if (data->all_ate)
			break ;
		eat();
		printer("sleeping");
		sleep_func();
		printer("thinking");
	}
	return (0);
}

int	run_philos(t_data *data)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = data->philo;
	data->time_start = timestamp();
	while (i < data->nb_philos)
	{
		if (pthread_create(&(ph[i].thread_id), NULL, routine, &(ph[i])))
			return (1);
		ph[i].t_last_ate = timestamp();
		i++;
	}
	check_death();
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(&(ph[i].thread_id), NULL))
			return (1);
		i++;
	}
	return (0);
}
