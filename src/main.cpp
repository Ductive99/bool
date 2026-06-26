/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:25:21 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/26 19:48:35 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"


// TODO: fix EOF input in interactive mode
int main(void) {
	std::cout << "\n===         Adder         ===\n";
	test_adder();
	std::cout << "\n===       Multiplier      ===\n";
	test_multiplier();
	std::cout << "\n===       Gray Code       ===\n";
	test_gray_code();
	std::cout << "\n===      Eval Formula     ===\n";
	test_eval_formula();
	std::cout << "\n===   Print Truth Table   ===\n";
	test_print_truth_table();
	std::cout << "\n===  Negation Normal Form ===\n";
	test_negation_normal_form();

	return (0);
}
