#include <iostream>
#include "triangulation_drawing/triangulation_drawer.h"

//C - show/hide circles
//S - take screenshot
//Enter - add next point
//Escape - close window
int main() {
    srand(time(nullptr));
    drawer::TriangulationDrawer d({dt::Point(-16, -3), dt::Point(7, 13), dt::Point(16, -15)},
                                  {dt::Point(-6, -2), dt::Point(0, -4), dt::Point(4, 1), dt::Point(1, 3),
                                   dt::Point(6, 7), dt::Point(8, -1), dt::Point(10, -5)},
                                  21);
    d.run();
    return 0;
}
