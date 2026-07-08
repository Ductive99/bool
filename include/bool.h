/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:22:12 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/08 17:58:54 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOL_H_
#define BOOL_H_

#include "ast.h"
#include "tests.h"
#include <bitset>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <string>

#define i32 int32_t
#define u32 uint32_t

#define INTERACTIVE_MODE 1
#define NORMAL_MODE		 0

// Adds `a + b` using only bitwise ops (`&`, `|`, `^`, `<<`, `>>`).
u32 adder(u32 a, u32 b);
// Multiplies `a * b` using only bitwise ops.
u32 multiplier(u32 a, u32 b);
// Converts integer `n` to its Gray code equivalent.
u32 gray_code(u32 n);
// Evaluates a propositional formula in **Reverse Polish Notation**.
bool eval_formula(const std::string &formula);
// Prints the truth table for a formula with variables `A-Z`
void print_truth_table(const std::string &formula);
// Converts a propositional formula to its negation normal form
std::string negation_normal_form(const std::string &formula);
// Converts a propositional formula to its conjuctive normal form
std::string conjunctive_normal_form(const std::string &formula);
// Checks if there's a combination of true and false for which the formula
// evaluates to true
bool sat(const std::string &formula);

// Utility functions
std::unique_ptr<ASTNode> transform_to_nnf(const ASTNode *node);
std::unique_ptr<ASTNode> transform_nnf_to_cnf(const ASTNode *node);
void		collect_variables(const ASTNode *node, std::set<char> &vars);
std::string to_rpn(const ASTNode *node);
void		collect_variables(const ASTNode *node, std::set<char> &vars);
bool		eval_with_assignment(const ASTNode				*root,
								 const std::map<char, bool> &assignment);

#endif /* BOOL_H_ */
