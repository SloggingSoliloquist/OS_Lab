#include<iostream>
#include<thread>
#include<vector>

void summer(std::vector<int> &arr, int start, int end, int &sum){
    sum=0;
    for(int i=start; i<end; i++){
        sum+=arr[i];
    }
}

int main(){
    int n;
    std::cout<<"Enter the number of elements: ";
    std::cin>>n;
    std::vector<int> elements(n);
    for(auto &p:elements){
        std::cout<<"Enter element; ";
        std::cin>>p;
    }
    int sum1, sum2;
    std::thread t1(summer, std::ref(elements), 0, n/2, std::ref(sum1));//whenever you pass stuff by reference, use std::ref
    std::thread t2(summer, std::ref(elements), n/2, n, std::ref(sum2));
    t1.join();
    t2.join();
    std::cout<<sum1+sum2;
}