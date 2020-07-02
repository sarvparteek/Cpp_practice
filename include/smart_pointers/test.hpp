/*!
 * @brief: Implement a shared pointer using a raw pointer
 * @author: Sarv Parteek Singh
 * @date: June-28-2020
 */

#ifndef CPP_PRACTICE_SHARED_PTR_IMPL_HPP
#define CPP_PRACTICE_SHARED_PTR_IMPL_HPP

#include <cstdint> // for uint32_t
#include <iostream> // for cout
#include <cassert> // for assert

namespace smart_pointers
{
    template <typename T>
    class SharedPointer
    {
    public:
        SharedPointer(T* var, bool debug = true): m_var(var), m_ref_count(new uint32_t(1)), m_debug(debug)
        {
        }

        // Copy constructor
        SharedPointer(SharedPointer const &s) : m_var(s.m_var),
                                                m_ref_count(s.m_ref_count),
                                                m_debug(s.m_debug)
        {
            *m_ref_count += 1;
            announceCreation("Copy constructed");
        }

        // Move constructor
        SharedPointer(SharedPointer &&s) : m_var(std::move(s.m_var)),
                                           m_ref_count(std::move(s.m_ref_count)),
                                           m_debug(std::move(s.m_debug))
        {
            *m_ref_count += 1;
            announceCreation("Move assigned");
        }

        // Copy assignment operator
        SharedPointer& operator=(SharedPointer const &s)
        {
            m_var         = s.m_var;
            m_ref_count   = s.m_ref_count;
            *m_ref_count += 1;
            m_debug       = s.m_debug;
            announceCreation("Copy assigned");
        }

        // Move assignment operator
        SharedPointer& operator=(SharedPointer const &&s)
        {
            m_var         = std::move(s.m_var);
            m_ref_count   = std::move(s.m_ref_count);
            *m_ref_count += 1;
            m_debug       = std::move(s.m_debug);
            announceCreation("Move assigned");
        }

        ~SharedPointer()
        {
            *m_ref_count -= 1;
            if (*m_ref_count == 0)
            {
                delete m_var; // assuming that this variable pointed to dynamically allocated memory
            }
        }

        uint32_t getCount() const
        {
            return *m_ref_count;
        }

    private:
        T*         m_var;       //!< Raw pointer to variable
        uint32_t*  m_ref_count; //!< Count of the number of references to variable i.e. number of pointers to variable
        bool       m_debug;     //!< Flag enabling/disabling debug prints

        void announceCreation(std::string const &str)
        {
            if (m_debug)
            {
                std::cout << str << ", ref count = " << *m_ref_count << std::endl;
            }
        }
    };

// TODO: 2020-06-28: Move to test/ and employ a GTEST framework

    void testSharedPtr()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        {
            SharedPointer<int> x(new int(5));
            assert(x.getCount() == 1);

            {
                SharedPointer<int> y(x);
                assert(x.getCount() == y.getCount());
                assert(x.getCount() == 2);
            }
            assert(x.getCount() == 1);

            {
                SharedPointer<int> z1 = std::move(x);
                SharedPointer<int> z2 = z1;
                SharedPointer<int> z3(std::move(z2));
                assert(x.getCount() == z1.getCount());
                assert(x.getCount() == z2.getCount());
                assert(x.getCount() == z3.getCount());
                assert(x.getCount() == 4);
            }
            assert(x.getCount() == 1);
        }
    }

}
#endif //CPP_PRACTICE_SHARED_PTR_IMPL_HPP
