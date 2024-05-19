/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:38:12 by atang             #+#    #+#             */
/*   Updated: 2024/02/23 12:44:39 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	chunk_sort_3(t_stack_node **stack_a, t_stack_node **stack_b,
			int *operation_count, int max_rank)
{
	t_stack_node	*current;
	t_chunk_node	*chunk_head;
	t_chunk_node	*chunk_tail;
	int				i;

	i = 0;
	while (i < 3)
	{
		current = *stack_a;
		set_chunk_null(&chunk_head, &chunk_tail);
		while (current != NULL && !is_sorted(*stack_a))
		{
			if (is_in_range(current->rank, i, max_rank))
				add_to_chunk(&chunk_head, &chunk_tail, current);
			current = current->next;
		}
		if (chunk_head != NULL)
		{
			push_chunk_to_b(stack_a, stack_b, &chunk_head, operation_count);
			i++;
		}
		else
			return ;
	}
}

void	chunk_sort_500(t_stack_node **stack_a, t_stack_node **stack_b,
		int	*operation_count)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		process_chunk_500(stack_a, stack_b, operation_count, i);
		i++;
	}
}

void	insertion_sort(t_stack_node **stack_a, t_stack_node **stack_b,
			int *operation_count)
{
	t_stack_node	*target_element;
	int				max_rank;
	int				target_rank;

	max_rank = stack_size(*stack_b);
	target_rank = max_rank;
	while (*stack_b != NULL && target_rank >= 1)
	{
		target_element = find_rank(stack_b, target_rank);
		rotate_to_top_of_b(stack_b, target_element, operation_count);
		if (*stack_b != NULL)
		{
			pa(stack_a, stack_b, operation_count);
			update_positions(*stack_a);
			update_positions(*stack_b);
			target_rank--;
		}
	}
}
