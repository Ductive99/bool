/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gray_code.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:38:51 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/28 20:39:48 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

static void print_diff(u32 n, u32 n_gray_code);

void test_gray_code(void) {
	print_diff(0, 0);
	print_diff(1, 1);
	print_diff(2, 3);
	print_diff(3, 2);
	print_diff(4, 6);
	print_diff(5, 7);
	print_diff(6, 5);
	print_diff(7, 4);
	print_diff(8, 12);
}

static void print_diff(u32 n, u32 n_gray_code) {
	u32 res;

	res = gray_code(n);
	std::cout << "> " << n << " G() => " << res << " == " << n_gray_code
			  << "?\n";
	if (res == n_gray_code)
		std::cout << "OK\n";
	else
		std::cout << "FAIL\n";
}
