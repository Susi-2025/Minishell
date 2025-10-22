/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:55:28 by vinguyen          #+#    #+#             */
/*   Updated: 2025/10/22 14:17:47 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "minishell.h"
# include "structs.h"
# include <stdbool.h>
# include <stddef.h>

/***** DEFINITIONS *****/

# define VECTOR_MINIMUM_CAPACITY 2
# define VECTOR_GROWTH_FACTOR 2
# define VECTOR_SHRINK_THRESHOLD (1 / 4)
# define VECTOR_ERROR -1
# define VECTOR_SUCCESS 0
# define VECTOR_UNINITIALIZED NULL
# define VECTOR_INITIALIZER \
	{ 0, 0, 0, VECTOR_UNINITIALIZED }
# define MAX(a, b) ((a) > (b) ? (a) : (b))

int		vector_setup(t_vector *vector);
int		vector_push_back(t_vector *vector, char *element);
void	vector_destroy(t_vector *vector);
void	vector_destroy_heredocs(t_vector *vector);
#endif
