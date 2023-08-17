/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philos_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:51:19 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/17 15:10:38 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_sleep(t_data *data, t_philo *philo)
{
	sem_wait(data->forks);
	printer(data, philo->id, "has taken a fork");
	sem_wait(data->forks);
	printer(data, philo->id, "has taken a fork");
	sem_wait(data->check_death);
	if (timestamp() - philo->last_ate <= data->time_die)
		philo->last_ate = timestamp();
	sem_post(data->check_death);
	printer(data, philo->id, "is eating");
	usleep(data->time_eat);
	philo->nb_ate++;
	if (philo->nb_ate == data->nb_eat)
		exit(0);
	sem_post(data->forks);
	sem_post(data->forks);
	printer(data, philo->id, "is sleeping");
	usleep(data->time_sleep);
}

void	think(t_philo *philo)
{
	time_t	time_to_think;

	sem_wait(philo->data->check_death);
	time_to_think = (philo->data->time_die
			- (timestamp() - philo->last_ate)
			- philo->data->time_eat) / 2;
	sem_post(philo->data->check_death);
	if (time_to_think <= 0)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	printer(philo->data, philo->id, "is thinking");
	usleep(time_to_think * 1000);
}

int	routine(t_data *data, t_philo *philo)
{
	if (pthread_create(&philo->thread_id, NULL, supervisor, philo))
		return (1);
	if (pthread_detach(philo->thread_id))
		return (1);
	ft_sync(data);
	if (philo->id % 2)
		think(philo);
	while (1)
	{
		eat_sleep(data, philo);
		think(philo);
	}
}

void	*ft_wait(t_data *data)
{
	int	i;
	int	j;
	int	status;

	i = -1;
	j = -1;
	while (++i < data->nb_philos)
	{
		waitpid(data->pid[i], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			while (++j < data->nb_philos)
				kill(data->pid[i], SIGTERM);
			break ;
		}
	}
	return (0);
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
	ft_wait(data);
	return (0);
}
