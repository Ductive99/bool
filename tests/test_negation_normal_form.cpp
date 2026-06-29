/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_negation_normal_form.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:45:56 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/29 13:20:35 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

static void compare_truth_table_rpn_nnf(std::string s, int mode = NORMAL_MODE);

void test_negation_normal_form(int mode) {
	if (mode == NORMAL_MODE) {
		compare_truth_table_rpn_nnf("AB&!");
		compare_truth_table_rpn_nnf("AB=");
		compare_truth_table_rpn_nnf("AB|C=!D>");
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
			compare_truth_table_rpn_nnf(s, INTERACTIVE_MODE);
		}
	}
}

static void compare_truth_table_rpn_nnf(std::string s, int mode) {
	std::string nnf;
	try {
		nnf = negation_normal_form(s);
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		if (mode == INTERACTIVE_MODE)
			std::cout << "p.s. enter 'n' to quit\n";
		return;
	}
	std::cout << s << std::endl;
	print_truth_table(s);
	std::cout << std::endl;
	std::cout << nnf << std::endl;
	print_truth_table(nnf);
}
