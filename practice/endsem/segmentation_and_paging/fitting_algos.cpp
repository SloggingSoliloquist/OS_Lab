#include<iostream>
#include<vector> 
#include<string>
std::vector<int> get_fitting(std::string type, std::vector<int> processes, std::vector<int> partitions){
    std::vector<int> allocation(processes.size(), -1);
    for(int i=0; i<processes.size(); i++){
        int idx=-1; 
        for(int j=0; j<partitions.size(); j++){
            if(partitions[j]>=processes[i]){
                if(type=="first-fit"){
                    idx=j;
                    break;
                }
                else if(type=="best-fit"){
                    if(idx==-1||partitions[j]<partitions[idx]){
                        idx=j;
                    }
                }
                else if(type=="worst-fit"){
                    if(idx==-1||partitions[j]>partitions[idx]){
                        idx=j;
                    }
                }
            }
        }
        //allocate if found 
        if(idx!=-1){
            allocation[i]=idx; 
            partitions[idx]-=processes[i];
        }
    }
    std::cout << "Process No.\tProcess Size\tBlock No." << std::endl;
    for (int i = 0; i < processes.size(); i++) {
        std::cout << " " << i + 1 << "\t\t" << processes[i] << "K\t\t";
        if (allocation[i] != -1)
            std::cout << allocation[i] + 1;
        else
            std::cout << "Not Allocated";
        std::cout << std::endl;
    }
    return allocation;
}

int main(){
    std::vector<int> partitions = {100, 500, 200, 300, 600};
    std::vector<int> processes = {212, 417, 112, 426};
    std::vector<int> bf, wf, ff; 
    ff=get_fitting("first-fit", processes, partitions);
    bf=get_fitting("best-fit", processes, partitions);
    wf=get_fitting("worst-fit", processes, partitions);
    return 0;


}