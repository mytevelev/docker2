#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <future>
#include <string>

using namespace std;

void get_min_element_idx(vector<int> vec, size_t from_idx, promise<size_t> min_idx) {
    const auto begin = vec.begin() + from_idx;
    vector<int>::iterator result = min_element(begin, vec.end());
    min_idx.set_value(distance(vec.begin(), result));
}

void swap_elements(size_t first_idx, size_t second_idx, vector<int>& vec) {
    swap(vec[first_idx], vec[second_idx]);
}

void print_vector(const vector<int> vec) {
    for (auto& el : vec) {
        cout << el << " ";
    };
}

int main(int argc, const char* argv[]) {

   // cout << this_thread::get_id() << endl;
    vector<int> test_vec = { 44, 55, 12, 42, 94, 18, 6, 67 };
    cout << "Before random\n";
    print_vector(test_vec);

    for (size_t i = 0; i < test_vec.size(); ++i) 
    {
        // вариант с promise
        promise<size_t> min_idx_promise;
        future<size_t> f{ min_idx_promise.get_future() };
        thread t{ std::move(get_min_element_idx), test_vec, i, std::move(min_idx_promise) };
        t.detach();
        const size_t min_idx{ f.get() };
        swap_elements(i, min_idx, test_vec);
    }

    cout << "\nAfter sort:" << endl;
    print_vector(test_vec);

    return 0;
}