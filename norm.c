/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:31:18 by jperpect          #+#    #+#             */
/*   Updated: 2024/09/23 14:21:57 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*bar_men_thead(void *infs)
{
	s_new_fuck	*infus;
	s_new		*infus2;
	int			nb;
	int			i;

	infus = (s_new_fuck *)infs;
	nb = infus->philo;
	pthread_mutex_lock(&infus->mens);
	*infus->fuck->i_end = 2;
	pthread_mutex_unlock(&infus->mens);
	infus2 = (s_new *)infus->fuck;
	if (nb == 1)
	{
		nb++;
	}
	while (1)
	{
		i = -1;
		if (bar_run(infs, infus2, i, nb) == fasle)
		{
			break ;
		}
	}
	return ("oi");
}
