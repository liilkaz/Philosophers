/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:45:44 by tacarlen          #+#    #+#             */
/*   Updated: 2021/09/06 20:25:42 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eating_count(void *philo)
{
	t_philosopher	*ph;
	int				i;

	ph = philo;
	i = -1;
	while (++i < ph->general->number_of_philosophers)
		sem_wait(ph->general->eat);
	message(ph, "\033[0;32mThe meal is over!", 2);
	sem_post(ph->general->is_dead);
	return (NULL);
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
		philo[i]->eating_start = gen->time_to_start;
		philo[i]->eating_count = 0;
	}
	i = 0;
	create(gen, philo);
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
	sem_unlink("/forks");
	sem_unlink("/message");
	sem_unlink("/dead");
	sem_unlink("/eat");
	gen.forks = sem_open("/forks", O_CREAT, 0644, gen.number_of_philosophers);
	gen.message = sem_open("/message", O_CREAT, 0644, 1);
	gen.is_dead = sem_open("/dead", O_CREAT, 0644, 0);
	gen.eat = sem_open("/eat", O_CREAT, 0644, 0);
	if (gen.forks == SEM_FAILED || gen.message == SEM_FAILED || \
			gen.is_dead == SEM_FAILED || gen.eat == SEM_FAILED)
		ft_error("ERROR");
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
