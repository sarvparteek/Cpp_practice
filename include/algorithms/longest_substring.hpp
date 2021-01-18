/*!
 * @brief: Given a string s, find the length of the longest substring without repeating characters.
 * @details: Example 1:
 *              Input: s = "abcabcbb"
 *              Output: 3
 *              Explanation: The answer is "abc", with the length of 3.
 *           Example 2:
 *              Input: s = "bbbbb"
 *              Output: 1
 *              Explanation: The answer is "b", with the length of 1.
 *           Example 3:
 *              Input: s = "pwwkew"
 *              Output: 3
 *              Explanation: The answer is "wke", with the length of 3.
 *              Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *           Example 4:
 *              Input: s = ""
 *              Output: 0
 *           Constraints:
 *              0 <= s.length <= 5 * 10^4
 *              s consists of English letters, digits, symbols and spaces.
 * @author: Sarv Parteek Singh
 * @date: Dec-28-2020
 */

#ifndef CPP_PRACTICE_LONGEST_SUBSTRING_HPP
#define CPP_PRACTICE_LONGEST_SUBSTRING_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

namespace algorithms
{
    class LongestSubstring
    {
    public:
        // Use std::string::size_type for size because it guarantees to capture any string size, which int etc. do not
        std::pair<std::string, std::string::size_type> solution1(std::string s)
        {
            // Time complexity: O(n^2)
            std::string longest_substring;
            for (std::string::size_type i = 0; i < s.size(); ++i)
            {
                // If the number of iterations left are <= size of the longest substring, no point going through them
                if (s.size() - i <= longest_substring.size())
                {
                    break;
                }

                std::string curr_string = "";
                for (std::string::size_type j = i; j < s.size(); ++j )
                {
                    auto pos = curr_string.find(s.at(j));
                    if (pos == std::string::npos) // if no match is found, then add this character to the string
                    {
                        curr_string += s.at(j);
                    }
                    else
                    {
                        break;
                    }
                }

                if (curr_string.size() > longest_substring.size())
                {
                    longest_substring = curr_string;
                }
            }
            return std::make_pair(longest_substring, longest_substring.size());
        }

        int solution2(std::string s)
        {
            // Sourced from solutions. Time complexity: O(n)
            std::map<char, int> char_map;
            int start_idx = -1;
            uint32_t max_length = 0;
            for (auto i = 0; i < s.size(); ++i)
            {
                // If this character already exists as a key, set the start of a new substring as this index
                if (char_map.count(s.at(i)) == 1) // all entries in a map are unique. So count is either 0 or 1
                {
                    start_idx = std::max(start_idx, i);
                }
                char_map[s.at(i)] = i;
                max_length = std::max(max_length, static_cast<uint32_t>(i - start_idx));
            }
            return max_length;
        }
    };

    void testLongestSubstring()
    {
        LongestSubstring ls;
        std::string s("hadippa");
        auto sol = ls.solution1(s);
        auto sol2 = ls.solution2(s);
        std::cout << "Longest substring (value, length) in " << s << " is ("
                   << sol.first << ", "  << sol.second << ")" << std::endl;
        std::cout << "Solution 2 length: " << sol2 << std::endl;

        s = "kinkartavyavimudh";
        sol = ls.solution1(s);
        sol2 = ls.solution2(s);
        std::cout << "Longest substring (value, length) in " << s << " is ("
                  << sol.first << ", "  << sol.second << ")" << std::endl;
        std::cout << "Solution 2 length: " << sol2 << std::endl;

        s = "";
        sol = ls.solution1(s);
        sol2 = ls.solution2(s);
        std::cout << "Longest substring (value, length) in " << s << " is ("
                  << sol.first << ", "  << sol.second << ")" << std::endl;
        std::cout << "Solution 2 length: " << sol2 << std::endl;

        s = " ";
        sol = ls.solution1(s);
        sol2 = ls.solution2(s);
        std::cout << "Longest substring (value, length) in " << s << " is ("
                  << sol.first << ", "  << sol.second << ")" << std::endl;
        std::cout << "Solution 2 length: " << sol2 << std::endl;
    }
}
#endif //CPP_PRACTICE_LONGEST_SUBSTRING_HPP
