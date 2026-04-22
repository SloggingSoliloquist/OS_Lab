#include<iostream>
#include<vector>
#include<algorithm>

void displayFrames(std::vector<int> frames, int curr){
    std::cout<<curr<<"->";
    for(auto frame:frames){
        std::cout<<" "<<frame;
    }
    std::cout<<std::endl;
}

int fifo(std::vector<int> pages, int capacity){
    std::vector<int> frames; 
    int page_faults=0; 
    int nextPos=0;
    for(int i=0; i<pages.size(); i++){
        int curr=pages[i];
        auto it=std::find(frames.begin(), frames.end(), curr);
        if(it==frames.end()){
            page_faults++;
            if(frames.size()<capacity){
                frames.push_back(curr);
            }
            else{
                frames[nextPos]=curr; 
                nextPos=(nextPos+1)%capacity;
            }
        }
        displayFrames(frames, curr);
    }
    return page_faults;
}

int main(){
    int capacity;
    std::cout<<"Enter the capacity: ";
    std::cin>>capacity; 
    std::vector<int> pages={7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n=pages.size()/sizeof(pages[0]);
    int totalFaults = fifo(pages, capacity);
    std::cout<<"NO of page faults: "<<totalFaults;
}