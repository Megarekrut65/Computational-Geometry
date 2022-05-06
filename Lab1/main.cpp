//3. Регіональний пошук. Метод 2-d дерева.
#include <iostream>
#include "2d_tree/binary_tree.h"
#include "2d_tree/tree_2d.h"

using namespace tree_2d;
int main() {
    Set set;
    set.push_back(point::Point{5,1});
    set.push_back(point::Point{2,2});
    set.push_back(point::Point{9,3});
    set.push_back(point::Point{1,4});
    Tree tree{set};
    return 0;
}
