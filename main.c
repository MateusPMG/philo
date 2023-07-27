/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:32:55 by mpatrao           #+#    #+#             */
/*   Updated: 2023/07/27 13:38:02 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = data->nb_philos;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->check_meal), NULL))
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = data->nb_philos;
	while (--i >= 0)
	{
		data->philo[i]->id = i + 1;
		data->philo[i]->nb_ate = 0;
		data->philo[i]->left_fork = i + 1;
		data->philo[i]->right_fork = (i % data->nb_philos) + 1;
	}
	return (0);
}

int	init_data(t_data *data, char **av)
{
	data->nb_philos = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (data->nb_philos < 1 || data->time_die <= 0 || data->time_eat <= 0
		|| data->time_sleep <= 0)
		return (1);
	data->philo = (t_philo **)malloc((sizeof(t_philo *) * (data->nb_philos)));
	data->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *)
			* (data->nb_philos));
	if (!data->philo || !data->forks)
		return (free_data(data));
	if (av[5])
	{
		data->nb_eat = ft_atoi(av[5]);
		if (data->nb_eat < 0)
			return (1);
	}
	else
		data->nb_eat = -1;
	init_philos(data);
	init_mutex(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (write(1, "wrong number of arguments\n", 26));
	init_data(&data, av);
	start_philos(&data);
	return (0);
}
