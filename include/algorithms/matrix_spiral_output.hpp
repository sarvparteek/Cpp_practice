/*!
 * @brief: Prints a 2D Matrix in spiral form
 * @details: Input:
                    1    2   3   4
                    5    6   7   8
                    9   10  11  12
                    13  14  15  16
            Output:
            1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10

            Input:
                    1   2   3   4  5   6
                    7   8   9  10  11  12
                    13  14  15 16  17  18
            Output:
            1 2 3 4 5 6 12 18 17 16 15 14 13 7 8 9 10 11
 * @author: Sarv Parteek Singh
 * @date: Jan-22-2021
 */

#ifndef CPP_PRACTICE_MATRIX_SPIRAL_OUTPUT_HPP
#define CPP_PRACTICE_MATRIX_SPIRAL_OUTPUT_HPP

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <unordered_map>
#include <cassert>

namespace algorithms
{
    template<typename T>
    class Matrix2DSpiralOutput
    {
    public:
        explicit Matrix2DSpiralOutput(std::vector<std::vector<T>> matrix) : m_matrix(std::move(matrix))
        {
            assert(m_matrix.size() >= 2 && m_matrix.at(0).size() >= 2);
        }

        void updateMatrix(std::vector<std::vector<T>> const &matrix);

        void printMatrix();

    private:
        void printMatrixLayer(std::array<std::size_t, 2> const &row_idx,
                              std::array<std::size_t, 2> const &col_idx);

        void traverseRow(std::array<std::size_t, 2> const &row_idx,
                         std::array<std::size_t, 2> const &col_idx,
                         bool forward);

        void traverseColumn(std::array<std::size_t, 2> const &row_idx,
                            std::array<std::size_t, 2> const &col_idx,
                            bool downward);

        std::vector<std::vector<T>> m_matrix;
    };

    template <typename T>
    void Matrix2DSpiralOutput<T>::updateMatrix(std::vector<std::vector<T>> const &matrix)
    {
        m_matrix = matrix;
    }

    template<typename T>
    void Matrix2DSpiralOutput<T>::printMatrix()
    {
        std::size_t row_min(0), row_max(m_matrix.size() - 1);
        std::size_t col_min(0), col_max(m_matrix.at(0).size() - 1);

        while (true)
        {
            if (row_min > row_max or col_min > col_max)
            {
                break;
            }

            printMatrixLayer(std::array<std::size_t, 2>{row_min, row_max},
                             std::array<std::size_t, 2>{col_min, col_max});
            row_min++;
            row_max--;
            col_min++;
            col_max--;
        }
    }

    template<typename T>
    void Matrix2DSpiralOutput<T>::printMatrixLayer(std::array<std::size_t, 2> const &row_idx,
                                                   std::array<std::size_t, 2> const &col_idx)
   {
        if (row_idx.at(0) == row_idx.at(1))
        {
            /* Traverse from lower column to higher column, because row_min and row_max can only be equal if the
             * number of rows are odd. In that case, the last remaining row will need a forward traversal. A backward
             * traversal is a mirror of a forward traversal, and if only one row is left, that is not possible.
             * */
            traverseRow(row_idx,
                        std::array<std::size_t, 2> {col_idx.at(0), col_idx.at(1) + 1},
                        true);
        }
        else if (col_idx.at(0) == col_idx.at(1))
        {
            /* Traverse from lower row to higher row, because col_min and col_max can only be equal if the
             * number of columns are odd. In that case, the last remaining column will need a downward traversal. An
             * upward traversal is a mirror of a downward traversal, and if only one column is left, that is not
             * possible.
             * */
            traverseColumn(std::array<std::size_t, 2> {row_idx.at(0), row_idx.at(1) + 1},
                           col_idx,
                           true);
        }
        else
        {
            /*
             * Steps
             * 1) In the lower row, go from lower column to higher column - 1
             * 2) In the higher column, go from lower row to higher row -1
             * 3) In the higher row, go from higher column to lower column -1
             * 4) In the lower column, go from higher row to lower row - 1
             *  */
            traverseRow(row_idx, col_idx, true); // Step 1
            traverseColumn(row_idx, col_idx, true); // Step 2
            traverseRow(row_idx, col_idx, false); // Step 3
            traverseColumn(row_idx, col_idx, false); // Step 4
        }
    }

    template<typename T>
    void Matrix2DSpiralOutput<T>::traverseRow(std::array<std::size_t, 2> const &row_idx,
                                              std::array<std::size_t, 2> const &col_idx,
                                              bool forward)
    {
        if (forward)
        {
            // Go from lower column to higher column - 1
            for (auto i = col_idx.at(0); i < col_idx.at(1) ; ++i)
            {
                std::cout << m_matrix.at(row_idx.at(0)).at(i) << " ";
            }
        }
        else
        {
            // Go from higher column to lower column + 1
            for (auto i = col_idx.at(1); i > col_idx.at(0); --i)
            {
                std::cout << m_matrix.at(row_idx.at(1)).at(i) << " ";
            }
        }
    }

    template <typename T>
    void Matrix2DSpiralOutput<T>::traverseColumn(std::array<std::size_t, 2> const &row_idx,
                                                 std::array<std::size_t, 2> const &col_idx,
                                                 bool downward)
    {
        if (downward)
        {
            // Go from lower row to higher row - 1
            for (auto i = row_idx.at(0); i < row_idx.at(1) ; ++i)
            {
                std::cout << m_matrix.at(i).at(col_idx.at(1)) << " ";
            }
        }
        else
        {
            // Go from higher row to lower row + 1
            for (auto i = row_idx.at(1); i > row_idx.at(0) ; --i)
            {
                std::cout << m_matrix.at(i).at(col_idx.at(0)) << " ";
            }
        }
    }

    void testMatrix2DSpiralPrint()
    {
        Matrix2DSpiralOutput<int> m(std::vector<std::vector<int>>({ { 1, 2 , 3 ,  4},
                                                                       { 5, 6 , 7 ,  8},
                                                                       { 9, 10, 11, 12},
                                                                       {13, 14, 15, 16} }));
        std::cout << std::endl;
        m.printMatrix();

        m.updateMatrix(std::vector<std::vector<int>>({ { 1, 2 , 3 ,  4,  5,  6},
                                                         { 7 , 8, 9, 10, 11, 12},
                                                         {13, 14, 15, 16, 17, 18}}));
        std::cout << std::endl;
        m.printMatrix();
    }

}

#endif //CPP_PRACTICE_MATRIX_SPIRAL_OUTPUT_HPP
