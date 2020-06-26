/*!
 * @brief: Leet code problem: Given an array of integers, return indices of the two numbers such that they add up to a
 *         specific target. you may assume that each input would have exactly one solution, and you may not use the same
 *         element twice.
 * @details: Example:
 *           Given nums = [2, 7, 11, 15], target = 9,
 *           Because nums[0] + nums[1] = 2 + 7 = 9,
 *           return [0, 1].
 * @author: Sarv Parteek Singh
 * @date: June-22-2020
 */

#ifndef CPP_PRACTICE_STL_TWO_SUM_HPP
#define CPP_PRACTICE_STL_TWO_SUM_HPP

#include <vector>
#include <unordered_map>
#include <algorithm>

namespace stl
{
// O(n^2) solution
class TwoSum
{
public:
    std::vector<int> solution(std::vector<int> const &nums, int target)
    {
        std::vector<int> rv;
        auto iter = nums.cbegin();

        for (auto it1 = nums.cbegin(); it1 != nums.cend()-1; ++it1)
        {
            for (auto it2 = it1 + 1; it2 != nums.cend(); ++it2 )
            {
                if (*it1 + *it2 == target)
                {
                    rv.emplace_back(it1 - nums.cbegin());
                    rv.emplace_back(it2 - nums.cbegin());
                    break;
                }
            }

            if (rv.size() > 0)
            {
                break;
            }
            // Fix this:
            /*{
            std::cout << "*iter: " << *iter << ", *(it +1): " << *(it+1) << std::endl;
            auto ret = std::find_if(it+1, nums.cend(), [it, target](int val)
                   {
                       std::cout << " *(it +1): " << *(it+1) << ", val: " << val << std::endl;
                       return *(it+1) + val == target;
                   });
            if (iter && iter != nums.cbegin())
            {
                rv.emplace_back(*iter);
                rv.emplace_back(*it);
                break;
            }
             */
        }
        return rv;
    }
};

// O(n) solution: Adapted from https://www.techiedelight.com/find-pair-with-given-sum-array/
class TwoSum2
{
public:
    std::vector<int> solution(std::vector<int> const &nums, int target)
    {
        std::vector<int> rv;
        std::unordered_map<int, int> map;
        for (std::size_t i = 0; i < nums.size(); i++)
        {
            map[nums.at(i)] = i;
            if (map.find(target - nums.at(i)) != map.end())
            {
                rv.emplace_back(i);
                rv.emplace_back(map[target - nums.at(i)]);
            }
        }
        return rv;
    }
};

} // stl

#endif // CPP_PRACTICE_STL_TWO_SUM_HPP