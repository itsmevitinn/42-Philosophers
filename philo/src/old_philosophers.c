/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/20 17:35:14 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/old_philosophers.h"

long long int	value = 0;
pthread_mutex_t see_table;

void	*routine(void *philo)
{
	t_philo	*temp = philo; //vai castar pra int * e apontar pro msm valor na memoria dos threads
	int		pos = temp->pos;

	printf("Running\n");
	printf("pos do philo: %i\n", temp->pos);
	pthread_mutex_lock(&see_table);
	if (pos == temp->guests) //ultimo thread
	{
		while(temp->eating[pos - 1] == 1 || temp->eating[0] == 1)
			if (temp->eating[pos - 1] == 0 && temp->eating[0] == 0) // o previous do ultimo eh ele -1, e o proximo o primeiro pois eh lista circular
			{
				temp->eating[pos] = 1;
				printf("Philo %i is eating", temp->pos);
			}	
	}
	else
	{
		while(temp->eating[pos - 1] == 1 || temp->eating[pos] == 1)
			if (temp->eating[pos - 1] == 0 && temp->eating[pos] == 0) // de resto, sera sempre a posicao dele -1 pro previos e a pos dele msm eh a posicao correta no array
			{
				temp->eating[pos] = 1;
				printf("Philo %i is eating", temp->pos);
			}	
	}
	pthread_mutex_unlock(&see_table);
	usleep(temp->time_to_eat); //tempo para comer
	pthread_mutex_lock(&see_table); //iremos entrar em zona critica novamente, devolvemos o garfo e comecamos a pensar
	printf("Philo %i is sleeping", temp->pos);
	temp->eating[pos] = 0;
	pthread_mutex_unlock(&see_table);
	printf("Ending\n\n");
	return (0);
}

int main(int argc, char **argv)
{
	//number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, number_of_times_each_philosophers_must_eat
	t_philo			*philo;
	t_data			data;
	int			i;

	if (argc < 2)
		perror("Erru\n");

	// philo->time_to_eat = ft_atoi(argv[2]);
	data.guests = ft_atoi(argv[1]);
	printf("Quantia de filosofos: %i\n", data.guests);

	philo = NULL;
	philo = malloc(sizeof(t_philo) * data.guests);
	data.eating = malloc(sizeof(int) * data.guests);
	data.eating = memset(data.eating, 0, sizeof(int) * data.guests);
	
	data.pos = 1;	
	i = 0;
	//criar array de status hungry e popular com -1, depois checar de acordo com a posicao do philo,
	//se o anterior e o proximo nao estao comendo, se nao estiverem, o thread edita com mutex o status no array de inteiros
	//que ele esta comendo..

	if (!philo)
	{
		free(philo);
		return (0);
	}

	pthread_mutex_init(&see_table, NULL);
	
	i = 0;
	while(i < data.guests)
	{
		if (pthread_create(&philo[i].philo_th, NULL, &routine, &philo[i]) != 0) //injeta ID da thread no 1o param
			write(2, "Error1\n", 7);
		philo[i].pos = data.pos;
		philo[i].eating = data.eating;
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
	pthread_mutex_destroy(&see_table);
	
	return (0);
}
