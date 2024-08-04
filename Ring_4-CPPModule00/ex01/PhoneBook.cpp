/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:32:56 by atang             #+#    #+#             */
/*   Updated: 2024/08/02 16:11:04 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

/*
	Constructor for the PhoneBook class which initialises the oldest_index to 0
	and contact_count to 0
*/

PhoneBook::PhoneBook() : contact_count(0), oldest_index(0) {}

/*
	Displays message prompting user to press enter to return to the main menu
	and waits for enter to be pressed before continuing
*/

void PhoneBook::pressEnter() const
{
    std::cout << C "\nPress enter to return to the main menu..." RST << std::endl;
    std::cin.get();
}

/*
	Bool that checks if a given string is numeric (true if numeric, false otherwise)
	(for loop version)
*/

bool PhoneBook::isNumeric(const std::string& str) const 
{
    if (str.empty()) 
		return false;
    for (std::size_t i = 0; i < str.size(); ++i)
	{
        if (!std::isdigit(str[i])) 
			return false;
    }
    return true;
}

/*
	Prints main menu of the Phonebook program displaying options to ADD a contact, 
	SEARCH for a specific contact, or EXIT the program
*/

void PhoneBook::printMenu() const
{
	std::cout << std::endl;
	std::cout << "******************  "  B "Phonebook" RST"  ********************" << std::endl;
	std::cout << "**                                               **" << std::endl;
	std::cout << "**            " G "ADD" RST" - Add new contact              **" << std::endl;
	std::cout << "**      " Y "SEARCH" RST" - Display a specific contact      **" << std::endl;
	std::cout << "**           " RED "EXIT" RST" - Exit the program             **" << std::endl;
	std::cout << "**                                               **" << std::endl;
	std::cout << "***************************************************" << std::endl;
	std::cout << std::endl;
	std::cout << B << "               Welcome to Phonebook!" RST << std::endl;
	std::cout << "             What would you like to do:" << std::endl;
	std::cout << G << "               ADD" << RST << ", " << Y << "SEARCH" << RST << ", or " << RED << "EXIT" << RST << "?" << std::endl;
	std::cout << std::endl;
	std::cout << "> ";
}

/*
	Adds a new contact to the PhoneBook
  	- creates a new Contact object, sets its information, and adds it to the contacts array 
	(if all fields are filled)
 	- updates the oldest_index and contact_count accordingly
 	- displays success or failure messages based on the contact's completeness
	- prompt to press enter to return to the main menu
*/

void PhoneBook::addContact()
{
    Contact newContact;
    newContact.setInfo();

    if (!newContact.isEmpty())
    {
        contacts[oldest_index] = newContact;
        oldest_index = (oldest_index + 1) % MAX_CONTACTS;
        if (contact_count < MAX_CONTACTS)
            contact_count++;
        std::cout << G "\nContact successfully added to Phonebook!\n" RST;
    }
	else
		std::cout << RED "\nContact NOT added - entry required for ALL fields\n" RST;
    pressEnter();
}

/*
	Searches and view contacts in the phone book
 	- if phone book is NOT empty, displays a summary of contacts and prompts the user to 
	enter an index to view a specific contact
	- if the index is valid, it displays the specified contact's information
 	- if the index is invalid (empty or outside range) or the input is not numeric, 
	appropriate error messages are shown
*/

void PhoneBook::searchContacts() const
{
    if (contact_count == 0)
    {
        std::cout << RED "\nPhonebook is empty!\n" RST;
        pressEnter();
        return;
    }

    displaySummary();  // Display the summary before asking for an index

    std::cout << Y "\nEnter the index of the contact you want to view: " RST;
    std::string input;
    std::getline(std::cin, input);

    if (isNumeric(input))
    {
        int index = std::atoi(input.c_str());
        if (index >= 0 && index < contact_count)
        {
            std::cout << B "\nContact Index: " << index << RST << std::endl;
            contacts[index].displayInfo();
        }
        else
        {
            std::cout << RED "\nInvalid index - empty or outside of range\n" RST;
        }
    }
    else
    {
        std::cout << RED "\nInvalid input\n" RST;
    }
    pressEnter();
}

/*
	Truncates a given string to a specified width (returns substring starting from index 0 to (width -1)) and adds "."
	OR returns original string without truncation if shorter than specified width
*/

std::string	PhoneBook::truncate(const	std::string &str, size_t width) const
{
	if (str.length() > width)
		return str.substr(0, width - 1) + ".";
	else
		return str;
}

/*
 	Displays a summary of the contacts in the phone book in a table form (index, first name, last name, 
	and nickname of each contact) either in complete form OR truncated form ending in "." (if > 10 characters) 
*/

void PhoneBook::displaySummary() const
{
    std::cout << "\n     " B" Index" RST "|" B "First Name" RST "|" B " Last Name" RST "|" B "  Nickname" RST "|\n";
    std::cout << "|----------|----------|----------|----------|\n" ;
    for (int i = 0; i < contact_count; ++i)
    {
        std::cout << "|" << std::setw(10) << i << "|"
                  << std::setw(10) << truncate(contacts[i].getInfo("first_name"), 10) << "|"
                  << std::setw(10) << truncate(contacts[i].getInfo("last_name"), 10) << "|"
                  << std::setw(10) << truncate(contacts[i].getInfo("nickname"), 10) << "|\n";
    }
    std::cout << "|----------|----------|----------|----------|\n";
}
