#include<iostream>
#include<vector>
#include<array>

struct Bankers{
    int p; //no. of processes
    int r; //no. of resource types

    std::vector<std::vector<int>> max, alloc, need; 
    std::vector<int> available;

    //Constructor
    public:
    Bankers(int p, int r):
        p(p), r(r),max(p, std::vector<int>(r)), alloc(p, std::vector<int>(r)), need(p, std::vector<int>(r)),
        available(r)
        {}

    void input(){
        std::cout<<"Enter the Max Matrix: "<<std::endl;
        for(int i=0; i<p; i++){
            for(int j=0; j<r; j++){
                std::cin>>max[i][j];
            }
        }
        std::cout<<"Enter the Allocation Matrix: "<<std::endl;
        for(int i=0; i<p; i++){
            for(int j=0; j<r; j++){
                std::cin>>alloc[i][j];
            }
        }

        //need: 
        for(int i=0; i<p; i++){
            for(int j=0; j<r; j++){
                need[i][j]=max[i][j]-alloc[i][j];
            }
        }
        std::cout<<"Enter available resources"<<std::endl;
        for(int i=0; i<r; i++){
            std::cin>>available[i];
        }
    }

    bool is_safe(){
        std::vector<int> work = available;
        std::vector<bool> finished(p, false);
        std::vector<int> safeSeq;
        
        for(int count=0; count<p; count++){
            bool found =false;
            for(int i=0; i<p; i++){
                if(!finished[i]){
                    //check if need<work
                    bool possible=true;
                    for(int j=0; j<r; j++){
                        if(need[i][j]>work[j]){
                            possible=false;
                            break;
                        }
                    }
                    if(possible){
                        //pretend to allocate i.e. release resources
                        for(int k=0; k<r; k++){
                            work[k]+=alloc[i][k];
                        }
                        finished[i]=true;
                        safeSeq.push_back(i);
                        found=true;
                    }
                }
            }if(!found)break;
        }
    if(safeSeq.size()==p){
        std::cout<<"System is in safe state. Sequence: ";
        for(auto process:safeSeq){
            std::cout<<" "<<process;
        }
        return true;
    }
    else{
        std::cout<<"No safe sequence found";
        return false;
        }
    }

    bool requestResource(int proc, std::vector<int> request){
        //check if request exceeds need
        for(int i=0; i<r; i++){
            if(request[i]>need[proc][i]){
                std::cout<<"Request exceeds need. Cannot allocate"<<std::endl;
                return false;
            }
        }
        //Check if enough resources are available 
        for(int i=0; i<r; i++){
            if(available[i]<request[i]){
                std::cout<<"Not enough resources available. Wait and try again later"<<std::endl;
                return false;
            }
        }
        //pretend to allocate process and check if safe sequence is possible
        for(int j=0; j<r; j++){
                available[j]-=request[j];
                alloc[proc][j]+=request[j];
                need[proc][j]-=request[j];
        }
        if(is_safe()){
            std::cout<<"Request granted"<<std::endl;
            return true;
        }
        else{
            std::cout<<"Request cannot be granted. Rolling back changes"<<std::endl;
            for(int i=0; i<r; i++){
                available[i]+=request[i];
                alloc[proc][i]-=request[i];
                need[proc][i]+=request[i];
            }
            return false;
        }
    }
};

int main(){
    int p, r;
    std::cout<<"Enter the number of processes and resources: ";
    std::cin>>p>>r;
    Bankers b(p, r);
    b.input();
    b.is_safe();
    int pid;
    std::vector<int> req(r);
    std::cout << "\nEnter process ID for request (e.g., 1): ";
    std::cin >> pid;
    std::cout << "Enter request vector: ";
    for(int i=0; i<r; i++) std::cin >> req[i];

    b.requestResource(pid, req);

    return 0;
}