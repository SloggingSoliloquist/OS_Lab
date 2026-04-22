#include<iostream>
#include<vector> 
#include<algorithm>

void displayFrames(int curr, std::vector<int> frames, int capacity){
        std::cout<<curr<<"->";
        for(auto frame:frames){
            std::cout<<frame<<" ";
        }
        std::cout<<std::endl;
}

int findLruIdx(std::vector<int> pages, std::vector<int> frames, int currPos){
    int farthest=currPos; 
    int framePos=-1;
    for(int i=0; i<frames.size(); i++){
        for(int j=currPos-1; j>=0; j--){
            if(pages[j]==frames[i]){
                if(j<farthest){
                    farthest=j;
                    framePos=i;
                }
                break;
            }
        }
    }
    return (framePos==-1)?0:framePos;
}

int lru(std::vector<int> pages,int capacity){
    std::vector<int> frames; 
    int page_faults=0;
    for(int i=0; i<pages.size(); i++){
        int curr=pages[i]; 
        auto it=std::find(frames.begin(), frames.end(), curr);
        if(it==frames.end()){
            page_faults++;
            if(frames.size()<capacity){
                frames.push_back(curr);
            }
            else{
                int lruIdx = findLruIdx(pages, frames, i);
                frames[lruIdx]=curr;
            }
        }
        displayFrames(curr, frames, capacity);
    }
    return page_faults;
}
int main(){
    int capacity; 
    std::cout<<"Enter the capacity: ";
    std::cin>>capacity;
    std::vector<int> pages= {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n=pages.size()/sizeof(pages[0]);
    int totalFaults = lru(pages, capacity);
    std::cout<<"NO of page faults: "<<totalFaults;
    return 0;
}