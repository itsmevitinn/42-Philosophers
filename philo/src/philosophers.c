/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/07 14:59:11 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	pthread_t	killer;
	t_data		data;
	t_global	global;

	if (argc != 5 && argc != 6)
		if (!invalid_args())
			return (0);
	start_global(&global, argv);
	if (!create_data(&data, argv, argc, &global))
	{
		free_all(&data);
		return (0);
	}
	init_mutexes(&data);
	pthread_create(&killer, NULL, &lifetime, &data);
	pthread_detach(killer);
	create_philo_threads(&data);
	join_philos(&data);
	destroy_mutexes(&data);
	free_all(&data);
	return (0);
}

void	start_global(t_global *global, char **argv)
{
	global->guests = ft_atoi(argv[1]);
	global->end = 0;
	global->meal_access = malloc(sizeof(pthread_mutex_t) * global->guests);
	global->m_forks = malloc(sizeof(pthread_mutex_t) * global->guests);
	global->forks = malloc(sizeof(int) * global->guests);
	// global->forks = memset(global->forks, 1, sizeof(int) * global->guests);
	global->lst_meal = malloc(sizeof(long int) * global->guests);
	// global->lst_meal = memset(global->lst_meal, 0, sizeof(long int) * global->guests);
}

int	create_data(t_data *data, char **argv, int argc, t_global *global)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->times_must_eat = 0;
	data->meals = 0;
	data->global = global;
	data->ph_thread = malloc(sizeof(pthread_t) * data->global->guests);
	data->ph_data = malloc(sizeof(t_data) * data->global->guests);
	data->id = 0;
	if (argc == 6)
	{
		data->times_must_eat = ft_atoi(argv[5]);
		data->meals = malloc(sizeof(int) * data->global->guests);
		data->meals = memset(data->meals, 0, sizeof(int) * data->global->guests);
		data->all_eaten = 0;
	}
	if (!check_values(data))
		return (0);
	return (1);
}

int	check_values(t_data *data)
{
	if (data->global->guests == 2147483650)
		return (invalid_values());
	else if (data->time_to_die == 2147483650)
		return (invalid_values());
	else if (data->time_to_eat == 2147483650)
		return (invalid_values());
	else if (data->time_to_sleep == 2147483650)
		return (invalid_values());
	else if (data->times_must_eat == 2147483650)
		return (invalid_values());
	return (1);
}

void	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->global->guests)
	{
		pthread_mutex_init(&data->global->m_forks[i], NULL);
		pthread_mutex_init(&data->global->meal_access[i], NULL);
	}
	pthread_mutex_init(&data->global->print, NULL);
}

void	create_philo_threads(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->global->guests)
	{
		data->ph_data[i] = *data;
		pthread_create(&data->ph_thread[i], NULL, &dinner, &data->ph_data[i]);
		// pthread_detach(data->ph_thread[i]);
		data->id++;
	}
}

void	join_philos(t_data *data)
{
	int i;

	i = -1;
	while(++i < data->global->guests)
		pthread_join(data->ph_thread[i], NULL);
}
