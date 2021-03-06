/*!
 * @brief: Describes orders of constructor and destructor call, and access of methods in single inheritance
 * @author: Sarv Parteek Singh
 * @date: June-19-2020
 */

#ifndef CPP_PRACTICE_INHERITANCE_SINGLE_TWO_LEVEL_BASICS
#define CPP_PRACTICE_INHERITANCE_SINGLE_TWO_LEVEL_BASICS

#include <iostream>
#include <memory> // for unique_ptr
#include <cmath> // for abs

namespace inheritance
{
namespace basics
{
class Parent
{
    public:
    Parent(int var) : m_var_parent(var)
    {
        std::cout << "Parent constructor" << std::endl;
    }

    virtual ~Parent()
    {
        std::cout << "Parent destructor" << std::endl;
    }

    virtual void increment(int num)
    {
        std::cout << "Invoking Parent increment type 1" << std::endl;
        m_var_parent += num;
    }

    void increment()
    {
        std::cout << "Invoking Parent increment type 2" << std::endl;
        m_var_parent++;
    }

    void absolute()
    {
        std::cout << "Invoking Parent absolute" << std::endl;
        m_var_parent = std::abs(m_var_parent);
    }

protected:
    int m_var_parent;

private:
    void decrement()
    {
        std::cout << "Invoking Parent decrement" << std::endl;
        m_var_parent--;
    }
};

class Child : public Parent
{
public:
    /* Constructor for 'child' must explicilty initialize the base class 'parent' which does not have a default
     * constructor. If 'parent' did not have an explicit constructor, the compiler would have added an implicit 'empty'
     * constructor. */
    Child(int var1, int var2) : Parent(var1), m_var_child(var2)
    {
        std::cout << "Child constructor" << std::endl;
    }

    ~Child() // virtual by default, as it overrides ~Parent()
    {
        std::cout << "Child destructor" << std::endl;
    }

    void increment(int num) override
    {
        std::cout << "Invoking Child increment type 1" << std::endl;
        m_var_parent += 2 * num;
        m_var_child += 2 * num;
    }

    void increment()
    {
        std::cout << "Invoking Child increment type 2" << std::endl;
        m_var_parent += 2;
        m_var_child += 2;
    }

protected:
    void decrement()
    {
        std::cout << "Invoking Child decrement" << std::endl;
        m_var_parent -= 2;
        m_var_child -= 2;
    }

    int m_var_child;
};

class Grandchild : public Child
{
public:
    Grandchild(int var1, int var2, int var3) : Child(var1, var2), m_var_grandchild(var3)
    {
        std::cout << "Grandchild constructor" << std::endl;
    }

    ~Grandchild()
    {
        std::cout << "Grandchild destructor" << std::endl;
    }

    void increment(int num) override
    {
        std::cout << "Invoking Grandchild increment type 1" << std::endl;
        m_var_parent += 3 * num;
        m_var_child += 3 * num;
        m_var_grandchild += 3 * num;
    }

protected:
    void decrement()
    {
        std::cout << "Invoking Grandchild decrement" << std::endl;
        m_var_parent -= 3;
        m_var_child -= 3;
        m_var_grandchild -= 3;
    }

