/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_powerset.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 20:28:19 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/08 21:05:32 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"
#include <limits>

static void print_powerset(const vector<vector<i32>> &ps);

void test_powerset(int mode) {
	if (mode == NORMAL_MODE) {
		vector<i32> set1 = {1, 2, 3};
		print_powerset(powerset(set1));
	} else {
		while (true) {
			i32 n;
			std::cout << "Number of elements: (or negative to quit) ";
			
			if (!(std::cin >> n)) {
                if (std::cin.eof()) return;
				std::cout << "Error: Invalid input. Please enter an integer.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
			if (n < 0)
				break;
			
			vector<i32> input_set(n);
			bool input_failed = false;
			std::cout << "Enter " << n << " integers: ";
			for (i32 i = 0; i < n; i++) {
				if (!(std::cin >> input_set[i])) {
                if (std::cin.eof()) return;
                    std::cout << "\nError: Invalid input detected at element " << (i + 1) << ".\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    input_failed = true;
                    break; 
                }
			}
			if (input_failed) continue;

			vector<vector<i32>> result = powerset(input_set);
			print_powerset(result);
		}
	}
}

static void print_powerset(const vector<vector<i32>> &ps) {
	std::cout << "[\n";
	for (const auto &subset : ps) {
		std::cout << "  [ ";
		for (i32 n : subset) {
			std::cout << n << " ";
		}
		std::cout << "]\n";
	}
	std::cout << "]\n";
}
