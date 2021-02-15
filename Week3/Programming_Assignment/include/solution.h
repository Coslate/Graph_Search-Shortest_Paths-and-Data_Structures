#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <MinHeap.h>

void ReBalance(MinHeap<int> &heap_min, MinHeap<int> &heap_max, const int &surpass_num);

void MedianMaintain(const std::vector<int> &input_num_list, MinHeap<int> &heap_min, MinHeap<int> &heap_max, std::vector<int> &median_vec);

#endif
