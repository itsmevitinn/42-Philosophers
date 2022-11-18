/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:25:33 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/17 19:36:58 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

int	check_values(t_data *data)
{
	if (data->global->guests == 2147483650)
		return (invalid_args('v'));
	else if (data->time_to_die == 2147483650)
		return (invalid_args('v'));
	else if (data->time_to_eat == 2147483650)
		return (invalid_args('v'));
	else if (data->time_to_sleep == 2147483650)
		return (invalid_args('v'));
	else if (data->times_must_eat == 2147483650)
		return (invalid_args('v'));
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

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void		*ptr;
	size_t		delete;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	delete = count * size;
	ft_bzero(ptr, delete);
	return (ptr);
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
