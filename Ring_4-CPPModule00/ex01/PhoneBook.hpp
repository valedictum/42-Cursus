/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atang <atang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:33:14 by atang             #+#    #+#             */
/*   Updated: 2024/08/02 16:10:06 by atang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHONEBOOK_HPP
#define	PHONEBOOK_HPP

#include "Contact.hpp"
#include <string> // For std::string class
#include <iostream>
#include <iomanip> // For manipulation of output formatting
#include <cstdlib> // For ::atoi()

#define MAX_CONTACTS 8

# define RST    "\033[0m"      /* Reset to default color */
# define RED    "\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

class PhoneBook
{
    public:
        PhoneBook();
        void addContact();
        void searchContacts() const;
        void printMenu() const;
		void displaySummary() const;

    private:
        Contact contacts[MAX_CONTACTS];
        int contact_count;
        int oldest_index;

        std::string truncate(const std::string& str, size_t width) const;
        bool isNumeric(const std::string& str) const;
        void pressEnter() const;
};

#endif
