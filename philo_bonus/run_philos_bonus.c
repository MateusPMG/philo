/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:51:19 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/17 12:48:17 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_sleep(t_data *data, t_philo *philo)
{
	//semaphore forks decrement
	//fork take msg
	//semaphore forks decrement
	//fork take msg
	//eating msg
	//semaphore timestamp
	//update last ate time
	//semaphore timestamp
	//printer (put semaphores inside for writing)
	
}

void	routine(t_data *data, t_philo *philo)
{
	if (pthread_create(philo->thread_id, NULL, supervisor(), philo))
		return (1);
	if (pthread_detach(philo->thread_id))
		return (1);
	ft_sync(data);
	if (philo->id % 2)
		think(data, philo);
	while (1)
	{
		eat_sleep(data, philo);
		think(data, philo);
	}
}

int	run_philos(t_data *data)
{
	int	i;

	i = -1;
	data->time_start = timestamp() + (data->nb_philos * 2);
	while (++i < data->nb_philos)
	{
		data->philo[i].last_ate = data->time_start;
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (1);
		else if (!data->pid[i])
			routine(data, &data->philo[i]);
	}
	return (0);
}
