#ifndef _SOLUTION_H_
#define _SOLUTION_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <AdjList.h>
#include <iostream>
#include <algorithm>
#include <stack> 

void BuildAdjList(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, const std::vector<std::vector<std::string>> &input_edge_list, AdjList &adj_list, AdjList &adj_list_rev, const bool set_weight=false);

void BuildAdjList(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, const std::vector<std::vector<std::string>> &input_edge_list, AdjList &adj_list, const bool set_weight=false);

void DFS(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time);

void DFSIterative(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time);

void DFSIterative2(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time);

void DFSLoop(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time, const bool use_decreasing_finish_time, int &finish_time);

void DFSLoop2(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time, const bool use_decreasing_finish_time, int &finish_time);

void ResetAllNodeToUnexplored(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln);

void CollectResult(std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, LinkedList*> &map_leader2scc);

void PrintResult(std::unordered_map<LinkedListNode*, LinkedList*> &map_leader2scc, std::vector<int> &scc_size_result);

void DijkstraNaiveImplementation(std::unordered_set<std::string> &myset, std::unordered_set<std::string> &uncovered_set, std::unordered_map<std::string, int> &shortest_path_dist, std::unordered_map<std::string, std::string> &shortest_path_prec, AdjList &adj_list, const int total_vertex_size, std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln);

#endif
