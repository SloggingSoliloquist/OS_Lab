#include<cmath>
#include<algorithm>
#include<iostream>
#include<vector> 

int calculateTHM(int head, std::vector<int> requests){
    int curr=head;
    int thm= 0;
    for(int next:requests){
        thm+=abs(curr-next);
        curr=next;
    }
    return thm;
}

int fcfs(int head, std::vector<int> requests){
    std::cout<<"FCFS\n";
    int thm = calculateTHM(head, requests);
    return thm;
}

int srtf(int head, std::vector<int> requests){
    std::vector<int> sequence; 
    std::vector<bool> is_visited(requests.size(), false);
    int curr=head;
    for(int i=0; i<requests.size(); i++){
        int min_dist = 1000; 
        int min_ind=-1;
        for(int j=0; j<requests.size(); j++){
            if(!is_visited[j] && abs(curr-requests[j])<min_dist){
                min_dist=abs(curr-requests[j]);
                min_ind=j;
            }
        }
        is_visited[min_ind]=true;
        curr=requests[min_ind];
        sequence.push_back(requests[min_ind]);
    }
    int thm = calculateTHM(head, sequence);
    return thm;
}

int scan_look(int head, bool is_look, std::vector<int> requests){
    std::sort(requests.begin(), requests.end());
    std::vector<int> left, right, sequence; 
    for(auto el:requests){
        if(el<head) left.push_back(el);
        else right.push_back(el);
    }
    std::sort(left.rbegin(), left.rend());
    for(auto l:left) sequence.push_back(l); 
    if(!is_look)
    sequence.push_back(0);
    for(auto r:right)sequence.push_back(r);
    int thm = calculateTHM(head, sequence);
    return thm;
}

int cscan_clook(int head, bool is_look, std::vector<int> requests){
    std::sort(requests.begin(), requests.end()); 
    std::vector<int> right, left, sequence; 
    int thm;
    for(auto el:requests){
        if(el<head)left.push_back(el);
        else right.push_back(el);
    }
    for(auto r:right) sequence.push_back(r);
    if(!is_look) {sequence.push_back(199);
        sequence.push_back(0);}
    for(auto l:left) sequence.push_back(l); 
    int thm_before = calculateTHM(head, sequence); 
    if(is_look){
        thm= thm_before-abs(right.back()-left.front()); 
    }
    else{
        thm = thm_before-199;
    }
    return thm;
}

int main(){
    int head=53; 
    std::vector<int> requests={98, 183, 37, 122, 14, 124, 65, 67};
    std::cout<<fcfs(head, requests)<<std::endl;
    std::cout<<srtf(head, requests)<<std::endl;
    std::cout<<scan_look(head,0, requests)<<std::endl;
    std::cout<<scan_look(head,1, requests)<<std::endl;
    std::cout<<cscan_clook(head,0, requests)<<std::endl;
    std::cout<<cscan_clook(head,1, requests)<<std::endl;
    return 0;
}