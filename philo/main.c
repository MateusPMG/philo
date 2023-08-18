/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:32:55 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/18 11:38:54 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_int(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
		}
	}
	return (0);
}

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
	if (pthread_mutex_init(&(data->check_death), NULL))
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].nb_ate = 0;
		data->philo[i].data = data;
		if (pthread_mutex_init(&(data->philo[i].check_meal), NULL))
			return (1);
		if (pthread_mutex_init(&(data->philo[i].l_ate), NULL))
			return (1);
		if (data->philo[i].id % 2)
		{
			data->philo[i].left_fork = i;
			data->philo[i].right_fork = ((i + 1) % data->nb_philos);
		}
		else
		{
			data->philo[i].right_fork = i;
			data->philo[i].left_fork = ((i + 1) % data->nb_philos);
		}
	}
	data->time_start = 0;
	return (0);
}

int	init_data(t_data *data, char **av)
{
	data->nb_philos = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]) * 1000;
	data->time_sleep = ft_atoi(av[4]) * 1000;
	data->died = 0;
	if ((data->nb_philos < 1 || data->nb_philos > 500) || data->time_die <= 0
		|| data->time_eat <= 0 || data->time_sleep <= 0)
		return (1);
	data->philo = (t_philo *)malloc((sizeof(t_philo) * (data->nb_philos)));
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (data->nb_philos));
	if (!data->philo || !data->forks)
		return (free_data(data));
	if (av[5])
	{
		data->nb_eat = ft_atoi(av[5]);
		if (data->nb_eat <= 0)
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
	if (check_int(ac, av))
		return (write(1, "bad arguments\n", 14));
	if (init_data(&data, av))
		return (write(1, "bad arguments\n", 14));
	run_philos(&data);
	free_data(&data);
	return (0);
}
