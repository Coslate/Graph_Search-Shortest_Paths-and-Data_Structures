//solution.cpp
#include <solution.h>


void BuildAdjList(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, const std::vector<std::vector<std::string>> &input_edge_list, AdjList &adj_list, AdjList &adj_list_rev){
    //Build the mapping of node_name -> address for all nodes.
    for (auto &itRow : input_edge_list){
        for (size_t i=0; i<itRow.size();++i){
            if(map_node_st2lln.find(itRow[i]) == map_node_st2lln.end()){//not found
                LinkedListNode* new_node = new LinkedListNode(0, itRow[i]);
                map_node_st2lln[itRow[i]] = new_node;
            }
        }

        //Build the adjacent list for all nodes.
        adj_list.SetAdjList(map_node_st2lln[itRow[0]], map_node_st2lln[itRow[1]], 0);
        adj_list_rev.SetAdjList(map_node_st2lln[itRow[1]], map_node_st2lln[itRow[0]], 0);
    }
}

void DFS(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time){
    invoke_node->SetExplored(true);
    map_leader_lln2lln[invoke_node] = first_invoke_node;

//    std::cout<<"invoke_node = "<<invoke_node->GetName()<<"("<<invoke_node<<")"<<std::endl;
    LinkedList* the_linked_list = adj_list.ReadAdjList(invoke_node);

    if(the_linked_list == NULL){
//        std::cout<<"The invoke_node: "<<invoke_node->GetName()<<"("<<invoke_node<<")"<<", explored = "<<invoke_node->GetExplored()<<", has no adjacent List."<<std::endl;
    }

    //Traversing all the adjacent nodes.
    if(the_linked_list != NULL){
        LinkedListNode* current_node = the_linked_list->GetFristNode();
        while(current_node != NULL){
            if(map_node_st2lln[current_node->GetName()]->GetExplored() == false){
                DFS(map_node_st2lln, adj_list, map_node_st2lln[current_node->GetName()], first_invoke_node, map_leader_lln2lln, finish_time, map_lln2ft, map_ft2ll, cal_finish_time);
            }
            current_node = current_node->GetNext();
        }
    }
    
    if(cal_finish_time){
        ++finish_time;

        map_lln2ft[invoke_node] = finish_time;

        if(map_ft2ll.find(finish_time) == map_ft2ll.end()){//not found
            LinkedList* the_finish_time_node_linked_list = new LinkedList();
            the_finish_time_node_linked_list->InsertTail(0, invoke_node->GetName());
            map_ft2ll[finish_time] = the_finish_time_node_linked_list;
        }else{
            LinkedList* the_finish_time_node_linked_list = map_ft2ll[finish_time];
            the_finish_time_node_linked_list->InsertTail(0, invoke_node->GetName());
        }
    }
}

void DFSIterative(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time){
    std::stack<LinkedListNode*> mystack;
    mystack.push(invoke_node);

    while(!mystack.empty()){
        LinkedListNode* proc_node = mystack.top();

        if(proc_node -> GetExplored() == false){
            proc_node->SetExplored(true);
            map_leader_lln2lln[proc_node] = first_invoke_node;

//            std::cout<<"proc_node = "<<proc_node->GetName()<<"("<<proc_node<<"), color = "<<proc_node->GetColor()<<std::endl;
            LinkedList* the_linked_list = adj_list.ReadAdjList(proc_node);

            if(the_linked_list == NULL){
//                std::cout<<"The proc_node: "<<proc_node->GetName()<<"("<<proc_node<<")"<<", explored = "<<proc_node->GetExplored()<<", has no adjacent List."<<std::endl;
            }

            //Traversing all the adjacent nodes.
            if(the_linked_list != NULL){
                LinkedListNode* current_node = the_linked_list->GetFristNode();
                while(current_node != NULL){
                    if(map_node_st2lln[current_node->GetName()]->GetExplored() == false){
                        mystack.push(map_node_st2lln[current_node->GetName()]);
                    }
                    current_node = current_node->GetNext();
                }
            }
        }else{
            if((proc_node->GetColor() == 0) && cal_finish_time){
                ++finish_time;
                map_lln2ft[proc_node] = finish_time;

                if(map_ft2ll.find(finish_time) == map_ft2ll.end()){//not found
                    LinkedList* the_finish_time_node_linked_list = new LinkedList();
                    the_finish_time_node_linked_list->InsertTail(0, proc_node->GetName());
                    map_ft2ll[finish_time] = the_finish_time_node_linked_list;
                }else{
                    LinkedList* the_finish_time_node_linked_list = map_ft2ll[finish_time];
                    the_finish_time_node_linked_list->InsertTail(0, proc_node->GetName());
                }

                proc_node->SetColor(1);
            }
            mystack.pop();
//            std::cout<<"finish_time = "<<finish_time<<", "<<"pop out proc_node: "<<proc_node->GetName()<<"("<<proc_node<<"), color = "<<proc_node->GetColor()<<std::endl;
        }
    }
}

