/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conjunctive_normal_form.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 12:48:36 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/05 20:12:02 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "bool.h"

std::string conjunctive_normal_form(const std::string &formula) {
	std::unique_ptr<ASTNode> root = build_ast(formula);
	std::string				 result;

	std::unique_ptr<ASTNode> nnf = transform_to_nnf(root.get());
	std::unique_ptr<ASTNode> cnf = transform_nnf_to_cnf(nnf.get());
	return to_rpn(cnf.get());
}

std::unique_ptr<ASTNode> distribute_or(std::unique_ptr<ASTNode> L,
									   std::unique_ptr<ASTNode> R) {
	if (L->type == NodeType::And) {
		auto left  = distribute_or(L->left->clone(), R->clone());
		auto right = distribute_or(L->right->clone(), R->clone());
		return make_and(std::move(left), std::move(right));
	}
	if (R->type == NodeType::And) {
		auto left  = distribute_or(L->clone(), R->left->clone());
		auto right = distribute_or(L->clone(), R->right->clone());
		return make_and(std::move(left), std::move(right));
	}
	return ASTNode::make_binary(NodeType::Or, std::move(L), std::move(R));
	return make_or(std::move(L), std::move(R));
}

std::unique_ptr<ASTNode> transform_nnf_to_cnf(const ASTNode *node) {
	if (!node)
		throw InvalidFormulaException();

	if (node->is_leaf() || node->type == NodeType::Not)
		return node->clone();

	if (node->type == NodeType::And) {
		auto left  = transform_nnf_to_cnf(node->left.get());
		auto right = transform_nnf_to_cnf(node->right.get());
		return make_and(std::move(left), std::move(right));
	}

	if (node->type == NodeType::Or) {
		auto left  = transform_nnf_to_cnf(node->left.get());
		auto right = transform_nnf_to_cnf(node->right.get());
		return distribute_or(std::move(left), std::move(right));
	}

	throw InvalidFormulaException();
}
