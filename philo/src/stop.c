/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:09:09 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/08 17:44:38 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	invalid_args(void)
{
	printf("Invalid arguments!\n");
	printf("Try: ./philo 2 200 100 100 || ./philo 2 300 100 100 2\n");
	return (0);
}

int	invalid_values(void)
{
	printf("Invalid values!\nOnly numbers above 0 are allowed.\n");
	return (0);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->global->print);
	pthread_mutex_lock(&data->global->finish);
	while (++i < data->global->guests)
	{
		pthread_mutex_lock(&data->global->m_forks[i]);
		pthread_mutex_lock(&data->global->meal_access[i]);
	}
	i = -1;
	pthread_mutex_unlock(&data->global->print);
	pthread_mutex_unlock(&data->global->finish);
	while (++i < data->global->guests)
	{
		pthread_mutex_unlock(&data->global->m_forks[i]);
		pthread_mutex_unlock(&data->global->meal_access[i]);
	}
	i = -1;
	pthread_mutex_destroy(&data->global->print);
	pthread_mutex_destroy(&data->global->finish);
	while (++i < data->global->guests)
	{
		pthread_mutex_destroy(&data->global->m_forks[i]);
		pthread_mutex_destroy(&data->global->meal_access[i]);
	}
	printf("mutexes destroyeds\n");
}

void	free_all(t_philo *philos, t_data *data)
{
	if (philos->threads)
		free(philos->threads);
	if (philos->data)
		free(philos->data);
	if (data->global->m_forks)
		free(data->global->m_forks);
	if (data->global->forks)
		free(data->global->forks);
	if (data->global->meal_access)
		free(data->global->meal_access);
	if (data->global->lst_meal)
		free(data->global->lst_meal);
	if (data->global->meals)
		free(data->global->meals);
}

void	print_status(t_data *data, char type, int id)
{
	pthread_mutex_lock(&data->global->print);
	pthread_mutex_lock(&data->global->finish);
	if (!data->global->end)
	{
		if (type == 't')
			printf("%lims: %i is thinking\n", get_current_time(), id);
		else if (type == 'f')
			printf("%lims: %i has taken a fork\n", get_current_time(), id);
		else if (type == 'e')
			printf("%lims: %i is eating\n", get_current_time(), id);
		else if (type == 's')
			printf("%lims: %i is sleeping\n", get_current_time(), id);
		else if (type == 'd')
			printf("%lims: %i died\n", get_current_time(), id);
	}
	pthread_mutex_unlock(&data->global->finish);
	pthread_mutex_unlock(&data->global->print);
}
