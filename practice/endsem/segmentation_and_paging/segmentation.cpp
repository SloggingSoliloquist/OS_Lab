#include<iostream> 
#include<vector> 

struct SegTable{
    int segNum; 
    int base;
    int limit; 
}; 

void calcPhysicalAddress(int seg_no, int offset, const std::vector<SegTable> segmentation_table){
    //check if seg_no is valid
    if(seg_no>segmentation_table.size()){
        std::cout<<"Invalid segmentation number"<<std::endl;
        return;
    }
    SegTable seg_table_entry = segmentation_table[seg_no];
    if(offset>=seg_table_entry.limit){
        std::cout<<"Invalid offset. Segmentation Fault"<<std::endl;
        return;
    }
    else{
        std::cout<<"Physical address: "<<seg_table_entry.base+offset<<std::endl;
    }

}
int main(){
    std::vector<SegTable> seg_table={
        {0, 1400, 1000},
        {1, 6300, 400},
        {2, 4300, 400},
        {3, 3200, 1100},
        {4, 4700, 1000}
    };

    calcPhysicalAddress(2, 53, seg_table);
    calcPhysicalAddress(3, 852, seg_table);
    calcPhysicalAddress(0, 1222, seg_table);
    return 0;
}