/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_evaluation.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:42:10 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/28 20:41:30 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

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
