/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:53:19 by tacarlen          #+#    #+#             */
/*   Updated: 2021/08/20 22:36:29 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*message(t_philosopher *philo, char *str, int i)
{
	if (i == 0)
	{
		mutex_safe(pthread_mutex_lock(&philo->general->message));
		printf("⏳%lu %d %s\n", diff_time(philo), philo->id, str);
		mutex_safe(pthread_mutex_unlock(&philo->general->message));
		return (NULL);
	}
	else if (i == 1)
	{
		mutex_safe(pthread_mutex_lock(&philo->general->message));
		printf("⌛️%lu %d %s 💀\n", diff_time(philo), philo->id, str);
		usleep (1001);
		mutex_safe(pthread_mutex_unlock(&philo->general->is_dead));
		return (NULL);
	}
	else if (i == 2)
	{
		mutex_safe(pthread_mutex_lock(&philo->general->message));
		printf("%s\n", str);
		mutex_safe(pthread_mutex_unlock(&philo->general->is_dead));
		return (NULL);
	}
	return (0);
}

void	take_forks(t_philosopher *philosoph)
{
	if (philosoph->id % 2)
	{
		mutex_safe(pthread_mutex_lock(&philosoph->right_fork));
		message(philosoph, "\033[2;36mhas taken a fork\033[0m", 0);
		mutex_safe(pthread_mutex_lock(philosoph->left_fork));
		message(philosoph, "\033[2;36mhas taken a fork\033[0m", 0);
	}
	else
	{
		mutex_safe(pthread_mutex_lock(philosoph->left_fork));
		message(philosoph, "\033[2;36mhas taken a fork\033[0m", 0);
		mutex_safe(pthread_mutex_lock(&philosoph->right_fork));
		message(philosoph, "\033[2;36mhas taken a fork\033[0m", 0);
	}
}

void	*live(void *philo)
{
	t_philosopher	*phil;

	phil = philo;
	pthread_detach(phil->threads);
	while (1)
	{
		take_forks(phil);
		phil->eating_start = get_time();
		message(phil, "\033[1;32mis eatting\033[0m", 0);
		phil->eating_count++;
		if (phil->eating_count == phil->general->num_of_time_each_phil_must_eat)
			phil->general->eating_philo_count++;
		my_usleep(phil->general->time_to_eat);
		mutex_safe(pthread_mutex_unlock(&phil->right_fork));
		mutex_safe(pthread_mutex_unlock(phil->left_fork));
		message(phil, "\033[3;33mis sleeping\033[0m", 0);
		my_usleep(phil->general->time_to_sleep);
		message(phil, "\033[0;36mis thinking\033[0m", 0);
	}
	return (0);
}

void	*die(void *philo)
{
	t_philosopher	**ph;
	unsigned long	time_for_die;
	int				i;

	ph = philo;
	while (1)
	{
		i = -1;
		while (++i < ph[0]->general->number_of_philosophers)
		{
			time_for_die = ph[i]->general->time_to_die + ph[i]->eating_start;
			if (ph[i]->general->eating_philo_count == \
				ph[i]->general->number_of_philosophers)
			{
				message(ph[i], "\033[0;32mThe meal is over!", 2);
				return (NULL);
			}
			if ((int)diff_eating_time(ph[i]) > ph[i]->general->time_to_die \
										|| get_time() > time_for_die)
			{
				message(ph[i], "\033[0;31mis dead", 1);
				return (NULL);
			}
		}
	}
}

void	create(t_general *gen, t_philosopher **philo)
{
	int	i;

	i = -1;
	mutex_safe(pthread_mutex_lock(&gen->is_dead));
	mutex_safe(pthread_create(&gen->thread, NULL, die, philo));
	while (++i < gen->number_of_philosophers)
	{
		mutex_safe(pthread_create(&philo[i]->threads, NULL, live, philo[i]));
		usleep (10);
	}
	mutex_safe(pthread_join(gen->thread, NULL));
	mutex_safe(pthread_mutex_lock(&gen->is_dead));
}
