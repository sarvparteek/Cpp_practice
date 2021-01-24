/*!
 * @brief Computes largest sum of k successive elements in an n-dimensional vector (k <= n)
 * @details: Reference - https://www.geeksforgeeks.org/window-sliding-technique/
 * @author Sarv Parteek Singh
 * @date Jan-17-2021
 */

#ifndef CPP_PRACTICE_SUB_VECTOR_SUM_HPP
#define CPP_PRACTICE_SUB_VECTOR_SUM_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <numeric>

namespace algorithms
{
    template <typename T>
    class SubVectorSum
    {
    public:
        SubVectorSum(std::size_t k, std::vector<T> v): m_k(k), m_v(v)
        {
            computeWithNestedLoops();
            computeWithSlidingWindow();
        }

        T getSum() const;

        void setSubVectorLength(T const &k);

        void setVector(std::vector<T> const &v);

    private:
        std::vector<T> m_v;
        std::size_t m_k; // Number of elements to be summed
        T m_largest_sum;

        void computeWithNestedLoops();

        void computeWithSlidingWindow();
    };

    template <typename T>
    T SubVectorSum<T>::getSum() const
    {
        return m_largest_sum;
    }

    template <typename T>
    void SubVectorSum<T>::setSubVectorLength(T const &k)
    {
        m_k = k;
        computeWithNestedLoops();
        computeWithSlidingWindow();
    }

    template <typename T>
    void SubVectorSum<T>::setVector(std::vector<T> const &v)
    {
        m_v = v;
        computeWithNestedLoops();
        computeWithSlidingWindow();
    }

    template <typename T>
    void SubVectorSum<T>::computeWithNestedLoops()
    {
        auto start_time = std::chrono::system_clock::now();

        m_largest_sum = 0;
        for (auto it = m_v.cbegin(); it != m_v.cend(); ++it)
        {
            auto end_it = (m_v.cend() - it < m_k) ? m_v.cend() : it + m_k;
            auto sum    = std::accumulate(it, end_it, T());
            m_largest_sum = (m_largest_sum > sum) ? m_largest_sum: sum;
        }

        auto end_time = std::chrono::system_clock::now();
        auto delta_time_ms = (std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count())/
                              1000.0;
        std::cout << "Nested loops running time for a vector of length " << m_v.size() << " = " << delta_time_ms
                  << " ms = " << delta_time_ms/m_v.size() * 1000.0 << " ns/element" << std::endl;
    }

    template <typename T>
    void SubVectorSum<T>::computeWithSlidingWindow()
    {
        auto start_time = std::chrono::system_clock::now();

        auto window_sum = std::accumulate(m_v.cbegin(), m_v.cbegin() + m_k, T());
        m_largest_sum = window_sum;
        for (auto it = m_v.cbegin() + m_k; it != m_v.cend(); ++it)
        {
            auto temp = it - m_k;
            window_sum = window_sum - *(it - m_k) + *it;
            m_largest_sum = (m_largest_sum > window_sum) ? m_largest_sum: window_sum;
        }

        auto end_time = std::chrono::system_clock::now();
        auto delta_time_ms = (std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count())/
                             1000.0;
        std::cout << "Sliding window running time for a vector of length " << m_v.size() << " = " << delta_time_ms
                  << " ms = " << delta_time_ms/m_v.size() * 1000.0 << " ns/element" << std::endl;
    }

    void testSubVectorSum()
    {
        std::cout << std::endl;
        SubVectorSum<int> s(4, std::vector<int>({1, 4, 2, 10, 23, 3, 1, 0, 20}));
        std::cout << "Largest sub-vector sum: " << s.getSum() << std::endl;
    }
}

#endif // CPP_PRACTICE_SUB_VECTOR_SUM_HPP
