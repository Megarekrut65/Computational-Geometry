#include "menu.h"

namespace menu {
    using namespace tree_2d;

    void Menu::run() {
        points = get_points();
        Tree tree{points};
        std::cout << "2d-tree was created!" << std::endl;
        int index = 1;
        while (true) {
            std::cout << "Enter 1 to show tree or any other key to continue" << std::endl;
            if (_getch() == '1' && _getch()) std::cout << "2d-tree " << tree << std::endl;
            QueryRegion region = get_region();
            Set res = tree.search(region);
            std::cout << "Result: " << res << std::endl;
            save_to_current_file(index++, region, res);
            std::cout << "Enter 1 to exit or any other key to repeat" << std::endl;
            if (_getch() == '1' && _getch()) break;
        }
        std::cout << "\nExit..." << std::endl;
    }

    std::string Menu::get_input_file() {
        while (true) {
            std::cout << "Enter number to select input file:\n"
                      << "1)" << general_file_name << "\n2)" << practice_file_name << "\n3)Enter own input file\n";
            switch (_getch()) {
                case '1':{
                    _getch();
                    return general_file_name;
                }

                case '2': {
                    _getch();
                    return practice_file_name;
                }
                case '3': {
                    _getch();
                    std::cout << "Enter file name in folder 'input': ";
                    std::string name;
                    std::getline(std::cin, name);
                    return name;
                }
                default:
                    std::cout << "Incorrect key was pressed!" << std::endl;
            }
        }
    }

    tree_2d::Set Menu::get_points() {
        Set set;
        while (true) {
            current_file_name = get_input_file();
            set = pr::read_points<double>(input_path + current_file_name);
            if (!set.empty()) {
                break;
            }
            std::cout << "File empty or not found!" << std::endl;
        }
        std::cout << "Points: " << set << std::endl;
        return std::move(set);
    }

    tree_2d::QueryRegion Menu::get_region() {
        Area region;
        while (true) {
            std::cout << "Enter query region(You can use +INF and -INF as infinity)." << std::endl;
            std::cout << "x1: ";
            region.point1.x = read_number();
            std::cout << "x2: ";
            region.point2.x = read_number();
            std::cout << "y1: ";
            region.point1.y = read_number();
            std::cout << "y2: ";
            region.point2.y = read_number();
            if (!region.is_empty()) break;
            std::cout << "Entered region is empty!" << std::endl;
        }
        std::cout << "Query region: " << region << std::endl;
        return std::make_shared<Area>(region);
    }

    double Menu::read_number() {
        while (true) {
            std::string input;
            std::getline(std::cin, input);
            if (input == "+INF") return nc::DoubleConverter::INF_PLUS;
            if (input == "-INF") return nc::DoubleConverter::INF_MINUS;
            char *error;
            double number;
            if (input.find(',') != std::string::npos)
                input.replace(input.find(','), 1, ".");
            number = strtod(input.c_str(), &error);
            if (*error == 0) return number;
            std::cout << "Incorrect data!" << std::endl;
        }
    }

    void Menu::save_to_current_file(int index, const QueryRegion &region, const Set &res) {
        std::ofstream out{output_path + std::to_string(index) + "_" + current_file_name};
        out << "Points: " << points << std::endl;
        out << "Query region: " << *region << std::endl;
        out << "Result: " << res << std::endl;
        out.close();
        std::cout << "Result was added to file '" << index << "_" << current_file_name
                  << "' in folder 'output'" << std::endl;
    }
}

