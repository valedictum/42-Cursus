/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:01:39 by atang             #+#    #+#             */
/*   Updated: 2024/02/16 16:28:44 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max_rank(t_stack_node *stack)
{
	int	max_rank;

	if (!stack)
		return (-1);
	max_rank = stack->rank;
	while (stack)
	{
		if (stack->rank > max_rank)
			max_rank = stack->rank;
		stack = stack->next;
	}
	return (max_rank);
}

void	update_positions(t_stack_node *stack)
{
	t_stack_node	*current;
	int				position;

	current = stack;
	position = 1;
	while (current != NULL)
	{
		current->position = position;
		current = current->next;
		position++;
	}
}

void	rotate_to_top_of_a(t_stack_node **stack, t_stack_node *target,
			int	*operation_count)
{
	t_stack_node	*current;

	current = *stack;
	while (current != target)
	{
		if (target->position <= stack_size(*stack) / 2)
			ra(stack, operation_count);
		else
			rra(stack, operation_count);
		current = *stack;
	}
}

void	rotate_to_top_of_b(t_stack_node **stack, t_stack_node *target,
			int	*operation_count)
{
	t_stack_node	*current;

	current = *stack;
	while (current != target)
	{
		if (target->position <= stack_size(*stack) / 2)
			rb(stack, operation_count);
		else
			rrb(stack, operation_count);
		current = *stack;
	}
}
