/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_evaluation.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:42:10 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/14 11:47:20 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "bool.h"
#include <exception>
#include <iostream>
#include <string>

static void print_comparison(const std::string &formula, bool result);

bool eval_formula(const std::string &formula) {
	std::stack<bool> operands;

	for (size_t i = 0; i < formula.size(); i++) {
		char c = formula[i];
		if (c == '0' || c == '1') {
			operands.push(c - '0');
		} else if (c == ' ') {
			std::cout << "s";
			continue;
		} else
			eval_operation(operands, c);
	}

	if (operands.size() != 1)
		throw TooManyOperandsException();

	return operands.top();
}

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
