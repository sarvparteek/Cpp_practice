/*!
 * @brief: Describes the effect of access specifiers during inheritance
 * @author: Sarv Parteek Singh
 * @date: June-20-2020
 * @note: Adapted from https://www.learncpp.com/cpp-tutorial/115-inheritance-and-access-specifiers/
 * @details: The file demonstrates the following access specifier and inheritance type combination:
 *     |------------------|-----------------------|-----------------------| ----------------------|
 *     | Access specifier | Access specifier when | Access specifier when | Access specifier when |
 *     | in base class    | inherited publicly    | inherited protectedly | inherited privately   |
 *     |------------------|-----------------------|-----------------------|-----------------------|
 *     |    Public        |       Public          |        Protected      |       Private         |
 *     |    Protected     |       Protected       |        Protected      |       Private         |
 *     |    Private       |       Inaccessible    |        Inaccessible   |       Inaccessible    |
 *     |------------------|-----------------------|-----------------------|-----------------------|
 */

#ifndef CPP_PRACTICE_INHERITANCE_SINGLE_TWO_LEVEL_ACCESS_SPECIFIERS_HPP
#define CPP_PRACTICE_INHERITANCE_SINGLE_TWO_LEVEL_ACCESS_SPECIFIERS_HPP

#include <iostream>

namespace inheritance
{
namespace access_specifiers
{
class Parent
{
public:
    int m_public_parent;

protected:
    int m_protected_parent;

private:
    int m_private_parent;
};

class Child1: public Parent
{
    /* Public inheritance =>
     * Public (base)    -> Public (derived)
     * Protected (base) -> Protected (derived)
     * Private (base)   -> inaccessible (derived)
     * Everything is inherited as is (at the level of public or more stringent)
     * */

public:
    int m_public_child1;

protected:
    int m_protected_child1;

private:
    int m_private_child1;
};

class Grandchild1: public Child1
{
    /* Public inheritance =>
     * Public (base)    -> Public (derived)
     * Protected (base) -> Protected (derived)
     * Private (base)   -> inaccessible (derived)
     * Everything is inherited as is (at the level of public or more stringent).
     * As Child1 protectedly inherited Parent, all of Parent's public and protected fields retain their specifier level
     * in Child1, and Grandchild1 can access all of them.
     * */

public:
    int m_public_grandchild1;

protected:
    int m_protected_grandchild1;

private:
    int m_private_grandchild1;
};

class Child2: protected Parent
{
    /* Protected inheritance =>
     * Public (base)    -> Protected (derived)
     * Protected (base) -> Protected (derived)
     * Private (base)   -> inaccessible (derived)
     * Essentially, everything is inherited at the level of protected or more stringent.
     * */

public:
    int m_public_child2;

protected:
    int m_protected_child2;

private:
    int m_private_child2;
};

class Grandchild2: public Child2
{
    /* Public inheritance =>
     * Public (base)    -> Public (derived)
     * Protected (base) -> Protected (derived)
     * Private (base)   -> inaccessible (derived)
     * Everything is inherited as is (at the level of public or more stringent).
     * As Child2 protectedly inherited Parent, all of Parent's public and protected fields became protected to Child2,
     * and Grandchild2 can access all of them.
     * */

public:
    int m_public_grandchild2;

protected:
    int m_protected_grandchild2;

private:
    int m_private_grandchild2;
};

class Child3: private Parent
{
    /* Private inheritance =>
     * Public (base)    -> Private (derived)
     * Protected (base) -> Private (derived)
     * Private (base)   -> inaccessible (derived)
     * Essentially, everything is inherited at the level of private.
     * */

public:
    int m_public_child3;

protected:
    int m_protected_child3;

private:
    int m_private_child3;
};

class Grandchild3: public Child3
{
    /* Public inheritance =>
     * Public (base)    -> Public (derived)
     * Protected (base) -> Protected (derived)
     * Private (base)   -> inaccessible (derived)
     * Everything is inherited as is (at the level of public or more stringent).
     * As Child3 privately inherited Parent, all of Parent's fields became private to Child3, and Grandchild3 cannot
     * access any of them.
     * */

public:
    int m_public_grandchild3;

protected:
    int m_protected_grandchild3;

private:
    int m_private_grandchild3;
};

int test()
{
    std::cout << "\nRunning " << __PRETTY_FUNCTION__ << std::endl;

    Parent p;
    Child1 c1;
    Child2 c2;
    Child3 c3;
    Grandchild1 gc1;
    Grandchild2 gc2;
    Grandchild3 gc3;

    /* Parent */
    std::cout <<"Parent's public: " << p.m_public_parent << std::endl;
    // cannot access p's protected and private.

    /* Child1: publicly inherited from parent*/
    std::cout << "Child1's public:"             << c1.m_public_child1 << std::endl;
    std::cout << "Child1's public from parent:" << c1.m_public_parent << std::endl;
    // Cannot access c1's protected (which includes Parent's protected) and private. Note that Child1 can access
    // Parent's protected (as they are its own protected now), but c1 cannot.

    /* Grandchild1: publicly inherited from Child1 */
    std::cout << "Grandchild1's public: "             << gc1.m_public_grandchild1 << std::endl;
    std::cout << "Grandchild1's public from Child1: " << gc1.m_public_child1      << std::endl;
    std::cout << "Grandchild1's public from parent: " << gc1.m_public_parent      << std::endl;
    // Cannot access gc1's protected (which includes Child1's protected, which in turn also includes Parent's protected)
    // and private. Note that Grandchild1 can access Child1's protected (as they are its own protected now), but gc1
    // cannot.

    /* Child2: protectedly inherited from parent */
    std::cout << "Child2's public:" << c2.m_public_child2 << std::endl;
    // Cannot access c2's protected (which includes Parent's public and protected) and private. Note that Child2 can
    // access Parent's public and protected (as they are now its protected), but c2 cannot.

    /* Grandchild2: publicly inherited from Child2 */
    std::cout << "Grandchild2's public: "             << gc2.m_public_grandchild2 << std::endl;
    std::cout << "Grandchild2's public from Child2: " << gc2.m_public_child2      << std::endl;
    // Cannot access gc2's protected (which includes Child2's protected, which in turn also includes Parent's public and
    // protected) and private. Note that Grandchild2 can access Child2's protected (as they are its own protected now),
    // but gc2 cannot.

    /* Child3: privately inherited from parent */
    std::cout << "Child3's public:" << c3.m_public_child3 << std::endl;
    // Cannot access c3's protected and private (which includes Parent's public and protected). Note that child3 can
    // access Parent's public and protected (as they are now its private), but c3 cannot.

    /* Grandchild3: publicly inherited from Child3 */
    std::cout << "Grandchild3's public: "             << gc3.m_public_grandchild3 << std::endl;
    std::cout << "Grandchild3's public from Child3: " << gc3.m_public_child3      << std::endl;
    // Cannot access gc3's protected and private. Grandchild3 gets no access to any of the Parent fields because all of
    // them were inherited privately by Child3 and Grandchild3 cannot access Child3's private fields.

    return 0;
}
} // access_specifiers
} // inheritance

#endif // CPP_PRACTICE_INHERITANCE_SINGLE_TWO_LEVEL_ACCESS_SPECIFIERS_HPP