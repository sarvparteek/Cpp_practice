/*!
 * @brief: Detects the number of anagrams in a list of numbers
 * @author: Sarv Parteek Singh
 * @date: July-06-2020
 */

#ifndef CPP_PRACTICE_ANAGRAM_HPP
#define CPP_PRACTICE_ANAGRAM_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cassert>

namespace algorithms
{
    std::vector<int> getDigits(int num)
    {
        std::vector<int> rv;
        while (num != 0)
        {
            rv.push_back(num % 10); // e.g. 1352 % 10 = 2
            num = num/10; // e.g. 1352 / 10 = 135
        }
        return rv;
    }

    bool areAnagrams(int const &num1, int const &num2)
    {
        bool rv(false);
        auto num1_vec = getDigits(num1);
        auto num2_vec = getDigits(num2);
        if (num1_vec.size() != num2_vec.size())
        {
            rv = false;
        }
        else // if both vectors are equal sized
        {
            std::sort(num1_vec.begin(), num1_vec.end());
            std::sort(num2_vec.begin(), num2_vec.end());
            rv = (num1_vec == num2_vec); // if vectors equal each other, numbers are anagrams
        }

        return rv;
    }

    int getAnagramCount(std::vector<int> const &num)
    {
        int rv = 0;
        std::unordered_map<int, int> matched_pair;
        assert(num.size() > 1);
        for (std::size_t i = 0; i < num.size(); ++i)
        {
            /* This will only give the first element, and not all pairs of anagrams. If an element can have multiple
             * anagrams, the following code snippet will have to be updated*/
             auto it = std::find_if(num.begin() + i + 1, num.end(), [&] (auto x)
                                   {
                                       return areAnagrams(num.at(i), x);
                                   });
             if (it != num.end() && matched_pair.find(i) == matched_pair.end())
             {
                 matched_pair[i]                 = it - num.begin();
                 matched_pair[it - num.begin()]  = i;
                 rv                             += 1;
             }
        }

        return rv;
    }

    void testSingleList(std::vector<int> const &vec)
    {
        std::cout << getAnagramCount(vec) << " anagram pair(s) found for ";
        stl::printVector<int>(vec);
    }

    void testAnagrams()
    {
        std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
        testSingleList(std::vector<int> {12, 1001, 21});
        testSingleList(std::vector<int> {12, 1001, 21, 1100, 692, 269, 235, 105});
    }


}
#endif //CPP_PRACTICE_ANAGRAM_HPP
