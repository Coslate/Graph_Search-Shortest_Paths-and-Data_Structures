#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>

void BuildMySet(const std::vector<long> &input_num_list, std::unordered_set<long> &myset);

void CalNumOfTargetTwoSum(const std::vector<long> &target_array, std::unordered_set<long> &myset, int &answer);

#endif
