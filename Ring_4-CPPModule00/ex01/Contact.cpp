/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:31:17 by atang             #+#    #+#             */
/*   Updated: 2024/08/02 15:30:55 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

/*
	Constructor for the Contact class which initialises all member variables to 
	empty strings
*/

Contact::Contact() : first_name(""), last_name(""), nickname(""), phone_number(""), darkest_secret("") {}

/*
	Bool which returns true if any of the contact fields are empty, otherwise false
*/

bool	Contact::isEmpty() const
{
	return first_name.empty() || last_name.empty() || nickname.empty() || phone_number.empty() || darkest_secret.empty();
}

/*
	Returns the information stored in the specified field for the Contact 
*/

std::string Contact::getInfo(const std::string& field) const
{
    if (field == "first_name")
        return first_name;
    else if (field == "last_name")
        return last_name;
    else if (field == "nickname")
        return nickname;
    else if (field == "phone_number")
        return phone_number;
    else if (field == "darkest_secret")
        return darkest_secret;
    else
        return "Invalid field";
}

/*
	Displays contact information about the contact
*/

void Contact::displayInfo() const
{
    std::cout << Y "First Name: " RST << first_name << "\n";
    std::cout << Y "Last Name: " RST << last_name << "\n";
    std::cout << Y "Nickname: " RST << nickname << "\n";
    std::cout << Y "Phone Number: " RST << phone_number << "\n";
    std::cout << Y "Darkest Secret: " RST << darkest_secret << "\n";
}

/*
	Sets contact information (first name, last name, nickname, phone number, and darkest secret)
	by prompting the user to enter using standard inputfor each field
*/

void Contact::setInfo()
{
	std::cout << std::endl;
    std::cout << "Enter first name: ";
    std::getline(std::cin, first_name);
    std::cout << "Enter last name: ";
    std::getline(std::cin, last_name);
    std::cout << "Enter nickname: ";
    std::getline(std::cin, nickname);
    std::cout << "Enter phone number: ";
    std::getline(std::cin, phone_number);
    std::cout << "Enter darkest secret: ";
    std::getline(std::cin, darkest_secret);
}
