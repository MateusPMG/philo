/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:48:04 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/17 12:36:44 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

struct	s_data;
typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread_id;
	int				id;
	int				nb_ate;
	time_t			last_ate;
}	t_philo;

typedef struct s_data
{
	int			nb_philos;
	int			nb_eat;
	int			died;
	t_philo		*philo;
	sem_t		*forks;
	sem_t		*writing;
	sem_t		*check_death;
	time_t		time_start;
	time_t		time_die;
	time_t		time_eat;
	time_t		time_sleep;
	pid_t		*pid;
}	t_data;

//utils_bonus.c
time_t	timestamp(void);

//run_philos_bonus_utils.c
void	ft_sync(t_data *data);
void	think(t_data *data, t_philo *philo);
void	single(t_data *data, t_philo *philo);

//run_philos_bonus.c
int		run_philos(t_data *data);

#endif