void DFSIterative2(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, LinkedListNode *invoke_node, LinkedListNode *first_invoke_node, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, int &finish_time, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time){

    //Color-0: WHITE
    //Color-1: GRAY
    //Color-2: BLACK
    
    std::stack<LinkedListNode*> mystack;
    mystack.push(invoke_node);

    while(!mystack.empty()){
        LinkedListNode* proc_node = mystack.top();
        mystack.pop();
        bool all_adj_discovered;

        if(proc_node -> GetColor() != 2){
            mystack.push(proc_node);

            if(proc_node ->GetColor() == 0){
                proc_node->SetColor(1);
            }

            all_adj_discovered = true;
//            std::cout<<"proc_node = "<<proc_node->GetName()<<"("<<proc_node<<"), color = "<<proc_node->GetColor()<<std::endl;
            LinkedList* the_linked_list = adj_list.ReadAdjList(proc_node);

            if(the_linked_list == NULL){
//                std::cout<<"The proc_node: "<<proc_node->GetName()<<"("<<proc_node<<")"<<", explored = "<<proc_node->GetExplored()<<", has no adjacent List."<<std::endl;
            }

            //Traversing all the adjacent nodes.
            if(the_linked_list != NULL){
                LinkedListNode* current_node = the_linked_list->GetFristNode();
                while(current_node != NULL){
                    if(map_node_st2lln[current_node->GetName()]->GetColor() == 0){
                        mystack.push(map_node_st2lln[current_node->GetName()]);
                        all_adj_discovered = false;
                    }
                    current_node = current_node->GetNext();
                }
            }
            
            if(all_adj_discovered){
                proc_node->SetColor(2);
                if(cal_finish_time){
                    ++finish_time;
                    map_lln2ft[proc_node] = finish_time;

                    if(map_ft2ll.find(finish_time) == map_ft2ll.end()){//not found
                        LinkedList* the_finish_time_node_linked_list = new LinkedList();
                        the_finish_time_node_linked_list->InsertTail(0, proc_node->GetName());
                        map_ft2ll[finish_time] = the_finish_time_node_linked_list;
                    }else{
                        LinkedList* the_finish_time_node_linked_list = map_ft2ll[finish_time];
                        the_finish_time_node_linked_list->InsertTail(0, proc_node->GetName());
                    }
                }
                mystack.pop();
                map_leader_lln2lln[proc_node] = first_invoke_node;
//                std::cout<<"finish_time = "<<finish_time<<", "<<"pop out proc_node: "<<proc_node->GetName()<<"("<<proc_node<<"), color = "<<proc_node->GetColor()<<std::endl;
            }
        }
    }
}

void DFSLoop(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time, const bool use_decreasing_finish_time, int &finish_time){
    if(use_decreasing_finish_time == false){
        for (auto element : map_node_st2lln) {
            LinkedListNode* the_node = element.second;
//            std::cout<<"the_node = "<<the_node->GetName()<<"("<<the_node<<")"<<", color = "<<the_node->GetColor()<<std::endl;
            if(the_node -> GetExplored() == false){
                DFSIterative(map_node_st2lln, adj_list, the_node, the_node, map_leader_lln2lln, finish_time, map_lln2ft, map_ft2ll, cal_finish_time);
            }
        }
    }else{
        for(int i=finish_time;i>0;--i){
            if(map_ft2ll.find(i) != map_ft2ll.end()){//found
                LinkedList* the_linked_list_time = map_ft2ll[i];
                LinkedListNode* current_node     = the_linked_list_time->GetFristNode();
                while(current_node != NULL){
                    LinkedListNode* the_node = map_node_st2lln[current_node->GetName()];
//                    std::cout<<"the_node = "<<the_node->GetName()<<"("<<the_node<<")"<<std::endl;
                    if(the_node->GetExplored() == false){
                        DFSIterative(map_node_st2lln, adj_list, the_node, the_node, map_leader_lln2lln, finish_time, map_lln2ft, map_ft2ll, cal_finish_time);
                    }
                    current_node = current_node->GetNext();
                }
            }
        }
    }
}

