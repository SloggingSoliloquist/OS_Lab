#include<iostream>
#include<vector>

struct DetectDeadlock{
    int p, r; 
    std::vector<std::vector<int>> allocation, request;
    std::vector<int> available;
    
    public:
    DetectDeadlock(int p, int r):p(p), r(r), allocation(p, std::vector<int>(r)), request(p, std::vector<int>(r)), available(r)
    {}

    void input(){
        std::cout<<"Enter the allocation matrix: "<<std::endl;
        for(int i=0; i<p; i++){
            for(int j=0; j<r; j++){
                std::cin>>allocation[i][j];
            }
        }
        std::cout<<"Enter the request matrix: "<<std::endl;
        for(int i=0; i<p; i++){
            for(int j=0; j<r; j++){
                std::cin>>request[i][j];
            }
        }
        std::cout<<"Enter the available matrix: "<<std::endl;
        for(int i=0; i<r; i++){
            std::cin>>available[i];
        }
    }
    bool isSafe(){
        std::vector<int> work= available;
        std::vector<bool> finished(p, false);
        std::vector<int> deadlocked_procs;    //processes with 0 allocation are already free and not part of deadlock 
        for(int i=0; i<p; i++){
            bool free=true;
            for(int j=0; j<r; j++){
                if(allocation[i][j]!=0){
                    free=false; 
                    break;
                }
            }
            if (free){
                finished[i]=true;
            }
        }

        for(int count=0; count<p; count++){
            bool found = false;
            for(int i =0; i<p; i++){
                if(!finished[i]){
                    //check if possible to allocate
                    bool possible=true; 
                    for(int j=0; j<r; j++){
                        if(request[i][j]>work[j]){
                            possible=false;
                            break;
                        }
                    }
                    if(possible){
                        //pretend to allocate
                        for(int k=0; k<r; k++){
                            work[k]+=allocation[i][k];//not the request
                        }
                        found=true; 
                        finished[i]=true; 
                    }
                }
            }
            if(!found)break;
        }
        //if any unfinished processes, then deadlock 
        for(int i=0; i<p; i++){
            if(!finished[i])deadlocked_procs.push_back(i);
        }
        if (deadlocked_procs.empty()){
            std::cout<<"No deadlocks detected"<<std::endl;
            return true;
        }
        else{
            std::cout<<"System is in deadlock. Deadlocked processes: "<<std::endl; 
            for(auto proc:deadlocked_procs){
                std::cout<<" "<<proc;
            }
            return false;
        }
    }
};

int main(){
    int p, r; 
    std::cout<<"Enter the number of processes and resources: ";
    std::cin>>p>>r;
    DetectDeadlock d(p, r);
    d.input(); 
    d.isSafe();
}