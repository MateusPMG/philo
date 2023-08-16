/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:51:59 by mpatrao           #+#    #+#             */
/*   Updated: 2023/08/16 18:10:51 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	timestamp(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, 0);
	return (start_time.tv_sec * 1000 + (start_time.tv_usec / 1000));
}