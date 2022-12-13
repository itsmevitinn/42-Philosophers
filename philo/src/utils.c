/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:09:09 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/13 11:31:11 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	invalid_args(char type)
{
	if (type == 'q')
	{
		printf("Invalid arguments!\n");
		printf("Try: ./philo 2 200 100 100 || ./philo 2 300 100 100 2\n");
	}
	else if (type == 'v')
		printf("Invalid values!\nOnly numbers above 0 are allowed.\n");
	return (0);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->global->print);
	pthread_mutex_destroy(&data->global->finish);
	while (++i < data->global->guests)
	{
		pthread_mutex_destroy(&data->global->m_forks[i]);
		pthread_mutex_destroy(&data->global->meal_access[i]);
	}
}

void	free_data(t_data *data)
{
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

int	smart_usleep(long int timer, t_data *data)
{
	long int	start;
	long int	end;

	start = get_current_time();
	end = start + timer;
	while (end >= get_current_time())
	{
		pthread_mutex_lock(&data->global->finish);
		if (data->global->end)
		{
			pthread_mutex_unlock(&data->global->finish);
			return (0);
		}
		pthread_mutex_unlock(&data->global->finish);
		usleep(200);
	}
	return (1);
}
