#include<iostream>
#include<vector>
#include<thread>

void find_max_el(std::vector<int> &elements, int start, int end, int &max){
    int max_ind=start;
    for(int i=start+1; i<end; i++){
        if(elements[i]>elements[max_ind])max_ind=i;
    }
    max=elements[max_ind];
}

int main()
{
    int n;
    std::cout<<"Enter the number of elements: ";
    std::cin>>n;
    std::vector<int> arr(n);
    std::cout<<"Enter the array: \n";
    for(int i=0; i<n; i++){
        std::cin>>arr[i];
    }

    int num_threads=4;
    int chunk= n/num_threads;
    int start, end;
    std::vector<std::thread> threads;
    std::vector<int> max(num_threads);
    for(int i=0; i<num_threads; i++){
        start=i*chunk;
        end=(i==num_threads-1)?n:start+chunk;
        threads.push_back(std::thread(find_max_el, std::ref(arr), start, end, std::ref(max[i])));
    }

    for(auto &thread:threads){
        thread.join();
    }
    int total_max=0;
    for(int i=1; i<num_threads;i++){
        if(max[i]>max[total_max]){
            total_max=i;
        }
    }
    std::cout<<max[total_max];
}