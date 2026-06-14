/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 11:00:17 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/14 11:02:53 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "bool.h"

// RPN Operation Dispatcher

static const std::map<char, void(*)(std::stack<bool>&)> operations = {
    {'!', negation},
    {'&', conjunction},
    {'|', disjunction},
    {'^', exclusive_disjunction},
    {'>', material_condition},
    {'=', equivalence},
};

void eval_operation(std::stack<bool> &operands, const char op) {
    auto it = operations.find(op);
    if (it == operations.end())
        throw InvalidOperandException();
    it->second(operands);
}

// RPN Operations

void negation(std::stack<bool> &operands) {
	if (operands.size() < 1)
		throw InsufficientOperandsException();
	bool top = operands.top();
	operands.pop();
	operands.push(!top);
}

void conjunction(std::stack<bool> &operands) {
	if (operands.size() < 2)
		throw InsufficientOperandsException();
	bool result = operands.top();
	operands.pop();
	result &= operands.top();
	operands.pop();
	operands.push(result);
}

void disjunction(std::stack<bool> &operands) {
	if (operands.size() < 2)
		throw InsufficientOperandsException();
	bool result = operands.top();
	operands.pop();
	result |= operands.top();
	operands.pop();
	operands.push(result);
}

void exclusive_disjunction(std::stack<bool> &operands) {
	if (operands.size() < 2)
		throw InsufficientOperandsException();
	bool result = operands.top();
	operands.pop();
	result ^= operands.top();
	operands.pop();
	operands.push(result);
}

void material_condition(std::stack<bool> &operands) {
	if (operands.size() < 2)
		throw InsufficientOperandsException();
	bool p1, p2;
	// p1 => p2 is equilavent to not p1 or p2
	p2 = operands.top();
	operands.pop();
	p1 = operands.top();
	operands.pop();
	operands.push(!p1 | p2);
}

void equivalence(std::stack<bool> &operands) {
	if (operands.size() < 2)
		throw InsufficientOperandsException();
	bool p1, p2;
	p2 = operands.top();
	operands.pop();
	p1 = operands.top();
	operands.pop();
	operands.push(p1 == p2);
}
