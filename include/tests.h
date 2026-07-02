/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:31:55 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/02 13:43:30 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H_
#define TESTS_H_

#include <string>

#include <functional>
struct TestCase {
	std::string				 name;
	std::function<void(int)> func;
};

#define REGISTER_FUNC(func_name) {#func_name, func_name}

void test_adder();
void test_multiplier();
void test_gray_code();
void test_eval_formula(int mode);
void test_print_truth_table(int mode);
void test_negation_normal_form(int mode);
void test_conjunctive_normal_form(int mode);

#endif /* TESTS_H_ */
