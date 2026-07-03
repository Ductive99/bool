/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_conjunctive_normal_form.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:38:43 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/03 17:49:31 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

static void compare_truth_table_rpn(const std::string s, int mode = NORMAL_MODE);

void test_conjunctive_normal_form(int mode) {
	if (mode == NORMAL_MODE) {
		compare_truth_table_rpn("AB&!");
		compare_truth_table_rpn("AB|!");
		compare_truth_table_rpn("AB|C&");
		compare_truth_table_rpn("AB|C|D|");
		compare_truth_table_rpn("AB&C&D&");
		compare_truth_table_rpn("AB&!C!|");
		compare_truth_table_rpn("AB|!C!&");
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
			compare_truth_table_rpn(s, INTERACTIVE_MODE);
		}
	}
}

static void compare_truth_table_rpn(const std::string s, int mode) {
	std::string cnf;
	try {
		cnf = conjunctive_normal_form(s);
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		if (mode == INTERACTIVE_MODE)
			std::cout << "p.s. enter 'n' to quit\n";
		return;
	}
	std::cout << ">>>" << std::endl;
	std::cout << s << std::endl;
	print_truth_table(s);
	std::cout << std::endl;
	std::cout << cnf << std::endl;
	print_truth_table(cnf);
}
