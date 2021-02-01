#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <unordered_map>
#include <vector>
#include <string>
#include <AdjList.h>
#include <iostream>
#include <algorithm>
#include <stack> 

void BuildAdjList(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, const std::vector<std::vector<std::string>> &input_edge_list, AdjList &adj_list, AdjList &adj_list_rev);

void DFS(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time);

void DFSIterative(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time);

void DFSIterative2(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time);

void DFSLoop(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time, const bool use_decreasing_finish_time, int &finish_time);

void DFSLoop2(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time, const bool use_decreasing_finish_time, int &finish_time);

void ResetAllNodeToUnexplored(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln);

void CollectResult(std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, LinkedList*> &map_leader2scc);

void PrintResult(std::unordered_map<LinkedListNode*, LinkedList*> &map_leader2scc, std::vector<int> &scc_size_result);

#endif
