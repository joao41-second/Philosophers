/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpect <jperpect@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:11 by jperpect          #+#    #+#             */
/*   Updated: 2024/08/20 10:13:08 by jperpect         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../philosophers.h"

typedef struct {
    int contador;
    pthread_mutex_t mutex;
} ThreadData;


void *therd(void * struc)
{
	ThreadData *mute = (ThreadData *)struc;
	
	 if (pthread_mutex_trylock(&(mute->mutex)) == 0) {
            // Se o mutex foi adquirido com sucesso
        	// Seção crítica
			printf("ja tenho grafo\n");
			
            pthread_mutex_unlock(&(mute->mutex)); // Libera o mutex
        } else 
		{
            // Se o mutex não está disponível
            printf("Mutex não disponível, tentando novamente...\n");
        }
	return("ola");
}

void filof()
{

	ThreadData data;

	
	pthread_t p1, p2;

	pthread_mutex_init(&(data.mutex),NULL);

	pthread_create(&p1,NULL,therd,&data);
	pthread_create(&p2,NULL,therd,&data);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	
}
