/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_multiplier.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:37:11 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/28 20:38:36 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

static void print_comparison(u32 a, u32 b);

void test_multiplier(void) {
	print_comparison(1, 1);
	print_comparison(99, 11);
	print_comparison(210389712, 213199213);
	print_comparison(1000, 10000);
	print_comparison(6456, 123);
	print_comparison(0, 1123456789);
}

static void print_comparison(u32 a, u32 b) {
	u32 mul	   = a * b;
	u32 my_mul = multiplier(a, b);

	std::cout << "> " << a << " * " << b << " => " << mul << " == " << my_mul
			  << "?\n";
	if (mul == my_mul)
		std::cout << "OK\n";
	else
		std::cout << "FALSE\n";
}
