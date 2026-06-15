/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_evaluation.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:42:10 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/15 22:50:33 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

static void print_comparison(const std::string &formula, bool result);

bool eval_formula(const std::string &formula) {
	std::unique_ptr<ASTNode> root = build_ast(formula);

	auto leaf = [](const ASTNode &n) -> bool {
		if (n.type == NodeType::Const)
			return n.value;
		throw InvalidFormulaException();
	};

	auto apply_not = [](bool v) -> bool { return !v; };

	auto apply_bin = [](NodeType t, bool l, bool r) -> bool {
		switch (t) {
		case NodeType::And:
			return l & r;
		case NodeType::Or:
			return l | r;
		case NodeType::Xor:
			return l ^ r;
		case NodeType::Implies:
			return (!l) | r;
		case NodeType::Iff:
			return l == r;
		default:
			throw InvalidFormulaException();
		}
	};

	return evaluate<bool>(root.get(), leaf, apply_not, apply_bin);
}

void test_eval_formula(void) {
	std::string answer;
	std::cout << "Enter interactive mode ? (y/n) ";
	std::cin >> answer;
	std::cin.ignore();

	if (answer == "n") {
		print_comparison("10&", false);
		print_comparison("10|", true);
		print_comparison("11>", true);
		print_comparison("10=", false);
		print_comparison("1011||=", true);
	} else {
		std::cout << "p.s. enter 'n' to quit\n";
		while (1) {
			try {
				std::string s;

				std::getline(std::cin, s);
				if (s == "n")
					break;
				bool result = eval_formula(s);
				std::cout << "> " << result << std::endl;
			} catch (const std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
	}
}

static void print_comparison(const std::string &formula, bool result) {
	bool out;

	out = eval_formula(formula);

	std::cout << "> " << formula << "-> " << out << " == " << result
			  << std::endl;
	if (out == result)
		std::cout << "OK\n";
	else
		std::cout << "FAIL\n";
}
