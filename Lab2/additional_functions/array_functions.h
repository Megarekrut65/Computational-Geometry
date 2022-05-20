#pragma once

#include <vector>
#include <stdexcept>

namespace af {
    template<typename T>
    T remove_random_item(std::vector<T> &arr);
}
namespace af {
    template<typename T>
    T remove_random_item(std::vector<T> &arr) {
        if (arr.empty()) {
            throw std::invalid_argument{"Can't remove item from empty array!"};
        }
        std::size_t index = rand() % arr.size();
        T item = arr[index];
        arr.erase(arr.begin() + index);
        return item;
    }
}
