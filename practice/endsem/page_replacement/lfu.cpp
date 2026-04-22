#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

void displayFrames(std::vector<int> frames, int curr){
    std::cout<<curr<<"->";
    for(auto frame:frames){
        std::cout<<" "<<frame;
    }
    std::cout<<std::endl;
}

int findLFUIdx(std::vector<int> frames, std::unordered_map<int, int>&pageCounts){
    int minCount=100; 
    int frameRes=-1; 
    for(int i=0; i<frames.size(); i++){
        if(pageCounts[frames[i]]<minCount){
            minCount=pageCounts[frames[i]];
            frameRes=i;
        }
    }
    return (frameRes==-1)?0:frameRes;
}

int lfu(std::vector<int>pages, int capacity){
    std::unordered_map<int, int> counts; 
    int page_faults=0;
    std::vector<int> frames;
    for(int i=0; i<pages.size(); i++){
        int curr= pages[i];
        auto it=std::find(frames.begin(), frames.end(), curr);
        counts[curr]++;
        if(it==frames.end()){
            page_faults++;
            if(frames.size()<capacity){
                frames.push_back(curr);
            }
            else{
                int targetIdx=findLFUIdx(frames, counts);
                frames[targetIdx]=curr;
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
    int totalFaults = lfu(pages, capacity);
    std::cout<<"NO of page faults: "<<totalFaults;
}