    int m_var_grandchild;
};

void add_five(std::unique_ptr<Parent> p)
{
    std::cout << "Adding 5" << std::endl;
    p->increment(5);
}

/*!
 * @details: This function demonstrates the following:
 * 1. A pointer to a base class can be used to point to an object of the derived (or derived of derived) class, but not
 *    vice versa. This is true for both raw and smart pointers (obviously, since the latter is just a 'safer' version of
 *    the former).
 * 2. When a pointer to base class is used to point to an object of the derived class, a call to this pointer's method,
 *    which is virtual in base class and overriden in derived class, invokes the method in the derived class. However, a
 *    call to a method which is present in both base and derived class, but not linked via the virtual-override
 *    mechanism, invokes the method in the base class.
 * 3. In an object of derived_second_level class,
 *    The order of construction is always: base,derived_first_level, derived_second_level
 *    The order of destruction is always: derived_second_level, derived_first_level, base
 * 4. For 2 to be valid, destructors in every class that has a virtual function (i.e. from which inheritance is occuring)
 *    should be virtual. If this is not the case, the results are quite different. Experiment with that and see the
 *    output. Also, see C++ programming fundamentals (4th edition) by Stroustrup, Section 17.2.5
 *
 * @return none
 */
int test()
{
    std::cout << "\nRunning " << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "-------Analyzing Parent-------" << std::endl;
    {
        Parent p(2);
        p.increment(3);
        p.increment();
        p.absolute();
        // p.decrement(); // cannot call protected method
        auto p_ptr = std::make_unique<Parent>(p);
        add_five(std::move(p_ptr)); // cannot pass without constructing p_ptr as function expects lvalue (not rvalue)
                                    // std::move required to transfer unique_ptr. See
                                    // https://stackoverflow.com/questions/17473900/unique-ptr-to-a-derived-class-as-an-argument-to-a-function-that-takes-a-unique-p
                                    // add_five is a "sink" function.
                                    // See https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/
                              // calls Parent destructor to destroy p_ptr
        std::cout << "Addition of 5 done" << std::endl;
    } // Parent destructor called to destroy p


    std::cout << "-------Analyzing Parent-Child pointer conversions-------" << std::endl;
    {
        /* The following is not possible, as we cannot convert from base class pointer to derived class pointer */
//        std::unique_ptr<Child> p(new Parent(2));
        /* However, the following is allowed */
        /*
        Parent *p_ptr_to_p = new Parent(1);
        Parent *p_ptr_to_c = new Child(2, 6);
//        Child *c_ptr_to_p = new Parent(1); // a Child* cannot point to a Parent object
        Child *c_ptr_to_p_to_c = static_cast<Child *>(p_ptr_to_c); // a Child* can
        Child *c_ptr_to_p_to_p = static_cast<Child *>(p_ptr_to_p);

        delete p_ptr_to_p;
        delete p_ptr_to_c;
        delete c_ptr_to_p_to_c;
        delete c_ptr_to_p_to_p;
*/ // TODO - SPS - Investigate "terminate called recursively" in subsequent statement when this commented block is
   // executed.
//        std::unique_ptr<Parent> p_uptr_to_p(new Parent(1)); // not as safe as the following usage of unique_ptr
                                                              //(see https://shaharmike.com/cpp/unique-ptr/)
                                                   // https://herbsutter.com/2013/05/29/gotw-89-solution-smart-pointers/
        std::unique_ptr<Parent> p_uptr_to_p = std::make_unique<Parent>(4);
        std::unique_ptr<Parent> p_uptr_to_c = std::make_unique<Child>(2,6);
//        std::unique_ptr<Child>  c_uptr_to_p  = std::make_unique<Parent>(Parent(1)); // not allowed
        /* The following two statements are not allowed until a new constructor of the type
         * Child(std::unique_ptr<Parent>) is created */
//        std::unique_ptr<Child> c_uptr_to_p_to_c = std::make_unique<Child>(std::move(p_uptr_to_c));
//        std::unique_ptr<Child> c_uptr_to_p_to_p = std::make_unique<Child>(std::move(p_uptr_to_p));
    }

    /* Order of constructor invocation: Parent->child
     * Order of destruction invocation: Child->parent
     * Call to overriden function invokes method in Child
     * Call to non-overriden function of same name invokes method in Child
     * */
    std::cout << "-------Analyzing Child-------" << std::endl;
    {
        Child c(3, 5);
        c.increment(4); // will invoke method in Child
        c.increment(); // will invoke method in Child
        c.absolute();  // will invoke method in Parent
        // c.decrement(); // cannot call protected method (decrement is still protected in Child, as protected methods
                          // stay protected when derived class inherits the base class publicly)
        auto c_ptr = std::make_unique<Child>(c);
        add_five(std::move(c_ptr)); // calls Child Destructor, Parent destructor to destroy c_ptr
        std::cout << "Addition of 5 done" << std::endl;
    } // Child destructor, Parent destructor called to destroy c

    /* Order of constructor invocation: Parent->child
     * Order of destruction invocation: Parent (child destructor is not called)
     * Call to overriden function invokes method in Child
     * Call to non-overriden function of same name invokes method in Parent, not Child
     * */
    std::cout << "-------Analyzing Child of type Parent-------" << std::endl;
    {
        std::unique_ptr<Parent> p_ptr(new Child(3, 5));
        p_ptr->increment(4); // will invoke method in Child
        p_ptr->increment(); // will invoke method in Parent
        p_ptr->absolute(); // will invoke method in Parent
        // p_ptr->decrement(); // cannot call protected method
        add_five(std::move(p_ptr)); // calls Child destructor, Parent destructor to destroy p_ptr
        std::cout << "Addition of 5 done" << std::endl;
    }

    /* Order of constructor invocation: Parent->child->Grandchild
     * Order of destruction invocation: Grandchild->child->parent
     * Call to overriden function invokes method in Grandchild
     * */
    std::cout << "-------Analyzing Grandchild-------" << std::endl;
    {
        Grandchild gc(1, 8, 9);
        gc.increment(6); // will invoke method in Grandchild
        // gc.increment(); // cannot invoke increment() method of Child
        gc.absolute(); // will invoke method in Parent
        // gc.decrement(); // cannot call protected method
        auto gc_ptr = std::make_unique<Grandchild>(gc);
        add_five(std::move(gc_ptr)); // calls Grandchild destructor, Child destructor, Parent destructor to destroy gc_ptr
        std::cout << "Addition of 5 done" << std::endl;
    } // Grandchild destructor, Child destructor, Parent destructor called to destroy gc

    /* Order of constructor invocation: Parent->child->Grandchild
     * Order of destruction invocation: Child->parent (Grandchild destructor is not called)
     * Call to overriden function invokes method in Grandchild
     * Call to non-overriden function of same name invokes method in Child
     * */
    std::cout << "--------Analyzing Grandchild of type Child-------" << std::endl;
    {
        std::unique_ptr<Child> c_ptr(new Grandchild(1, 2, 3));
        c_ptr->increment(6); // will invoke method in Grandchild
        c_ptr->increment(); // will invoke method in Child
        c_ptr->absolute(); // will invoke method in Parent
        add_five(std::move(c_ptr)); // calls Grandchild destructor, Child destructor, Parent destructor to destroy c_ptr
        std::cout << "Addition of 5 done" << std::endl;
    }

    /* Order of constructor invocation: Parent->child->Grandchild
     * Order of destruction invocation: Parent (child and Grandchild destructors are not called)
     * Call to overriden function invokes method in Grandchild
     * Call to non-overriden function of same name invokes method in Parent
     * */
    std::cout << "--------Analyzing Grandchild of type Parent-------" << std::endl;
    {
        std::unique_ptr<Parent> p_ptr(new Grandchild(1, 2, 3));
        p_ptr->increment(6); // will invoke method in Grandchild
        p_ptr->increment(); // will invoke method in Parent
        p_ptr->absolute(); // will invoke method in Parent
        add_five(std::move(p_ptr)); // calls Grandchild destructor, Child destructor, Parent destructor to destroy p_ptr
        std::cout << "Addition of 5 done" << std::endl;
    }

    return 0;
}

} // basics
} // inheritance

#endif // CPP_PRACTICE_INHERITANCE_SINGLE_TWO_LEVEL_BASICS