/*!
 * @brief Tests multiple threads with resource sharing amongst them
 * @author Sarv Parteek Singh
 * @date July-02-2020
 */

#ifndef CPP_PRACTICE_THREADING_HPP
#define CPP_PRACTICE_THREADING_HPP

#include <iostream>
#include <thread>

namespace threading
{
    void func(int const &id)
    {
        std::cout << "Creating thread " << id << "using function object" << std::endl;
    }

    class Functor
    {
    public:
        Functor(int const &id): m_id(id)
        {
            std::cout << "Creating" << m_id << "using class object" << std::endl;
        }

        /* Default move and copy constructors and assignment operators */
        Functor(Functor const &o) = default;
        Functor(Functor &&o) = default;
        Functor& operator=(Functor const &o) = default;
        Functor& operator=(Functor &&o) = default;

        ~Functor()
        {
            std::cout << "Destroying " << m_id << std::endl;
        }

        void operator()(int const &id)
        {
            std::cout << "Creating thread with id " << id << " and m_id = " << id << std::endl;
        }
    private:
        int m_id;
    };

    // TODO - 2020-07-02 Complete later (use C++ Concurrency in Action for reference)

    void testThreading()
    {
        //std::thread t(func, 1);
    }
}
#endif //CPP_PRACTICE_THREADING_HPP
