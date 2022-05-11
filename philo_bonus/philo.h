/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:40:10 by tacarlen          #+#    #+#             */
/*   Updated: 2021/09/06 20:33:38 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_general
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_time_each_phil_must_eat;
	int				eating_philo_count;
	unsigned long	time_to_start;
	pthread_t		thread;
	sem_t			*forks;
	sem_t			*message;
	sem_t			*is_dead;
	sem_t			*eat;
}	t_general;

typedef struct s_philosopher
{
	int				id;
	int				eating_count;
	unsigned long	eating_start;
	t_general		*general;

}	t_philosopher;

void			*create(t_general *gen, t_philosopher **philo);
void			*die(void *philo);
void			*live(void *philo);
void			take_forks(t_philosopher *philosoph);
void			*message(t_philosopher *philo, char *str, int i);
void			my_usleep(unsigned long arg_time);
void			sem_safe(int i);
void			destroy(t_philosopher **philo, int i);
int				ft_isdigit(int c);
int				ft_error(char *str);
size_t			ft_strlen(const char *s);
long long		ft_atoi(const char *str);
unsigned long	diff_eating_time(t_philosopher *philo);
unsigned long	diff_time(t_philosopher *philo);
unsigned long	get_time(void);
void			*eating_count(void *philo);

#endif