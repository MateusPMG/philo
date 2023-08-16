/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:48:24 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/16 15:56:01 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].nb_ate = 0;
		data->philo[i].data = data;
	}
	data->time_start = 0;
	sem_unlink("/forks_s");
	sem_unlink("/check_d_s");
	sem_unlink("/writing_s");
	data->forks = sem_open("/forks_s", O_CREAT, 0644, data->nb_philos);
	data->check_death = sem_open("/check_d_s", O_CREAT, 0644, 1);
	data->writing = sem_open("/writing_s", O_CREAT, 0644, 1);
	return (0);
}

int	init_data(t_data *data, char **av)
{
	data->nb_philos = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]) * 1000;
	data->time_sleep = ft_atoi(av[4]) * 1000;
	data->died = 0;
	if (data->nb_philos < 1 || data->time_die <= 0 || data->time_eat <= 0
		|| data->time_sleep <= 0)
		return (1);
	data->philo = (t_philo *)malloc((sizeof(t_philo) * (data->nb_philos)));
	data->pid = (pid_t *)malloc(sizeof(pid_t) * (data->nb_philos));
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
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (write(1, "wrong number of arguments\n", 26));
	if (init_data(&data, av))
		return (write(1, "bad arguments\n", 14));
	run_philos(&data);
	free_data(&data);
	return (0);
}
