/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print_truth_table.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:43:04 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/29 13:21:03 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

void test_print_truth_table(int mode) {
	if (mode == NORMAL_MODE) {
		std::string s = "AB&C|";
		std::cout << s << std::endl;
		print_truth_table(s);
		std::cout << std::endl;
		s = "AB>C&!";
		std::cout << s << std::endl;
		print_truth_table(s);
	} else {
		std::cout << "p.s. enter 'n' to quit\n";
		while (1) {
			try {
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
				print_truth_table(s);
			} catch (const std::exception &e) {
				std::cout << e.what() << std::endl;
				std::cout << "p.s. enter 'n' to quit\n";
			}
		}
	}
}
