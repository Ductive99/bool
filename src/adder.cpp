/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:19:53 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/28 20:35:17 by esouhail         ###   ########.fr       */
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
