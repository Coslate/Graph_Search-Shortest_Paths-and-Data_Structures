//main.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> input_edge_list;

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()){
        while ( std::getline (myfile,line) ){
            std::istringstream iss(line); 
            std::vector<int> tmp_vec_edge;

            for(int s; iss >> s;) 
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

    ReadFile(argv[1]);

/*
    for (auto &itRow : input_edge_list){
        for (size_t i=0; i<itRow.size();++i){
//            std::cout << itRow[i] << " ";
       }
//        std::cout << std::endl;
    }
*/

    std::cout<<"input_edge_list.size() = "<<input_edge_list.size()<<std::endl;
    return EXIT_SUCCESS;
}
