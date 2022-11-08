/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/08 18:04:50 by vsergio          ###   ########.fr       */
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
		if (!invalid_args())
			return (0);
	global_data(&global, argc, argv);
	if (!private_data(&data, argc, argv, &global))
	{
		free_data(&data);
		return (0);
	}
	init_mutexes(&data);
	pthread_create(&killer, NULL, &lifetime, &data);
	pthread_detach(killer);
	start_philos(&philos, &data);
	join_philos(&philos, &data);
	usleep(1000); //wait untill all threads end
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
	global->forks = malloc(sizeof(int) * global->guests);
	global->forks = memset(global->forks, 0, sizeof(int) * global->guests);
	global->lst_meal = malloc(sizeof(long int) * global->guests);
	global->lst_meal = memset(global->lst_meal, 0, sizeof(long int) * global->guests);
	global->meals = 0;
	if (argc == 6)
	{
		global->meals = malloc(sizeof(int) * global->guests);
		global->meals = memset(global->meals, 0, sizeof(int) * global->guests);
	}
}

int	private_data(t_data *data, int argc, char **argv, t_global *global)
{
	data->id = 0;
	data->global = global;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->times_must_eat = 0;
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
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
	pthread_mutex_init(&data->global->print, NULL);
	pthread_mutex_init(&data->global->finish, NULL);
	while (++i < data->global->guests)
	{
		pthread_mutex_init(&data->global->m_forks[i], NULL);
		pthread_mutex_init(&data->global->meal_access[i], NULL);
	}
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
	}
}

void	join_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->global->guests)
	{
		pthread_join(philos->threads[i], NULL);
		printf("philo ended\n");
	}
}
