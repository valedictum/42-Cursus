/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:22:25 by atang             #+#    #+#             */
/*   Updated: 2024/02/21 13:58:21 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	choose_sort(t_stack_node **stack_a, t_stack_node **stack_b,
		int *operation_count, int num_elements)
{
	int	max_rank;

	if (num_elements == 2)
		sort_2(stack_a, operation_count);
	else if (num_elements == 3)
		sort_3(stack_a, operation_count);
	else if (num_elements == 5)
		sort_5(stack_a, stack_b, operation_count);
	else if (num_elements < 500)
	{
		max_rank = stack_size(*stack_a);
		chunk_sort_3(stack_a, stack_b, operation_count, max_rank);
		insertion_sort(stack_a, stack_b, operation_count);
	}
	else if (num_elements >= 500)
	{
		chunk_sort_500(stack_a, stack_b, operation_count);
		insertion_sort(stack_a, stack_b, operation_count);
	}
}

void	initialise_stacks(t_stack_node **stack_a, t_stack_node **stack_b)
{
	*stack_a = NULL;
	*stack_b = NULL;
}

void	free_stacks(t_stack_node *stack_a, t_stack_node *stack_b)
{
	free_stack(&stack_a);
	free_stack(&stack_b);
}

char	**split_arguments_or_exit(char *argument, char delimiter)
{
	char	**split_arguments;

	split_arguments = ft_split(argument, delimiter);
	if (split_arguments == NULL)
	{
		exit(1);
	}
	return (split_arguments);
}

int	main(int argc, char **argv)
{
	t_stack_node	*stack_a;
	t_stack_node	*stack_b;
	int				num_elements;
	int				operation_count;
	char			**split_arguments;

	initialise_stacks(&stack_a, &stack_b);
	num_elements = 0;
	operation_count = 0;
	if (argc < 2)
		exit (1);
	if (argc == 2)
	{
		split_arguments = split_arguments_or_exit(argv[1], ' ');
		parse_and_insert(&stack_a, split_arguments, &num_elements);
		free_split_arguments(split_arguments);
	}
	else
		parse_and_insert(&stack_a, &argv[1], &num_elements);
	check_stack_and_display_error(stack_a);
	stack_rank(stack_a);
	choose_sort(&stack_a, &stack_b, &operation_count, num_elements);
	free_stacks(stack_a, stack_b);
	return (0);
}
