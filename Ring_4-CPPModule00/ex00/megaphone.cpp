/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:37:14 by atang             #+#    #+#             */
/*   Updated: 2024/07/06 17:50:25 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream> // std::cout
#include <cctype> // std::toupper

/*

	- cast to unsigned char to properly handle character values 
	before passing it to std::toupper (C++ type-safe) (unlike the C-style 
	toupper() which doesn't handle negatives or values outside the standard 
	ASCII range properly)

*/

int main (int argc, char **argv)
{
	int i;
	int j;

	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		for (i = 1; i < argc; ++i)
		{
			j = 0;
			while (argv[i][j] != '\0')
			{
				std::cout << (char)std::toupper((unsigned char)argv[i][j]); 
				j++;
			}
			std::cout << " ";
		}
	}
	std::cout << std::endl; // new line
	return (0);
}