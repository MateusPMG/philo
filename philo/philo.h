/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:33:01 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/17 13:37:18 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int					id;
	int					left_fork;
	int					right_fork;
	pthread_t			thread_id;
	int					nb_ate;
	struct s_data		*data;
	time_t				t_last_ate;
	pthread_mutex_t		check_meal;
	pthread_mutex_t		l_ate;
}	t_philo;

typedef struct s_data
{
	int					nb_philos;
	time_t				time_die;
	time_t				time_eat;
	time_t				time_sleep;
	int					nb_eat;
	int					died;
	time_t				time_start;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing;
	pthread_mutex_t		check_death;
}	t_data;

// run_philos.c
int			run_philos(t_data *data);

//run_philos_utils.c
void		printer(t_data	*data, int id, char *str);
void		single(t_philo *philo, t_data *data);
int			died(t_data *data);
void		supervisor(t_data *data);
int			check_died(t_data *data);

// utils.c
int			free_data(t_data *data);
int			ft_atoi(const char *nptr);
time_t		timestamp(void);
void		ft_sync(t_data *data);
int			died_checks(t_data *data, int i);

#endif