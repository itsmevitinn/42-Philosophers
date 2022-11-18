/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/17 21:14:52 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_global	global;
	t_data		data;
	pthread_t	killer;
	t_philo		philos;

	if (argc != 5 && argc != 6)
		if (!invalid_args('q'))
			return (0);
	global_data(&global, argc, argv);
	if (!private_data(&data, argc, argv, &global))
		return (0);
	init_mutexes(&data);
	pthread_create(&killer, NULL, &lifetime, &data);
	start_philos(&philos, &data);
	pthread_join(killer, NULL);
	join_philos(&philos, &data);
	destroy_mutexes(&data);
	free_all(&philos, &data);
	return (0);
}

void	global_data(t_global *global, int argc, char **argv)
{
	global->guests = ft_atoi(argv[1]);
	global->end = 0;
	global->meal_access = malloc(sizeof(pthread_mutex_t) * global->guests);
	global->m_forks = malloc(sizeof(pthread_mutex_t) * global->guests);
	global->forks = calloc(sizeof(int), global->guests);
	global->lst_meal = calloc(sizeof(long int), global->guests);
	global->meals = 0;
	if (argc == 6)
		global->meals = calloc(sizeof(int), global->guests);
}

int	private_data(t_data *data, int argc, char **argv, t_global *global)
{
	data->id = 0;
	data->next_fork = 1;
	data->global = global;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->times_must_eat = 0;
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	if (!check_values(data))
	{
		free_data(data);
		return (0);
	}
	return (1);
}

void	start_philos(t_philo *philos, t_data *data)
{
	int		i;

	philos->threads = malloc(sizeof(pthread_t) * data->global->guests);
	philos->data = malloc(sizeof(t_data) * data->global->guests);
	i = -1;
	while (++i < data->global->guests)
	{
		philos->data[i] = *data;
		pthread_create(&philos->threads[i], NULL, &dinner, &philos->data[i]);
		data->id++;
		data->next_fork++;
	}
}

void	join_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->global->guests)
		pthread_join(philos->threads[i], NULL);
}
