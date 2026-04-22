#include<iostream>
#include<algorithm>
#include<vector>

void display_frames(std::vector<int> frames, int curr){
    std::cout<<curr<<"->";
    for(auto frame: frames){
        std::cout<<" "<<frame;
    }
    std::cout<<std::endl;
}

int findOptIdx(std::vector<int> pages, std::vector<int> frames, int currPos){
    int farthest=currPos; 
    int framePos=-1;
    for(int i=0; i<frames.size(); i++){
        int j=0;
        for(j=currPos+1; j<pages.size(); j++){
            if(pages[j]==frames[i]){
                if(j>farthest){
                    farthest=j; 
                    framePos=i;
                }
                break;
            }
        }
        //if the loop didn't break, i.e. the element does not occur again, then replace the page
        if(j==pages.size()){
            return i;
        }
    }
    return (framePos==-1)?0:framePos;
}

int opt(std::vector<int> pages, int capacity){
    std::vector<int> frames;
    int page_faults =0; 
    for(int i=0; i<pages.size(); i++){
        //find current element in frames
        int curr= pages[i];
        auto it=std::find(frames.begin(), frames.end(), curr);
        if(it==frames.end()){
            page_faults++;
            if(frames.size()<capacity){
                frames.push_back(curr);
            }
            else{
                int targetIdx=findOptIdx(pages, frames, curr);
                frames[targetIdx]=curr;
            }
        }
        display_frames(frames, curr);
    }
    return page_faults;
}

int main(){
    int capacity;
    std::cout<<"Enter the capacity: ";
    std::cin>>capacity; 
    std::vector<int> pages={7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n=pages.size()/sizeof(pages[0]);
    int totalFaults = opt(pages, capacity);
    std::cout<<"NO of page faults: "<<totalFaults;
}