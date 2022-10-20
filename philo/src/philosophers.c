/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/20 17:58:16 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*routine(void *philo)
{
	t_philo	*temp = philo;
	int		pos = temp->pos;

	while(42)
	{
		printf("Philo %i is thinking\n", temp->pos);
		if (pos == temp->guests) //ultimo filosofo
		{
			pthread_mutex_lock(&temp->forks[0]); //garfo a direita do ultimo filosofo eh o garfo do primeiro, e tambem deve rodar primeiro pra ficar na fila e evitar deadlock
			printf("Philo %i has taken right fork\n", temp->pos);
			pthread_mutex_lock(&temp->forks[pos - 1]);
			printf("Philo %i has taken left fork\n", temp->pos);
		}
		else
		{
			pthread_mutex_lock(&temp->forks[pos - 1]);
			printf("Philo %i has taken left fork\n", temp->pos);
			pthread_mutex_lock(&temp->forks[pos]); //garfo a direita do filosofo
			printf("Philo %i has taken right fork\n", temp->pos);
		}
		// usleep(temp->time_to_eat); //tempo para comer
		usleep(50); //tempo para comer
		printf("Philo %i is eating\n", temp->pos);
		pthread_mutex_unlock(&temp->forks[pos - 1]); //libera o garfo a esquerda
		printf("Left Fork from %i returned\n", temp->pos);
		if (pos == temp->guests)
		{
			pthread_mutex_unlock(&temp->forks[0]); //libera o garfo a direita
			printf("Right Fork from %i returned\n", temp->pos);
		}
		else
		{
			pthread_mutex_unlock(&temp->forks[pos]); //libera o garfo a direita
			printf("Right Fork from %i returned\n", temp->pos);
		}
		printf("Philo %i is sleeping\n", temp->pos);
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
	philo = NULL;
	philo = malloc(sizeof(t_philo) * data.guests);
	if (!philo)
	{
		free(philo);
		return (0);
	}
	printf("Quantia de filosofos: %i\n", data.guests);

	data.forks = malloc(sizeof(pthread_mutex_t) * data.guests);
	if (!data.forks)
	{
		free(philo);
		return (0);
	}
	printf("Quantia de garfos: %i\n", data.guests);

	data.pos = 1;	
	i = 0;
	//criar array de status hungry e popular com -1, depois checar de acordo com a posicao do philo,
	//se o anterior e o proximo nao estao comendo, se nao estiverem, o thread edita com mutex o status no array de inteiros
	//que ele esta comendo..

	while(i < data.guests)
		pthread_mutex_init(&data.forks[i++], NULL);
	
	i = 0;
	while(i < data.guests)
	{
		if (pthread_create(&philo[i].philo_th, NULL, &routine, &philo[i]) != 0) //injeta ID da thread no 1o param
			write(2, "Error1\n", 7);
		philo[i].pos = data.pos;
		philo[i].forks = data.forks;
		philo[i].guests = data.guests;
		data.pos++;
		i++;
	}

	i = 0;
	while(i < data.guests)
	{
		if (pthread_join(philo[i].philo_th, NULL) != 0)
			write(2, "Error2\n", 7);
		i++;
	}
	
	i = 0;
	while(i < data.guests)
		pthread_mutex_destroy(&data.forks[i++]);
	
	return (0);
}
