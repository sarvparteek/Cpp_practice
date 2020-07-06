//
// Created by sarvp on 6/22/2020.
//

#ifndef CPP_PRACTICE_VECTOR_ITERATION_HPP
#define CPP_PRACTICE_VECTOR_ITERATION_HPP

#endif //CPP_PRACTICE_VECTOR_ITERATION_HPP

#include <vector>

namespace stl
{
    template <typename T>
    void printVector(std::vector<T> const &vec)
    {
        std::size_t i = 0;
        for (i = 0; i < vec.size() - 1; ++i)
        {
            std::cout << vec.at(i) << ", ";
        }
        std::cout << vec.at(i) << std::endl;
    }

    int vec_iteration_test()
    {
        std::cout << "--- Technique 1 ---" << std::endl;
        std::vector<int> vec{1,2,4,5,6,2024,20};
        for (auto &x: vec)
        {
            std::cout << x << std::endl;
        }

        std::cout << "--- Technique 2 ---" << std::endl;
        for (auto it = vec.cbegin(); it != vec.cend(); ++it)
        {
            std::cout << *it << std::endl;
        }

        std::cout << "--- Technique 3 ---" << std::endl;
        for (std::size_t i = 0; i < vec.size(); i++)
        {
            std::cout << vec.at(i) << std::endl; // vec.at(i) is safer than vec[i] as the latter does not check for
                                                 // out -of-range.
        }

        return 0;
    }
}
