/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/10 23:43:06 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
void	*test()
{
	int value = 3;
	printf("Valor: %i\n", ++value);
	printf("Running\n");
	sleep(5);
	printf("Ending\n");
	return (0);
}

int main(void)
{
	pthread_t t1;
	pthread_t t2;

	if (pthread_create(&t1, NULL, &test, NULL) != 0) //criamos a thread, passamos ponteiro da variavel e a funcao p/ ser chamada
		write(2, "Error\n", 6);
	if (pthread_create(&t2, NULL, &test, NULL) != 0) //criamos a thread, passamos ponteiro da variavel e a funcao p/ ser chamada
		write(2, "Error\n", 6);
	if (pthread_join(t1, NULL) != 0) // basicamente um wait para threads, p/ processo n acabar antes da thread
		write(2, "Error\n", 6);
	if (pthread_join(t2, NULL) != 0) // basicamente um wait para threads, p/ processo n acabar antes da thread
		write(2, "Error\n", 6);
}
