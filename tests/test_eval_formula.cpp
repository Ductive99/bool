/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_eval_formula.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:40:12 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/28 20:42:52 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

static void print_comparison(const std::string &formula, bool result);

void test_eval_formula(void) {
	std::string answer;
	std::cout << "Enter interactive mode ? (y/n) ";
	std::cin >> answer;
	std::cin.ignore();

	if (answer == "n") {
		print_comparison("10&", false);
		print_comparison("10|", true);
		print_comparison("11>", true);
		print_comparison("10=", false);
		print_comparison("1011||=", true);
	} else {
		std::cout << "p.s. enter 'n' to quit\n";
		while (1) {
			try {
				std::string s;

				std::getline(std::cin, s);
				if (std::cin.eof())
				{
					std::cout << std::endl;
					return ;
				}
				if (s == "n")
					break;
				bool result = eval_formula(s);
				std::cout << "> " << result << std::endl;
			} catch (const std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
	}
}

static void print_comparison(const std::string &formula, bool result) {
	bool out;

	out = eval_formula(formula);

	std::cout << "> " << formula << "-> " << out << " == " << result
			  << std::endl;
	if (out == result)
		std::cout << "OK\n";
	else
		std::cout << "FAIL\n";
}
