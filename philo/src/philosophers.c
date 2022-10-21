/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/21 01:28:26 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*routine(void *philo)
{
	t_philo		*temp;
	pthread_t	killer;
	t_data		data;
	int			pos;

	temp = philo;
	data = temp->data_control;
	pos = data.pos;
	data.last_meal[pos] = get_current_time(&data); //primeira refeicao, ja entra alimentado
	printf("philo %i first meal %li\n", data.pos, data.last_meal[pos]);	
	while(42)
	{
		if (pthread_create(&killer, NULL, &lifetime, &data) != 0)
			write(2, "Error2\n", 7);
		printf("Philo %i is thinking\n", data.pos);
		if (pos == data.guests) //ultimo filosofo
		{
			pthread_mutex_lock(&data.forks[0]); //garfo a direita do ultimo filosofo eh o garfo do primeiro, e tambem deve rodar primeiro pra ficar na fila e evitar deadlock
			printf("Philo %i has taken right fork\n", data.pos);
			pthread_mutex_lock(&data.forks[pos - 1]);
			printf("Philo %i has taken left fork\n", data.pos);
		}
		else
		{
			pthread_mutex_lock(&data.forks[pos - 1]);
			printf("Philo %i has taken left fork\n", data.pos);
			pthread_mutex_lock(&data.forks[pos]); //garfo a direita do filosofo
			printf("Philo %i has taken right fork\n", data.pos);
		}

		usleep(data.time_to_eat); //tempo para comer
		printf("Philo %i is eating\n", data.pos);
		data.last_meal[pos] = get_current_time(&data); //n precisa de mutex pois nao eh compartilhado com threads
		printf("Philo %i launched at: %li\n", data.pos, data.last_meal[pos]);
		pthread_mutex_unlock(&data.forks[pos - 1]); //libera o garfo a esquerda
		
		printf("Left Fork from %i returned\n", data.pos);
		if (pos == data.guests)
		{
			pthread_mutex_unlock(&data.forks[0]); //libera o garfo a direita
			printf("Right Fork from %i returned\n", data.pos);
		}
		else
		{
			pthread_mutex_unlock(&data.forks[pos]); //libera o garfo a direita
			printf("Right Fork from %i returned\n", data.pos);
		}
		printf("Philo %i is sleeping\n", data.pos);
	}
	return (0);
}

int main(int argc, char **argv)
{
	//number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, number_of_times_each_philosophers_must_eat
	t_philo			*philo;
	t_data			data;
	int				i;
	
	if (argc < 2)
		perror("Error\n");

	data.guests = ft_atoi(argv[1]);
	data.time_to_eat = ft_atoi(argv[2]) * 1000;
	data.forks = malloc(sizeof(pthread_mutex_t) * data.guests);
	data.last_meal = malloc(sizeof(long int) * data.guests);
	data.last_meal = memset(data.last_meal, 0, sizeof(long int) * data.guests);
	
	philo = NULL;
	philo = malloc(sizeof(t_philo) * data.guests);

	data.pos = 1;	
	i = -1;

	while(++i < data.guests)
		pthread_mutex_init(&data.forks[i], NULL);
	
	i = -1;
	while(++i < data.guests)
	{
		philo[i].data_control = data;
		if (pthread_create(&philo[i].philo_th, NULL, &routine, &philo[i]) != 0) //injeta ID da thread no 1o param
			write(2, "Error1\n", 7);
		data.pos++;
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
