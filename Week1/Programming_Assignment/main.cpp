//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <AdjList.h>
#include <solution.h>

bool debug_addr     = true;
bool debug_key      = true;
bool debug_name     = true;
bool debug_explored = true;
bool directed       = true;

std::vector<std::vector<std::string>> input_edge_list;

//Generate the correspondence between Node & LinkedListNode.
std::unordered_map<std::string, LinkedListNode*> map_node_st2lln;

//For storing the leader of a node in a SCC.
std::unordered_map<LinkedListNode*, LinkedListNode*> map_leader_lln2lln;

//For storing the finish time of each node.
std::unordered_map<LinkedListNode*, int> map_lln2ft;

//For storing every node in a given finish time.
std::unordered_map<int, LinkedList*> map_ft2ll;

//Each element is a leader node -> list within the same leader of SCC.
std::unordered_map<LinkedListNode*, LinkedList*> map_leader2scc;

std::vector<int> scc_size_result;

//Declare a new adjacent list to represent Graph(V, E).
AdjList adj_list(directed, false);
AdjList adj_list_rev(directed, false);

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 
            std::vector<std::string> tmp_vec_edge;

            for(std::string s; iss >> s;) 
                tmp_vec_edge.push_back(s); 
            //std::cout << line << '\n';
            //
            if(tmp_vec_edge.size() != 0){
                input_edge_list.push_back(tmp_vec_edge);
            }
        }
        myfile.close();
    }else std::cout << "Unable to open file"; 
}

int main(int argc, char*argv[]){
    if(argc < 2){
        std::cerr<<"Error: There should be at least one input argument like ./main arg1."<<std::endl;
        return EXIT_FAILURE;
    }
    int finish_time = 0;
    int method = 1;

    ReadFile(argv[1]);
    BuildAdjList(map_node_st2lln, input_edge_list, adj_list, adj_list_rev);

    if(strcmp(argv[2], "-method") == 0){
        method = atoi(argv[3]);
    }
/*
    std::cout<<"map_node_st2lln = "<<std::endl;
    for (auto element : map_node_st2lln) {
        LinkedListNode* the_node = element.second;
        std::cout<<the_node->GetName()<<"("<<the_node<<")"<<", color = "<<the_node->GetColor()<<std::endl;
    }
*/

    std::cout<<"-----------1st-------------"<<std::endl;
    //1st DFSLoop - To calculate the finish time.
    if(method == 1){
        std::cout<<"Use 'DFSLoop' subroutine..."<<std::endl;
        DFSLoop(map_node_st2lln, adj_list_rev, map_leader_lln2lln, map_lln2ft, map_ft2ll, true, false, finish_time);
    }else if(method == 2){
        std::cout<<"Use 'DFSLoop2' subroutine..."<<std::endl;
        DFSLoop2(map_node_st2lln, adj_list_rev, map_leader_lln2lln, map_lln2ft, map_ft2ll, true, false, finish_time);
    }

    std::cout<<"-----------2nd-------------"<<std::endl;
    //2nd DFSLoop - To calculate the SCC
    ResetAllNodeToUnexplored(map_node_st2lln);
    if(method == 1){
        std::cout<<"Use 'DFSLoop' subroutine..."<<std::endl;
        DFSLoop(map_node_st2lln, adj_list, map_leader_lln2lln, map_lln2ft, map_ft2ll, false, true, finish_time);
    }else if(method == 2){
        std::cout<<"Use 'DFSLoop2' subroutine..."<<std::endl;
        DFSLoop2(map_node_st2lln, adj_list, map_leader_lln2lln, map_lln2ft, map_ft2ll, false, true, finish_time);
    }

/*
    std::cout<<"the finish time of each node: "<<std::endl;
    for (auto element : map_lln2ft) {
        LinkedListNode* the_node = element.first;
        std::cout<<the_node->GetName()<<"("<<the_node<<") : finish_time = "<<element.second<<std::endl;
    }
*/


    CollectResult(map_leader_lln2lln, map_leader2scc);

    PrintResult(map_leader2scc, scc_size_result);
/*
    std::cout<<"-----------------adj_list, AdjList::PrintAdjList, node: 21081-----------------"<<std::endl;
    adj_list.PrintAdjList(map_node_st2lln, map_node_st2lln["21081"], debug_addr, debug_name, debug_key, debug_explored);

    std::cout<<"-----------------adj_list_rev, AdjList::PrintAdjList, node: 21081-----------------"<<std::endl;
    adj_list_rev.PrintAdjList(map_node_st2lln, map_node_st2lln["21081"], debug_addr, debug_name, debug_key, debug_explored);
*/

    std::cout<<"input_edge_list.size() = "<<input_edge_list.size()<<std::endl;
    return EXIT_SUCCESS;
}
