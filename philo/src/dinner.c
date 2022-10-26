/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:04:41 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/26 09:53:21 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*dinner(void *data)
{
	t_data	*cast;

	cast = data;
	cast->last_meal[cast->pos - 1] = get_current_time();
	while(42)
	{
		printf("%lims: %i is thinking\n", get_current_time(), cast->pos);
		take_forks(cast);
		eat(cast);
		return_forks(cast);
		sleep_time(cast);
	}
	return (NULL);
}

void	take_forks(t_data *data)
{
	if (data->pos == data->guests) //ultimo filosofo
	{
		pthread_mutex_lock(&data->forks[0]); //garfo a direita do ultimo filosofo eh o garfo do primeiro, e tambem deve rodar primeiro pra ficar na fila e evitar deadlock
		printf("%lims: %i has taken a fork\n", get_current_time(), data->pos);
		pthread_mutex_lock(&data->forks[data->pos - 1]);
		printf("%lims: %i has taken a fork\n", get_current_time(), data->pos);
	}
	else
	{
		pthread_mutex_lock(&data->forks[data->pos - 1]);
		printf("%lims: %i has taken a fork\n", get_current_time(), data->pos);
		pthread_mutex_lock(&data->forks[data->pos]); //garfo a direita do filosofo
		printf("%lims: %i has taken a fork\n", get_current_time(), data->pos);
	}
}

void	sleep_time(t_data *data)
{
	printf("%lims: %i is sleeping\n", get_current_time(), data->pos);
	usleep(data->time_to_sleep * 1000);
}

void	return_forks(t_data *data)
{
	pthread_mutex_unlock(&data->forks[data->pos - 1]); //libera o garfo a esquerda
	if (data->pos == data->guests)
		pthread_mutex_unlock(&data->forks[0]); //libera o garfo do primeiro
	else
		pthread_mutex_unlock(&data->forks[data->pos]); //libera o garfo a direita
}

void	eat(t_data *data)
{
	printf("%lims: %i is eating\n", get_current_time(), data->pos);
	pthread_mutex_lock(&data->meal_access[data->pos - 1]);
	data->last_meal[data->pos - 1] = get_current_time(); //mutex p/ evitar content race c/ funcao lifetime
	pthread_mutex_unlock(&data->meal_access[data->pos - 1]);
	usleep(data->time_to_eat * 1000); //tempo para comer
	if (data->times_must_eat)
		data->meals_eaten[data->pos - 1]++;
}
