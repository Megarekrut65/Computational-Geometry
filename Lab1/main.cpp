//3. Регіональний пошук. Метод 2-d дерева.
#include <iostream>
#include "2d_tree/tree_2d.h"

using namespace tree_2d;

int main() {
    Set set;
    set.push_back(Point{2,10, "p1"});
    set.push_back(Point{4,6, "p2"});
    set.push_back(Point{5,15, "p3"});
    set.push_back(Point{7,8, "p4"});

    set.push_back(Point{10,11, "p5"});
    set.push_back(Point{13,16, "p6"});
    set.push_back(Point{14,6, "p7"});
    set.push_back(Point{15,13, "p8"});
    set.push_back(Point{17,9, "p9"});
    Tree tree{set};
    std::cout << tree << std::endl;
    return 0;
}
