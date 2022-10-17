/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:08:40 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/17 15:08:52 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_philo
{
	int id;
	int	number_of_philo;
	pthread_t	*philo_th;
}				t_philo;

long int	ft_atoi(char *str);
int			check_atoi_numbers(char *string);

#endif
