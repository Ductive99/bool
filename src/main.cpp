/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:25:21 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/29 13:20:09 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

static void print_banner(const std::string &txt);

int main(void) {
	std::vector<TestCase> interactive_test_funcs = {
		REGISTER_FUNC(test_eval_formula), REGISTER_FUNC(test_print_truth_table),
		REGISTER_FUNC(test_negation_normal_form)};

	// Non-interactive tests
	print_banner("test_adder");
	test_adder();
	print_banner("test_multiplier");
	test_multiplier();
	print_banner("test_gray_code");
	test_gray_code();

	for (const auto &t : interactive_test_funcs) {
		std::string mode;
		print_banner(t.name);
		std::cout << "Enter interactive mode ? (y/n) ";
		std::cin >> mode;
		std::cin.ignore();

		if (std::cin.eof())
			return (0);
		if (mode == "n")
			t.func(NORMAL_MODE);
		else
			t.func(INTERACTIVE_MODE);
		std::cin.clear();
	}

	return (0);
}

static void print_banner(const std::string &txt) {
	int l = std::max(0, (80 - (int)txt.length()) / 2);
	int r = std::max(0, 80 - (int)txt.length() - l);
	std::cout << std::string(l, '=') << " " << txt << " " << std::string(r, '=')
			  << std::endl;
}
