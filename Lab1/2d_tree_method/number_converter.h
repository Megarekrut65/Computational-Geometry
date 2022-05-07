#pragma once

#include <string>
#include <limits>
#include <sstream>

namespace nc {
    template<typename T>
    class NumberConverter {
    public:
        static const T INF_PLUS;
        static const T INF_MINUS;

        static std::string convert(T value);
    };

    using DoubleConverter = NumberConverter<double>;
}
namespace nc {
    template<typename T>
    const T NumberConverter<T>::INF_PLUS = std::numeric_limits<T>::max();
    template<typename T>
    const T NumberConverter<T>::INF_MINUS = std::numeric_limits<T>::min();

    template<typename T>
    std::string NumberConverter<T>::convert(T value) {
        if (value == INF_PLUS) return "+INF";
        if (value == INF_MINUS) return "-INF";
        std::stringstream stream;
        stream << value;
        return stream.str();
    }
}