/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_eat_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:01:14 by mpatrao           #+#    #+#             */
/*   Updated: 2023/07/27 14:56:36 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void *philo)
{
	;
}

int	start_philos(t_data *data)
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
}
