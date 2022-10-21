/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:49:55 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/21 01:28:02 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*lifetime(void *data)
{
	t_data	*new_data;
	long long int	current_time;
	long long int	starving_time;
	int			pos;

	new_data = data;
	pos = new_data->pos;
	
	while(42)
	{
		current_time = get_current_time(new_data);
		printf("philo %i Last meal: %li\n", new_data->pos, new_data->last_meal[pos]);	
		printf("philo %i Current time: %lli\n", new_data->pos, current_time);
		starving_time = current_time - new_data->last_meal[pos];
		if (starving_time > new_data->time_to_eat)
		{
			printf("Philo %i died\n", new_data->pos);
			exit(EXIT_FAILURE);
		}
		printf("philo %i Difference %lli\n", new_data->pos, new_data->last_meal[pos] - current_time);
		return (NULL);
	}
}

long long int	get_current_time(t_data *data)
{
	long long int	sec_to_micro;

	data->time = malloc(sizeof(struct timeval));
	gettimeofday(data->time, NULL);
	sec_to_micro = data->time->tv_sec * 1000000;
	return (sec_to_micro + data->time->tv_usec);
}
