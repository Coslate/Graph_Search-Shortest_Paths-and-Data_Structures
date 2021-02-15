//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <solution.h>
#include <unordered_set>
#include <MinHeap.h>

//All of the input numbers from input text file.
std::vector<int> input_num_list;
//Answer
std::vector<int> median_vec;
long long final_answer = 0;

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 
            for(std::string s; iss >> s;){
                input_num_list.push_back(std::stoi(s));
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

    MinHeap<int> heap_min;//store the maximum half part
    MinHeap<int> heap_max;//store the minimum half part

    ReadFile(argv[1]);

    /*for(const auto &i : input_num_list){
        std::cout<<i<<std::endl;
    }*/
    
    MedianMaintain(input_num_list, heap_min, heap_max, median_vec);

    for(auto const &i : median_vec){
        std::cout<<i<<std::endl;
        final_answer += i;
    }
    final_answer = final_answer % 10000;
    std::cout<<"final_answer = "<<final_answer<<std::endl;
    return EXIT_SUCCESS;
}
