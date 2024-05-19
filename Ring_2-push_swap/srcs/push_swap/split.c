/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sentry <sentry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:38:21 by sentry            #+#    #+#             */
/*   Updated: 2024/02/21 14:10:11 by sentry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_words(char const *s, char c)
{
	int	count;
	int	in_word_flag;

	count = 0;
	in_word_flag = 0;
	while (*s)
	{
		if (*s == c)
			in_word_flag = 0;
		else if (in_word_flag == 0)
		{
			in_word_flag = 1;
			count++;
		}
		s++;
	}
	return (count);
}

char	*extract_word(char const **s, char c)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = 0;
	while (**s && **s == c)
		(*s)++;
	while ((*s)[word_len] && (*s)[word_len] != c)
		word_len++;
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		word[i] = (*s)[i];
		i++;
	}
	word[word_len] = '\0';
	*s += word_len;
	return (word);
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = extract_word(&s, c);
		if (!result[i])
		{
			free_words(result);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
