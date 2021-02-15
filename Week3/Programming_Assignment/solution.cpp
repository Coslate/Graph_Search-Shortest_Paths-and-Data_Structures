//solution.cpp
#include <solution.h>

void ReBalance(MinHeap<int> &heap_min, MinHeap<int> &heap_max, const int &surpass_num, const bool &max_to_min){
    int surpass_remain_value = surpass_num;

    if(max_to_min){
        while(surpass_remain_value > 0){
            int max_val = -1*heap_max.ExtractMin();
            heap_min.Insert(max_val);
            --surpass_remain_value;
        }
    }else{
        while(surpass_remain_value > 0){
            int min_val = heap_min.ExtractMin();
            heap_max.Insert(-1*min_val);
            --surpass_remain_value;
        }
    
    }
}

void MedianMaintain(const std::vector<int> &input_num_list, MinHeap<int> &heap_min, MinHeap<int> &heap_max, std::vector<int> &median_vec){
    for(size_t i=0;i<input_num_list.size();++i){
        //Heap insertion
        //std::cout<<"i = "<<i<<", pt1"<<std::endl;
        if((heap_max.GetSize() == 0) && (heap_min.GetSize() == 0)){
            heap_max.Insert(-1*input_num_list[i]);
        }else if((heap_max.GetSize() == 0) && (heap_min.GetSize() > 0)){
            if(input_num_list[i]<heap_min.top()){
                heap_max.Insert(-1*input_num_list[i]);
            }else{
                heap_min.Insert(input_num_list[i]);
            }
        }else if((heap_max.GetSize() > 0) && (heap_min.GetSize() == 0)){
            if(input_num_list[i]>-1*heap_max.top()){
                heap_min.Insert(input_num_list[i]);
            }else{
                heap_max.Insert(-1*input_num_list[i]);
            }
        }else if((heap_max.GetSize() > 0) && (heap_min.GetSize() > 0)){
            if(input_num_list[i] <= -1*heap_max.top()){
                heap_max.Insert(-1*input_num_list[i]);
            }else if(input_num_list[i] >= heap_min.top()){
                heap_min.Insert(input_num_list[i]);
            }else if((input_num_list[i] < heap_min.top()) && (input_num_list[i] > -1*heap_max.top())){
                heap_max.Insert(-1*input_num_list[i]);
            }
        }

        //std::cout<<"heap_max.size = "<<heap_max.GetSize()<<std::endl;
        //std::cout<<"heap_min.size = "<<heap_min.GetSize()<<std::endl;
        //std::cout<<"i = "<<i<<", pt2"<<std::endl;
        //Do the rebalancing
        if(heap_max.GetSize() - heap_min.GetSize() == 2){
            ReBalance(heap_min, heap_max, 1, true);
        }else if(heap_min.GetSize() - heap_max.GetSize() == 2){
            ReBalance(heap_min, heap_max, 1, false);
        }

        //std::cout<<"heap_max.size = "<<heap_max.GetSize()<<std::endl;
        //std::cout<<"heap_min.size = "<<heap_min.GetSize()<<std::endl;
        //std::cout<<"i = "<<i<<", pt3"<<std::endl;
        //Median Calculation
        if((i+1)%2 == 0){//k is even
            //std::cout<<"i = "<<i<<", pt3-1"<<std::endl;
            median_vec.push_back(-1*heap_max.top());
        }else{//k is odd
            //std::cout<<"i = "<<i<<", pt3-2"<<std::endl;
            if(heap_max.GetSize() > heap_min.GetSize()){
                //std::cout<<"i = "<<i<<", pt3-3"<<std::endl;
                median_vec.push_back(-1*heap_max.top());
            }else{
                //std::cout<<"i = "<<i<<", pt3-4"<<std::endl;
                median_vec.push_back(heap_min.top());
            }
        }
    }
}
