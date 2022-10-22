/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/22 12:12:35 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*routine(void *philo)
{
	t_philo		*temp;
	t_data		data;

	temp = philo;
	data = temp->data_control;
	
	while(42)
	{
		printf("%lims: %i is thinking\n", get_current_time(&data), data.pos);
		if (data.pos == data.guests) //ultimo filosofo
		{
			pthread_mutex_lock(&data.forks[0]); //garfo a direita do ultimo filosofo eh o garfo do primeiro, e tambem deve rodar primeiro pra ficar na fila e evitar deadlock
			printf("%lims: %i has taken a fork\n", get_current_time(&data), data.pos);
			pthread_mutex_lock(&data.forks[data.pos - 1]);
			printf("%lims: %i has taken a fork\n", get_current_time(&data), data.pos);
		}
		else
		{
			pthread_mutex_lock(&data.forks[data.pos - 1]);
			printf("%lims: %i has taken a fork\n", get_current_time(&data), data.pos);
			pthread_mutex_lock(&data.forks[data.pos]); //garfo a direita do filosofo
			printf("%lims: %i has taken a fork\n", get_current_time(&data), data.pos);
		}

		usleep(data.time_to_eat); //tempo para comer
		printf("%lims: %i is eating\n", get_current_time(&data), data.pos);
		
		pthread_mutex_lock(&data.meal_access[data.pos - 1]);
		data.last_meal[data.pos - 1] = get_current_time(&data); //n precisa de mutex pois nao eh compartilhado com threads
		pthread_mutex_unlock(&data.meal_access[data.pos - 1]);
		
		pthread_mutex_unlock(&data.forks[data.pos - 1]); //libera o garfo a esquerda
		
		if (data.pos == data.guests)
			pthread_mutex_unlock(&data.forks[0]); //libera o garfo a direita
		else
			pthread_mutex_unlock(&data.forks[data.pos]); //libera o garfo a direita
		printf("%lims: %i is sleeping\n", get_current_time(&data), data.pos);
	}
	return (0);
}

int main(int argc, char **argv)
{
	//number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, number_of_times_each_philosophers_must_eat
	t_philo			*philo;
	pthread_t		killer;
	t_data			data;
	int				i;
	
	if (argc < 2)
		perror("Error\n");
	data.guests = ft_atoi(argv[1]);
	data.time_to_eat = ft_atoi(argv[2]);
	data.forks = malloc(sizeof(pthread_mutex_t) * data.guests);
	data.meal_access = malloc(sizeof(pthread_mutex_t) * data.guests);
	data.last_meal = malloc(sizeof(long int) * data.guests);
	data.last_meal = memset(data.last_meal, 0, sizeof(long int) * data.guests);
	data.pos = 0;	

	if (pthread_create(&killer, NULL, &lifetime, &data) != 0)
		write(2, "Error2\n", 7);

	philo = NULL;
	philo = malloc(sizeof(t_philo) * data.guests);
	
	i = -1;
	while(++i < data.guests)
		pthread_mutex_init(&data.forks[i], NULL);

	i = -1;
	while(++i < data.guests)
	{
		data.pos++;
		philo[i].data_control = data;
		if (pthread_create(&philo[i].philo_th, NULL, &routine, &philo[i]) != 0) //injeta ID da thread no 1o param
			write(2, "Error1\n", 7);
	}

	i = -1;
	while(++i < data.guests)
		if (pthread_join(philo[i].philo_th, NULL) != 0)
			write(2, "Error2\n", 7);
	
	i = -1;
	while(++i < data.guests)
		pthread_mutex_destroy(&data.forks[i]);
	
	return (0);
}
