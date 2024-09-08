/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:09:20 by lucas             #+#    #+#             */
/*   Updated: 2024/09/08 18:11:21 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// SPINLOCK 

void   sync_threads(t_data *data)
{
    while (!get_b(&data->variable_mtx, &data->trheads_sync))
        ;
}