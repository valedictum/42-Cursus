/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:36:24 by atang             #+#    #+#             */
/*   Updated: 2024/08/02 19:07:19 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <cstdlib> // C++ version of stdlib.h for exit()

/*
	&str (reference to string object) as changes made to str parameter inside 
	fn will directly affect the original string passed to the fn (as opposed 
	to *str where changes made to *str would require dereferencing the pointer 
	to access and modify the original string object) i.e. operating on the 
	ORIGINAL std::string object without needing to return a new string 
*/

static void	makeUpper(std::string	&str) 
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		str[i] = std::toupper((unsigned char)str[i]);
	}
}

int main()
{
	PhoneBook	phoneBook; // Create an instance of PhoneBook

	while (true)
	{
		phoneBook.printMenu(); // Display menu options
		std::string command; // Declare string variable to store user command
		std::getline(std::cin, command); // Get user input from console
		makeUpper(command);
		if (command == "ADD")
		{
			phoneBook.addContact();
		}
		else if (command == "SEARCH")
		{
			phoneBook.searchContacts();
		}
		else if (command == "EXIT")
		{
			exit(0);
		}
		else
		{
			std::cout << std::endl;
			std::cout << RED "Invalid command entered!" RST << std::endl; 
			std::cout << "Please choose from: " G "ADD" RST "," Y " SEARCH" RST ", or " RED "EXIT" RST <<std::endl;
			std::cout << std::endl;
		}
	}
	return(0);
}
