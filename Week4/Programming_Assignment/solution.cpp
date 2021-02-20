//solution.cpp
#include <solution.h>

void BuildMySet(const std::vector<long> &input_num_list, std::unordered_set<long> &myset){
    for(const auto &i : input_num_list){
        myset.insert(i);
    }
}

void CalNumOfTargetTwoSum(const std::vector<long> &target_array, std::unordered_set<long> &myset, int &answer){
    long count = 0;
    double last_progress = 0;
    double progress = 0;

    for(const auto &target_value : target_array){
        for(const auto &x : myset){
            long y = target_value - x;
            if((y != x) && (myset.find(y) != myset.end())){
                ++answer;
                break;
            }
        }

        //for inspecting progress.
        ++count;
        progress = count/double(target_array.size()) * 100;
        if(progress - last_progress > 1 ){
            last_progress = progress;
            std::cout<<"target_array.size() = "<<target_array.size()<<", current count = "<<count<<", progress = "<<progress<<"%"<<std::endl;
        }
    }
}
