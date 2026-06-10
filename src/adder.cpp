/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:19:53 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/10 17:00:20 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

u32 adder(u32 a, u32 b) {
	u32 result = 0;
	u32 a_bit;
	u32 b_bit;
	u32 carry;

	carry = 0;
	for (int i = 0; i < 32; i++) {
		if (a >> i == 0 && b >> i == 0 && carry == 0)
			break;
		a_bit	  = 1 & (a >> i);
		b_bit	  = 1 & (b >> i);
		u32 sum	  = a_bit ^ b_bit;
		u32 c_out = a_bit & b_bit;

		result |= ((sum ^ carry) << i);
		carry = c_out | (carry & sum);
	}

	return result;
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
