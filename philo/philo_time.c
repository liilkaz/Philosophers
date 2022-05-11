/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:48:07 by tacarlen          #+#    #+#             */
/*   Updated: 2021/08/20 15:11:06 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_error("Error time\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned long	diff_time(t_philosopher *philo)
{
	unsigned long	time;

	time = get_time() - philo->general->time_to_start;
	return (time);
}

unsigned long	diff_eating_time(t_philosopher *philo)
{
	unsigned long	time;

	time = get_time() - philo->eating_start;
	return (time);
}

void	my_usleep(unsigned long arg_time)
{
	unsigned long	end_time;

	end_time = get_time() + arg_time;
	while (get_time() < end_time)
		usleep(100);
}
