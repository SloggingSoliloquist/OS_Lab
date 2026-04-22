#include <iostream>
#include <thread>
#include <vector>

void merge(std::vector<int> &arr, int left, int mid, int right) {
    std::vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = left; k <= right; k++)
        arr[k] = temp[k - left];
}

void merge_sort(std::vector<int> &arr, int left, int right, int depth) {
    if (left >= right) return;

    int mid = (left + right) / 2;

    if (depth > 0) {
        // spawn two threads for left and right halves
        std::thread t1(merge_sort, std::ref(arr), left, mid, depth - 1);
        std::thread t2(merge_sort, std::ref(arr), mid + 1, right, depth - 1);
        t1.join();
        t2.join();
    } else {
        // below threshold, just sort sequentially(i.e. recursively without creating new threads)
        //this is cos if you create  threads at every split point, number of threads grows exponentially.
        //you can control the depth, it's passed as a parameter.
        merge_sort(arr, left, mid, 0);
        merge_sort(arr, mid + 1, right, 0);
    }

    merge(arr, left, mid, right);
}

int main() {
    int n;
    std::cout << "Enter number of elements: ";
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) std::cin >> arr[i];

    merge_sort(arr, 0, n - 1, 3);  // depth 3 = at most 2^3 = 8 threads

    std::cout << "Sorted: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";
}