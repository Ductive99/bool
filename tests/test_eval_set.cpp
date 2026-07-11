/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_eval_set.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 09:20:07 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/11 14:20:02 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"
#include <limits>
#include <sstream>

static void print_eval_set(const std::string   &formula,
						   vector<vector<i32>> &sets);

void test_eval_set(int mode) {
	if (mode == NORMAL_MODE) {
		vector<i32>			a		= {1, 2, 3};
		vector<i32>			b		= {0, 3, 4};
		vector<vector<i32>> a_and_b = {a, b};
		print_eval_set("AB&", a_and_b);
		print_eval_set("AB|", a_and_b);
		print_eval_set("A!", a_and_b);
	} else {
		while (true) {
			vector<vector<i32>> sets;

			std::string line;
			std::cin.ignore();

			std::cout << "Enter sets, one per line, blank line to finish:\n";
			while (true) {
				std::cout << "Set " << sets.size() + 1 << ": ";
				std::getline(std::cin, line);
				if (line.empty())
					break;

				std::istringstream iss(line);
				vector<i32>		   input_set;
				i32				   n;
				while (iss >> n)
					input_set.push_back(n);

				sets.push_back(input_set);
			}
			std::string s;
			std::cout << "Enter formula: ";
			if (!(std::cin >> s)) {
				if (std::cin.eof())
					return;
				std::cin.clear();
				return;
			}
			if (s == "n")
				break;
			print_eval_set(s, sets);
		}
	}
}

static void print_eval_set(const std::string   &formula,
						   vector<vector<i32>> &sets) {
	vector<i32> result;

	try {
		result = eval_set(formula, sets);
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		return;
	}

	std::cout << "sets:\n[\n";
	for (const auto &set : sets) {
		std::cout << "\t[ ";
		for (const auto &n : set)
			std::cout << n << " ";
		std::cout << "]\n";
	}
	std::cout << "]\n";

	std::cout << "> " << formula << std::endl;
	std::cout << "[ ";
	for (const auto &n : result)
		std::cout << n << " ";
	std::cout << "]\n";
}
