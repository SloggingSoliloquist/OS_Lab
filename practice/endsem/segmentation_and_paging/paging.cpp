#include<iostream>
#include<vector> 

struct pageOffset{
    int pageno;
    int offset;
};

pageOffset calcLogicalAddress(int logical_addr, int page_size){
    pageOffset p; 
    p.pageno = logical_addr/page_size;
    p.offset = logical_addr%page_size; 
    return p;
}

int main(){
    int tot_size, page_size;
    std::cout<<"Enter the total size and page size: ";
    std::cin>>tot_size>>page_size; 
    int num_pages= tot_size/page_size;
    std::vector<int> addresses = {204, 56};
    for(int addr: addresses){
        pageOffset result=calcLogicalAddress(addr, page_size);
        std::cout<<"Results for logical address: "<<addr<<std::endl;
        std::cout<<"Page no: "<<result.pageno;
        std::cout<<" Offset: "<<result.offset;
    }
    return 0;
}