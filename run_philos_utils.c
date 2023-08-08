/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:08:23 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/08 14:14:15 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printer(t_data	*data, int id, char *str)
{
	pthread_mutex_lock(&(data->writing));
	printf("%lli, philo %i %s\n", timestamp() - data->time_start, id, str);
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

// checks wether someone died or they all ate x nb of times
// and changes the respective flag
void	supervisor(t_data *data)
{
	
}
