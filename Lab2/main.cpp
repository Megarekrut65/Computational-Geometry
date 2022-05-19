#include <iostream>
#include "triangulation_drawing/triangulation_drawer.h"


int main() {
    srand(time(nullptr));
    drawer::TriangulationDrawer d(
            {dt::Point(15,-18),dt::Point(24,24),dt::Point(-15,21)},
            {dt::Point(12,11),dt::Point(3,8),dt::Point(6,18),dt::Point(12,3)},
            7);
    d.run();
    return 0;
}
