#include <iostream>
#include <vector>

#include "dmao.hpp"

auto main() -> int {
    dmao::allocator<int>                   alct;
    std::vector<int, dmao::allocator<int>> vec(alct);

    std::cout << "Vector with dmao::allocator" << '\n';

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << '\n';

    return 0;
}
