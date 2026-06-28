/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_adder.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:30:11 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/28 20:36:36 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

void test_adder(void) {
	u32 result_adder, result_addition;

	result_adder = adder(0, 0), result_addition = 0 + 0;
	std::cout << "adder(0, 0) =                 " << result_adder
			  << " == " << result_addition << "? "
			  << (result_adder == result_addition) << std::endl;

	result_adder = adder(123, 23179), result_addition = 123 + 23179;
	std::cout << "adder(123, 23179) =           " << result_adder
			  << " == " << result_addition << "? "
			  << (result_adder == result_addition) << std::endl;

	result_adder = adder(1000000, 1010101), result_addition = 1000000 + 1010101;
	std::cout << "adder(1000000, 1010101) =     " << result_adder
			  << " == " << result_addition << "? "
			  << (result_adder == result_addition) << std::endl;

	result_adder	= adder(123456789, 987654321),
	result_addition = 123456789 + 987654321;
	std::cout << "adder(123456789, 987654321) = " << result_adder
			  << " == " << result_addition << "? "
			  << (result_adder == result_addition) << std::endl;

	result_adder = adder(19, 23), result_addition = 19 + 23;
	std::cout << "adder(19, 23) =               " << result_adder
			  << " == " << result_addition << "? "
			  << (result_adder == result_addition) << std::endl;
}
