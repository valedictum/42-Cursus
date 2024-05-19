/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:58:29 by sentry            #+#    #+#             */
/*   Updated: 2024/02/11 14:08:37 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_rank(t_stack_node *stack)
{
	t_stack_node	*current;
	t_stack_node	*temp;
	int				rank;
	int				current_value;

	current = stack;
	rank = 1;
	while (current != NULL)
	{
		temp = stack;
		current_value = current->value;
		while (temp != NULL)
		{
			if (temp->value < current_value)
			{
				rank++;
			}
			temp = temp->next;
		}
		current->rank = rank;
		rank = 1;
		current = current->next;
	}
}

t_stack_node	*find_rank(t_stack_node **stack, int target_rank)
{
	t_stack_node	*current;

	current = *stack;
	while (current != NULL)
	{
		if (current->rank == target_rank)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

int	stack_size(t_stack_node	*stack)
{
	size_t	stack_size;

	stack_size = 0;
	while (stack)
	{
		stack = stack->next;
		stack_size++;
	}
	return (stack_size);
}
