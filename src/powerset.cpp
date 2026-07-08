/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <ductive99.github.io>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 19:37:02 by esouhail          #+#    #+#             */
/*   Updated: 2026/07/08 20:49:22 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"

static void backtrack(vector<i32> &set, vector<i32> &current, vector<vector<i32>> &result, u32 pos);

vector<vector<i32>> powerset(vector<i32> &set)
{
	vector<vector<i32>> result;
	vector<i32> temp;

	backtrack(set, temp, result, 0);
	return result;
}

static void backtrack(vector<i32> &set, vector<i32> &current, vector<vector<i32>> &result, u32 pos)
{
	if (pos == set.size())
	{
		result.push_back(current);
		return;
	}
	
	current.push_back(set[pos]);
	backtrack(set, current, result, pos + 1);

	current.pop_back();
	backtrack(set, current, result, pos + 1);
}

void	print_vec(vector<i32> &arr)
{
	std::cout << "> ";
	for (const auto &n : arr)
		std::cout << n << " ";
	std::cout << std::endl;
}

