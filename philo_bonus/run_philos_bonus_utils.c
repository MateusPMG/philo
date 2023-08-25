/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos_bonus_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:52:03 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/25 16:50:43 by mpatrao          ###   ########.fr       */
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

void	printer(t_data *data, int id, char *str)
{
	int	t;

	t = timestamp() - data->time_start;
	sem_wait(data->writing);
	printf("%i philo %i %s\n", t, id, str);
	sem_post(data->writing);
	return ;
}

void	*supervisor(void *phil)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)phil;
	data = philo->data;
	ft_sync(data);
	while (1)
	{
		sem_wait(data->check_death);
		if (timestamp() - philo->last_ate >= data->time_die)
		{
			printer(data, philo->id, "has died");
			sem_post(data->check_death);
			exit(1);
		}
		sem_post(data->check_death);
	}
}
