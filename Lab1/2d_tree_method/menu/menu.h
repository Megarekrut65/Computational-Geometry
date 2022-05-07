#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include "../points_reader.h"
#include "../2d_tree/tree_2d.h"
#include "../number_converter.h"

namespace menu {
    class Menu {
    private:
        const std::string input_path = "../input/";
        const std::string output_path = "../output/";
        const std::string practice_file_name = "input_from_practice.txt";
        const std::string general_file_name = "input.txt";
        std::string current_file_name;
        tree_2d::Set points;

        std::string get_input_file();

        tree_2d::Set get_points();

        tree_2d::QueryRegion get_region();

        double read_number();

        void save_to_current_file(int index, const tree_2d::QueryRegion &region, const tree_2d::Set &res);

    public:
        void run();
    };
}