/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:33:01 by mpatrao           #+#    #+#             */
/*   Updated: 2023/07/21 16:00:15 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	pthread_t	thread_id;
	int			nb_ate;
}	t_philo;

typedef struct s_data
{
	int					nb_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	t_philo				**philo;
	pthread_mutex_t		**forks;
	pthread_mutex_t		writing;
	pthread_mutex_t		check_meal;
}	t_data;

// utils.c
int	free_data(t_data *data);

#endif