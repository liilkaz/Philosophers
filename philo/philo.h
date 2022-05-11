/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:40:10 by tacarlen          #+#    #+#             */
/*   Updated: 2021/08/20 16:47:54 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_general
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_time_each_phil_must_eat;
	int				eating_philo_count;
	pthread_mutex_t	message;
	pthread_mutex_t	is_dead;
	pthread_t		thread;
	unsigned long	time_to_start;
}	t_general;

typedef struct s_philosopher
{
	int				id;
	int				eating_count;
	unsigned long	eating_start;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	pthread_t		threads;
	t_general		*general;

}	t_philosopher;

void			create(t_general *gen, t_philosopher **philo);
void			*die(void *philo);
void			*live(void *philo);
void			take_forks(t_philosopher *philosoph);
void			*message(t_philosopher *philo, char *str, int i);
void			my_usleep(unsigned long arg_time);
void			mutex_safe(int i);
void			destroy(t_philosopher **philo, int i);
int				ft_isdigit(int c);
int				ft_error(char *str);
size_t			ft_strlen(const char *s);
long long		ft_atoi(const char *str);
unsigned long	diff_eating_time(t_philosopher *philo);
unsigned long	diff_time(t_philosopher *philo);
unsigned long	get_time(void);

#endif