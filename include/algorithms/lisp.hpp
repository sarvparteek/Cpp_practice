/*!
 * @brief Computes results for lisp expressions
 * @author Sarv Parteek Singh
 * @date July-12-2020
 */

#ifndef CPP_PRACTICE_LISP_HPP
#define CPP_PRACTICE_LISP_HPP

#include <iostream>
#include <sstream>
#include <string>

namespace algorithms
{
    /*!
     * @brief Computes the floating point answer for a single lisp instruction
     * @param[in] expr Lisp expression to be evaluated
     * @return Result of the computation
     * @details This function only computes
     *          "( + arg1 arg2 )" -> arg1 + arg2
     *          "( - arg1 arg2 )" -> arg1 - arg2
     *          "( * arg1 arg2 )" -> arg1 * arg2
     *          "( / arg1 arg2 )" -> arg1 / arg2
     * @note This function assumes that expressions would always be of the format listed in @details
     */
    float computeSingleInstruction(std::string expr)
    {
        std::stringstream ss(expr);
        float rv(0.0);
        char op;
        float arg1, arg2;
        ss >> op >> arg1 >> arg2;
        if (op == '+')
        {
            rv = arg1 + arg2;
        }
        else if (op == '-')
        {
            rv = arg1 - arg2;
        }
        else if (op == '*')
        {
            rv = arg1 * arg2;
        }
        else if (op == '/')
        {
            rv = arg1 / arg2;
        }
        return rv;
    }

    /*!
     * @brief Computes the floating point answer for a lisp expression
     * @param[in] lisp_expression Input lisp expression
     * @return Result of the computation
     * @note The format is :
     *       1) Every number/paranthesis/operator is separated by one space on either side
     *       2) Only the four basic operations (+,-,*,/) are allowed in the input expression
     */
    float computeLisp(std::string lisp_expression)
    {
        while (true)
        {
            auto start_idx = 0;
            auto end_idx   = 0;
            for (std::size_t i = 0; i < lisp_expression.size(); ++i)
            {
                char ch = lisp_expression.at(i);
                if (ch == '(')
                {
                    start_idx = i;
                }
                if (ch == ')')
                {
                    end_idx = i;
                    break;
                }
            }

            if (start_idx == 0 and end_idx == 0)
            {
                break;
            }

            auto val = computeSingleInstruction(lisp_expression.substr(start_idx + 2, end_idx - start_idx -3));
            lisp_expression = std::string(std::string(lisp_expression.substr(0, start_idx) + std::to_string(val))
                                          + lisp_expression.substr(end_idx + 1, lisp_expression.size() - end_idx));

        }
        return std::stof(lisp_expression);
    }

    void testLisp()
    {
        std::string lisp = "( - ( + 3 3 ) 2 )";
        std::cout << "\n Lisp output for " << lisp << " = " << computeLisp(lisp) << std::endl;
    }
}

#endif //CPP_PRACTICE_LISP_H
