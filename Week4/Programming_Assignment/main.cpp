//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <solution.h>
#include <unordered_set>

//All of the input numbers from input text file.
std::vector<long> input_num_list;

//The set to store the input from input_num_list.
std::unordered_set<long> myset;

//The array of the target value.
std::vector<long> target_array;

//The answer
int answer = 0;

void BuildTargetArray(const long &range_min, const long &range_max, std::vector<long> &target_array){
    for(long i=range_min;i<=range_max;++i){
        target_array.push_back(i);
    }
}

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 
            for(std::string s; iss >> s;){
                input_num_list.push_back(std::stol(s));
            }
        }
        myfile.close();
    }else std::cout << "Unable to open file"; 
}

int main(int argc, char*argv[]){
    long range_min = -10000;
    long range_max = 10000;

    if(argc < 2){
        std::cerr<<"Error: There should be at least one input argument like ./main arg1."<<std::endl;
        return EXIT_FAILURE;
    }

    ReadFile(argv[1]);

    /*
    for(const auto &i : input_num_list){
        std::cout<<i<<std::endl;
    }
    */

    //Build the target array
    BuildTargetArray(range_min, range_max, target_array);

    //Build myset from input_num_list.
    BuildMySet(input_num_list, myset);

    //Calculate the answer of the 2-sum problem
    CalNumOfTargetTwoSum(target_array, myset, answer);
    std::cout<<"answer = "<<answer<<std::endl;

    return EXIT_SUCCESS;
}