void DFSLoop2(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln, AdjList &adj_list, std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, int> &map_lln2ft, std::unordered_map<int, LinkedList*> &map_ft2ll, const bool cal_finish_time, const bool use_decreasing_finish_time, int &finish_time){
    if(use_decreasing_finish_time == false){
        for (auto element : map_node_st2lln) {
            LinkedListNode* the_node = element.second;
//            std::cout<<"the_node = "<<the_node->GetName()<<"("<<the_node<<")"<<", color = "<<the_node->GetColor()<<std::endl;
            if(the_node -> GetColor() == 0){
                DFSIterative2(map_node_st2lln, adj_list, the_node, the_node, map_leader_lln2lln, finish_time, map_lln2ft, map_ft2ll, cal_finish_time);
            }
        }
    }else{
        for(int i=finish_time;i>0;--i){
            if(map_ft2ll.find(i) != map_ft2ll.end()){//found
                LinkedList* the_linked_list_time = map_ft2ll[i];
                LinkedListNode* current_node     = the_linked_list_time->GetFristNode();
                while(current_node != NULL){
                    LinkedListNode* the_node = map_node_st2lln[current_node->GetName()];
//                    std::cout<<"the_node = "<<the_node->GetName()<<"("<<the_node<<")"<<std::endl;
                    if(the_node->GetColor() == 0){
                        DFSIterative2(map_node_st2lln, adj_list, the_node, the_node, map_leader_lln2lln, finish_time, map_lln2ft, map_ft2ll, cal_finish_time);
                    }
                    current_node = current_node->GetNext();
                }
            }
        }
    }
}

void ResetAllNodeToUnexplored(std::unordered_map<std::string, LinkedListNode*> &map_node_st2lln){
    for (auto element : map_node_st2lln) {
        LinkedListNode* the_node = element.second;
        the_node -> SetExplored(false);
        the_node -> SetColor(0);
    }
}

void CollectResult(std::unordered_map<LinkedListNode*, LinkedListNode*> &map_leader_lln2lln, std::unordered_map<LinkedListNode*, LinkedList*> &map_leader2scc){
    for (auto element : map_leader_lln2lln) {
        LinkedListNode* invoke_node = element.first;
        LinkedListNode* leader_node = element.second;

        if(map_leader2scc.find(leader_node) == map_leader2scc.end()){//not found
            LinkedList* the_scc_linked_list = new LinkedList();
            the_scc_linked_list->InsertTail(0, invoke_node->GetName());
            map_leader2scc[leader_node] = the_scc_linked_list;
        }else{
            LinkedList* the_scc_linked_list = map_leader2scc[leader_node];
            the_scc_linked_list->InsertTail(0, invoke_node->GetName());
        }
    }
}

void PrintResult(std::unordered_map<LinkedListNode*, LinkedList*> &map_leader2scc, std::vector<int> &scc_size_result){
    for (auto element : map_leader2scc) {
        LinkedListNode* leader_node     = element.first;
        LinkedList* the_linked_list     = element.second;

        int count = 0;
        int scc_size = the_linked_list->GetListSize();
        LinkedListNode* current_node = the_linked_list->GetFristNode();
        while(current_node != NULL){
            if((count == 0) && (count == (scc_size-1))){
                std::cout<<"scc["<<leader_node->GetName()<<"] = ["<<current_node->GetName()<<"]"<<std::endl;
            }else if(count == 0){
                std::cout<<"scc["<<leader_node->GetName()<<"] = ["<<current_node->GetName()<<", ";
            }else if(count == scc_size-1){
                std::cout<<current_node->GetName()<<"]"<<std::endl;
            }else{
                std::cout<<current_node->GetName()<<", ";
            }
            ++count;
            current_node = current_node->GetNext();
        } 
        std::cout<<"size = "<<scc_size<<std::endl;
        scc_size_result.push_back(scc_size);
        std::cout<<"----------------"<<std::endl;
    }

    std::sort(scc_size_result.begin(), scc_size_result.end(), std::greater<>());
    std::cout<<"All size of the SCC in descending order(max 5) : ";
    if(scc_size_result.size() < 5){
        for(size_t i=0;i<scc_size_result.size();++i){
            if(i==scc_size_result.size()-1){
                std::cout<<scc_size_result[i]<<std::endl;
            }else{
                std::cout<<scc_size_result[i]<<",";
            }
        }
    }else{
        for(size_t i=0;i<5;++i){
            if(i==5-1){
                std::cout<<scc_size_result[i]<<std::endl;
            }else{
                std::cout<<scc_size_result[i]<<",";
            }
        }
    
    }
}


