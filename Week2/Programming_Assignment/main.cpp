//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <solution.h>

bool debug_addr     = false;
bool debug_key      = true;
bool debug_name     = true;
bool debug_explored = true;
bool directed       = true; //In fact, this graph is an undirected graph, but the input txt file already has listed all the forward/reverse edges, so the data structure we build should set directed so as to remove redundent 'reverse' edge insertion in AdjList::SetAdjList().
bool set_weight     = true;

/*
//Generate the correspondence between Node & LinkedListNode.

//For storing the leader of a node in a SCC.
std::unordered_map<LinkedListNode*, LinkedListNode*> map_leader_lln2lln;

//For storing the finish time of each node.
std::unordered_map<LinkedListNode*, int> map_lln2ft;

//For storing every node in a given finish time.
std::unordered_map<int, LinkedList*> map_ft2ll;

//Each element is a leader node -> list within the same leader of SCC.
std::unordered_map<LinkedListNode*, LinkedList*> map_leader2scc;
*/

//All of the edges and the correspondent weight from input text file.
std::vector<std::vector<std::string>> input_edge_list;

//Generate the correspondence between Node & LinkedListNode.
std::unordered_map<std::string, LinkedListNode*> map_node_st2lln;

//Dijkstra, original set
std::unordered_set<std::string> myset;

//Dijkstra, unconvered set
std::unordered_set<std::string> uncovered_set;

std::unordered_map<std::string, int> shortest_path_dist;

std::unordered_map<std::string, std::string> shortest_path_prec;

//Declare a new adjacent list to represent Graph(V, E).
AdjList adj_list(directed, false);

//Decleare a MinHeap to store the uncovered set with key value = shortest path.
MinHeap<LinkedListNode> min_heap;

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 
            int count = 0;
            std::string tail_v = "";

            for(std::string s; iss >> s;){
                if(count != 0){
                    std::vector<std::string> tmp_vec_edge;
                    std::string delimiter = ",";
                    size_t pos = 0;
                    std::string token;

                    if((pos = s.find(delimiter)) != std::string::npos){
                        token = s.substr(0, pos);
                        tmp_vec_edge.push_back(tail_v);
                        tmp_vec_edge.push_back(token);
                        std::cout<<"(V="<<token<<" ";
                        s.erase(0, pos + delimiter.length());
                        tmp_vec_edge.push_back(s);
                        std::cout<<"W="<<s<<"), ";
                        input_edge_list.push_back(tmp_vec_edge);
                    }
                }else{
                    tail_v = s;
                    std::cout << tail_v <<": ";
                }
                ++count;
            }
            std::cout<<std::endl;
        }
        myfile.close();
    }else std::cout << "Unable to open file"; 
}

int main(int argc, char*argv[]){
    if(argc < 2){
        std::cerr<<"Error: There should be at least one input argument like ./main arg1."<<std::endl;
        return EXIT_FAILURE;
    }
    
    int method = 1;//1: Naive Based, 2: MinHeap Based
    if( (argc > 2) && (strcmp(argv[2], "-method") == 0)){
        method = atoi(argv[3]);
    }
    std::cout<<"method = "<<method<<std::endl;

    ReadFile(argv[1]);
    BuildAdjList(map_node_st2lln, input_edge_list, adj_list, set_weight, method);

    std::cout<<"----------input_edge_list------------"<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    for (auto &itRow : input_edge_list){
        for (size_t i=0; i<itRow.size();++i){
            if(i==0){
                std::cout<<"("<<itRow[i]<<", ";
            }else if(i == itRow.size()-1){
                std::cout<<itRow[i]<<")"<<std::endl;
            }else{
                std::cout<<itRow[i]<<", ";
            }
        }
    }

    std::cout<<"----------adj_list------------"<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"----------------------"<<std::endl;

    for (auto element : map_node_st2lln) {
        LinkedListNode* the_node = element.second;
        std::cout<<">>>> map_node_st2lln->the_node = "<<the_node->GetName()<<"("<<the_node<<")..."<<std::endl;
        adj_list.PrintAdjList(map_node_st2lln, the_node, debug_addr, debug_name, debug_key);
    }

    std::cout<<"----------Dijkstra------------"<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"> Initialization..."<<std::endl;
    std::cout<<"source : "<<input_edge_list[0][0]<<std::endl;

    for (auto element : map_node_st2lln) {
        LinkedListNode* the_node = element.second;
        std::string node_name = element.first;
        if(node_name.compare(input_edge_list[0][0]) != 0){//different with source node
            uncovered_set.insert(node_name);
        }

        //Build the MinHeap
        if(method == 2){
            min_heap.Insert(*the_node);
        }
    }

    for(auto element : uncovered_set){
        std::cout<<"uncovered_node = "<<element<<std::endl;
    }

    std::cout<<"> Calculating Dijkstra..."<<std::endl;
    if(method == 1){
        std::cout<<">> Using Naive based(-method 1)..."<<std::endl;
        myset.insert(input_edge_list[0][0]);
        shortest_path_dist[input_edge_list[0][0]] = 0;
        DijkstraNaiveImplementation(myset, uncovered_set, shortest_path_dist, shortest_path_prec, adj_list, map_node_st2lln.size(), map_node_st2lln);
    }else if(method == 2){
        std::cout<<">> Using Heap based(-method 2)..."<<std::endl;
        min_heap.DecreaseKey(input_edge_list[0][0], 0);//start from the '1' node
        DijkstraHeapImplementation(myset, uncovered_set, shortest_path_dist, shortest_path_prec, adj_list, map_node_st2lln.size(), map_node_st2lln, min_heap);
    }

    std::cout<<"> Show the result..."<<std::endl;
    std::vector<std::string> result_str_vec;
    result_str_vec.push_back("7");
    result_str_vec.push_back("37");
    result_str_vec.push_back("59");
    result_str_vec.push_back("82");
    result_str_vec.push_back("99");
    result_str_vec.push_back("115");
    result_str_vec.push_back("133");
    result_str_vec.push_back("165");
    result_str_vec.push_back("188");
    result_str_vec.push_back("197");

    for(size_t i=0;i<result_str_vec.size();++i){
        if(i == result_str_vec.size() - 1){
            std::cout<<shortest_path_dist[result_str_vec[i]]<<""<<std::endl;
        }else{
            std::cout<<shortest_path_dist[result_str_vec[i]]<<",";
        }
    }

    return EXIT_SUCCESS;
}
