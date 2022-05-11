/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:53:19 by tacarlen          #+#    #+#             */
/*   Updated: 2021/09/06 20:32:46 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*message(t_philosopher *philo, char *str, int i)
{
	if (i == 0)
	{
		sem_safe(sem_wait(philo->general->message));
		printf("⏳%lu %d %s\n", diff_time(philo), philo->id, str);
		sem_safe(sem_post(philo->general->message));
		return (NULL);
	}
	else if (i == 1)
	{
		sem_safe(sem_wait(philo->general->message));
		printf("⌛️%lu %d %s 💀\n", diff_time(philo), philo->id, str);
		usleep (1001);
		sem_safe(sem_post(philo->general->is_dead));
		return (NULL);
	}
	else if (i == 2)
	{
		sem_safe(sem_post(philo->general->message));
		printf("%s\n", str);
		sem_safe(sem_post(philo->general->is_dead));
		return (NULL);
	}
	return (0);
}

void	take_forks(t_philosopher *philosoph)
{
	sem_safe(sem_wait(philosoph->general->forks));
	message(philosoph, "\033[2;36mhas taken a fork\033[0m", 0);
	sem_safe(sem_wait(philosoph->general->forks));
	message(philosoph, "\033[2;36mhas taken a fork\033[0m", 0);
}

void	*live(void *philo)
{
	t_philosopher	*phil;

	phil = philo;
	pthread_detach(phil->general->thread);
	pthread_create(&phil->general->thread, NULL, die, philo);
	while (1)
	{
		take_forks(phil);
		phil->eating_start = get_time();
		message(phil, "\033[1;32mis eatting\033[0m", 0);
		phil->eating_count++;
		if (phil->eating_count == phil->general->num_of_time_each_phil_must_eat)
			sem_post(phil->general->eat);
		my_usleep(phil->general->time_to_eat);
		sem_post(phil->general->forks);
		sem_post(phil->general->forks);
		message(phil, "\033[3;33mis sleeping\033[0m", 0);
		my_usleep(phil->general->time_to_sleep);
		message(phil, "\033[0;36mis thinking\033[0m", 0);
	}
	return (0);
}

void	*die(void *philo)
{
	t_philosopher	*ph;
	unsigned long	time_for_die;

	ph = philo;
	while (1)
	{
		time_for_die = ph->general->time_to_die + ph->eating_start;
		if ((int)diff_eating_time(ph) > ph->general->time_to_die \
									|| get_time() > time_for_die)
		{
			message(ph, "\033[0;31mis dead", 1);
			return (NULL);
		}
	}
}

void	*create(t_general *gen, t_philosopher **philo)
{
	pid_t	pid[200];
	int		i;

	i = -1;
	if (gen->num_of_time_each_phil_must_eat != 0)
		pthread_create(&gen->thread, NULL, eating_count, philo[0]);
	while (++i < gen->number_of_philosophers)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (NULL);
		if (!pid[i])
			live(philo[i]);
	}
	pid[i] = 0;
	i = -1;
	sem_safe(sem_wait(philo[0]->general->is_dead));
	while (pid[++i] != 0)
		kill(pid[i], SIGKILL);
	return (0);
}
