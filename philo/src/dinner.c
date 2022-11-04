/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:04:41 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/03 23:06:31 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*dinner(void *cast)
{
	t_data	*data;

	data = cast;
	pthread_mutex_lock(&data->global->meal_access[data->id]);
	data->lst_meal[data->id] = get_current_time();
	pthread_mutex_unlock(&data->global->meal_access[data->id]);
	while (42)
	{
		pthread_mutex_lock(&data->global->finish);
		if (data->global->end == 1)
		{
			printf("philo %i morreu enquanto pensava\n", data->id);
			return (NULL);
		}
		pthread_mutex_unlock(&data->global->finish);
		take_forks(data);
		if (!eat(data))
			return (0);
		return_forks(data);
		if (!sleep_time(data))
			return (0);
		print_status(data, 't', 0);
	}
	return (NULL);
}

void	take_forks(t_data *data)
{
	if (data->id + 1 == data->global->guests)
	{
		pthread_mutex_lock(&data->global->m_forks[0]);
		print_status(data, 'f', 0);
		pthread_mutex_lock(&data->global->m_forks[data->id]);
		print_status(data, 'f', 0);
	}
	else
	{
		pthread_mutex_lock(&data->global->m_forks[data->id]);
		print_status(data, 'f', 0);
		pthread_mutex_lock(&data->global->m_forks[data->id + 1]);
		print_status(data, 'f', 0);
	}
}

int	sleep_time(t_data *data)
{
	print_status(data, 's', 0);
	if (!smart_check(data->time_to_eat, data))
	{
		printf("philo %i parou pois alguem morreu\n", data->id);
		return (0);
	}
	return (1);
}

void	return_forks(t_data *data)
{
	pthread_mutex_unlock(&data->global->m_forks[data->id]);
	if (data->id + 1 == data->global->guests)
		pthread_mutex_unlock(&data->global->m_forks[0]);
	else
		pthread_mutex_unlock(&data->global->m_forks[data->id + 1]);
}

int	eat(t_data *data)
{
	print_status(data, 'e', 0);
	if (!smart_check(data->time_to_eat, data))
	{
		printf("philo %i parou pois alguem morreu\n", data->id);
		return (0);
	}
	pthread_mutex_lock(&data->global->meal_access[data->id]);
	data->lst_meal[data->id] = get_current_time();
	pthread_mutex_unlock(&data->global->meal_access[data->id]);
	if (data->times_must_eat)
	{
		pthread_mutex_lock(&data->global->meal_access[data->id]);
		data->meals[data->id]++;
		pthread_mutex_unlock(&data->global->meal_access[data->id]);
	}
	return (1);
}

int	smart_check(long int timer, t_data *data)
{
	long int end;
	end = get_current_time() + timer;
	while (end >= get_current_time())
	{
		pthread_mutex_lock(&data->global->finish);
		if (data->global->end)
		{
			printf("algum philo morreu\n");
			pthread_mutex_unlock(&data->global->finish);
			return (0);
		}
		pthread_mutex_unlock(&data->global->finish);
		usleep(100);
	}
	return (1);
}
