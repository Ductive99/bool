/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conjunctive_normal_form.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 12:48:36 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/02 20:14:47 by esouhail         ###   ########.fr       */
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

std::unique_ptr<ASTNode> transform_nnf_to_cnf(const ASTNode *node) {
	if (!node)
		throw InvalidFormulaException();

	if (arity(node->type) < 2)
		return node->clone();

	if (node->type == NodeType::Or) {
		const ASTNode *left_child  = node->left.get();
		const ASTNode *right_child = node->right.get();
		if (!left_child || !right_child)
			throw InvalidFormulaException();

		if (left_child->type == NodeType::And && arity(right_child->type) < 2) {
			auto new_node = make_and(
				make_or(left_child->left->clone(), right_child->clone()),
				make_or(left_child->right->clone(), right_child->clone()));
			return transform_nnf_to_cnf(new_node.get());
		}

		if (arity(left_child->type) < 2 && right_child->type == NodeType::And) {
			auto new_node = make_and(
				make_or(left_child->left->clone(), right_child->left->clone()),
				make_or(left_child->left->clone(),
						right_child->right->clone()));
			return transform_nnf_to_cnf(new_node.get());
		}
		if (arity(left_child->type) < 2)
			return (node->clone());
	}

	if (node->type == NodeType::And) {
		const ASTNode *child = node->left.get();
		if (!child)
			throw InvalidFormulaException();

		if (child->type == NodeType::And && arity(node->right->type) < 2) {
			auto new_node =
				make_and(child->left->clone(),
						 make_and(child->right->clone(), node->right->clone()));
			return transform_nnf_to_cnf(new_node.get());
		}

		if (arity(child->type) < 2)
			return node->clone();
	}

	return ASTNode::make_binary(node->type,
								transform_nnf_to_cnf(node->left.get()),
								transform_nnf_to_cnf(node->right.get()));
}
