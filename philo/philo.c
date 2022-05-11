/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:45:44 by tacarlen          #+#    #+#             */
/*   Updated: 2021/09/06 20:34:42 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_philosopher **philo, int i)
{
	while (++i < philo[0]->general->number_of_philosophers)
		pthread_mutex_destroy(&philo[i]->right_fork);
	pthread_mutex_destroy(&philo[0]->general->message);
	pthread_mutex_destroy(&philo[0]->general->is_dead);
}

void	philo_init(t_general *gen)
{
	t_philosopher	**philo;
	int				i;

	i = -1;
	philo = malloc(sizeof(t_philosopher) * gen->number_of_philosophers);
	if (!philo)
		ft_error("\033[0;31mMemory allocation error!\n");
	while (++i < gen->number_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philosopher));
		if (!philo[i])
			ft_error("\033[0;31mMemory allocation error!\n");
		philo[i]->id = i + 1;
		philo[i]->general = gen;
		mutex_safe(pthread_mutex_init(&philo[i]->right_fork, NULL));
		philo[i]->eating_start = gen->time_to_start;
		philo[i]->eating_count = 0;
	}
	i = 0;
	while (++i < gen->number_of_philosophers)
		philo[i]->left_fork = &philo[i - 1]->right_fork;
	philo[0]->left_fork = &philo[i - 1]->right_fork;
	create(gen, philo);
	destroy(philo, -1);
	free (philo);
}

void	general_init(int argc, char **argv)
{
	t_general	gen;

	gen.number_of_philosophers = ft_atoi(argv[1]);
	gen.time_to_die = ft_atoi(argv[2]);
	gen.time_to_eat = ft_atoi(argv[3]);
	gen.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		gen.num_of_time_each_phil_must_eat = ft_atoi(argv[5]);
	else
		gen.num_of_time_each_phil_must_eat = -1;
	gen.eating_philo_count = 0;
	gen.time_to_start = get_time();
	mutex_safe(pthread_mutex_init(&gen.message, NULL));
	mutex_safe(pthread_mutex_init(&gen.is_dead, NULL));
	philo_init(&gen);
}

int	parser(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (ft_error("\033[0;31mThis is a wrong arguments!\n"));
		}
	}
	i = 0;
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) < 1)
			return (ft_error("\033[0;31mThis is a wrong arguments!\n"));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_error("\033[0;31mError: arguments!\n"));
	if (parser(argv))
		return (1);
	general_init(argc, argv);
}
