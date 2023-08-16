/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:51:19 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/16 18:46:35 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine()
{
	
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
			routine();
	}
	return (0);
}
