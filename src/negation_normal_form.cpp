/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negation_normal_form.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:12:01 by esouhail          #+#    #+#             */
/*   Updated: 2026/06/30 11:59:29 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "bool.h"

std::string negation_normal_form(const std::string &formula) {
	std::unique_ptr<ASTNode> root = build_ast(formula);

	std::unique_ptr<ASTNode> nnf_root = root->clone();
	nnf_root						  = transform_to_nnf(nnf_root.get());
	std::string result				  = to_rpn(nnf_root.get());
	return result;
}

std::unique_ptr<ASTNode> transform_to_nnf(const ASTNode *node) {
	if (!node)
		throw InvalidFormulaException();

	if (node->type == NodeType::Implies) {
		auto new_node = ASTNode::make_binary(
				NodeType::Or,
				ASTNode::make_unary(NodeType::Not, node->left->clone()),
				node->right->clone()
			);
		return transform_to_nnf(new_node.get());
	}

	if (node->type == NodeType::Iff) {
		auto new_node = ASTNode::make_binary(
				NodeType::And,
				ASTNode::make_binary(
					NodeType::Or, 
					ASTNode::make_unary(NodeType::Not, node->left->clone()), 
					node->right->clone()
				),
				ASTNode::make_binary(
					NodeType::Or,
					node->left->clone(),
					ASTNode::make_unary(NodeType::Not, node->right->clone())
				)
			);
		return transform_to_nnf(new_node.get());
	}

	if (node->is_leaf())
		return node->clone();
	
	if (node->type == NodeType::Not) {
		const ASTNode *child = node->left.get();
		if (!child)
			throw InvalidFormulaException();

		if (child->type == NodeType::Not) {
			if (!child->left)
				throw InvalidFormulaException();
			return transform_to_nnf(child->left.get());
		}
		
		if (child->type == NodeType::And || child->type == NodeType::Or)
		{
			auto new_node = ASTNode::make_binary(
				child->type == NodeType::And ? NodeType::Or : NodeType::And,
				ASTNode::make_unary(NodeType::Not, child->left->clone()),
				ASTNode::make_unary(NodeType::Not, child->right->clone())
			);
			return transform_to_nnf(new_node.get());
		}

		if (child->is_leaf())
			return node->clone();

		auto new_child = transform_to_nnf(child);
        return transform_to_nnf(
            ASTNode::make_unary(NodeType::Not, std::move(new_child)).get()
        );
	}

	return ASTNode::make_binary(
			node->type,
			transform_to_nnf(node->left.get()),
			transform_to_nnf(node->right.get())
		);
}
