#pragma once

namespace pa{
    template<typename One, typename Two>
    class Pair{
    public:
        One one;
        Two two;

        Pair(const One& one, const Two& two);

        Pair();
    };
}
namespace pa{
    template<typename One, typename Two>
    Pair<One, Two>::Pair() = default;

    template<typename One, typename Two>
    Pair<One, Two>::Pair(const One& one, const Two& two):one(one), two(two) {}
}