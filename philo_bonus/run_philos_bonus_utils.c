/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos_bonus_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:52:03 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/17 12:36:57 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sync(t_data *data)
{
	time_t	time;

	time = data->time_start - timestamp();
	if (time > 0)
		usleep(time * 1000);
}

void	think(t_data *data, t_philo *philo)
{
	
}

void	single(t_data *data, t_philo *philo)
{
	
}

void	printer(t_data *data, int id, char *str)
{
	int	t;

	t = timestamp() - data->time_start;
	//need a death condition
	if (?)
		return ;
	//semaphore
	printf("%i philo %i %s\n", t, id, str);
	//semaphore
	return ;
}

void	supervisor(void *phil)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)phil;
	data = philo->data;

	while (1)
	{
		
	}
}
