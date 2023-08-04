/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:08:23 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/04 12:26:04 by mpatrao          ###   ########.fr       */
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
