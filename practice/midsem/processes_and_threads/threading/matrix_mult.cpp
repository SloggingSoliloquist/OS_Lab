#include<algorithm>
#include<thread>
#include<vector>
#include<iostream>

void get_single_el(std::vector<std::vector<int>> &a, std::vector<std::vector<int>> &b, int row_num, int col_num, int num_col, int &result){
    result=0;
    for(int i=0; i<num_col; i++){
        result+=a[row_num][i]*b[i][col_num];
    }
}

int main(){
    int m, n, p;
    std::cout<<"Enter m: ";
    std::cin>>m;
    std::cout<<"Enter n: ";
    std::cin>>n;
    std::cout<<"Enter p: ";
    std::cin>>p;


    std::vector<std::vector<int>> matA(m,std::vector<int>(n,0));
    std::vector<std::vector<int>> matB(n,std::vector<int>(p,0));
    std::vector<std::vector<int>> matC(m,std::vector<int>(p,0)); 

    std::cout<<"Enter matrix A: "<<std::endl;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            std::cin>>matA[i][j];
        }
    }
    std::cout<<"Enter matrix B: "<<std::endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<p; j++){
            std::cin>>matB[i][j];
        }
    }
    //create a vector of m tasks (one for each row that has be operated on to get an element of the result)
    std::vector<std::vector<std::thread>> threads;
    //now create each thread and execute
    for(int i=0; i<m; i++){
        std::vector<std::thread> row;
        for(int j=0; j<p; j++){
            row.push_back(std::thread(get_single_el, std::ref(matA),std::ref(matB), i, j, n, std::ref(matC[i][j])));
        }
        threads.push_back(std::move(row));//threads can't be copied, so you need to use std::move
    }
    
    for(auto &row:threads){
        for(auto &thread:row){
            thread.join();
        }
    }

    for(int i=0; i<m; i++){
        for(int j=0; j<p; j++)
        {
            std::cout<<matC[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}