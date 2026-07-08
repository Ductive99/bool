/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:57:30 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/08 18:15:39 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"


static void print_sat_result(const std::string s, int mode);

void test_sat(int mode) {
	if (mode == NORMAL_MODE) {
		print_sat_result("AB|", mode);
		print_sat_result("AB&", mode);
		print_sat_result("AA!&", mode);
		print_sat_result("AA^", mode);
	} else {
		std::cout << "p.s. enter 'n' to quit\n";
		while (1) {
			std::string s;

			std::cout << "> ";
			std::getline(std::cin, s);
			if (std::cin.eof()) {
				std::cout << std::endl;
				std::cin.clear();
				return;
			}
			if (s == "n")
				break;
			print_sat_result(s, mode);
		}
	}
}

static void print_sat_result(const std::string s, int mode)
{
	std::string result;

	try {
		result = sat(s) ? "true" : "false";
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		if (mode == INTERACTIVE_MODE)
			std::cout << "p.s. enter 'n' to quit\n";
		return;
	}
	std::cout << ">>>\n " << s << " \t >> " ;
	std::cout << result << std::endl;
}

