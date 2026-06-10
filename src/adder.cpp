/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:19:53 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/10 18:23:37 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

u32 adder(u32 a, u32 b) {
	while (b != 0) {
		u32	carry = a & b;
		a	  = a ^ b;
		b	  = carry << 1;
	}
	return a;
}

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
