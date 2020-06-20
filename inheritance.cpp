#include <iostream>
#include <memory> // for unique_ptr

class parent
{
public:
    parent(int var): m_var_parent(var)
    {
        std::cout << "Parent constructor" << std::endl;
    }

    ~parent()
    {
        std::cout << "Parent destructor" << std::endl;
    }

    virtual void increment(int num)
    {
        std::cout << "Invoking parent increment type 1" << std::endl;
        m_var_parent += num;
    }

    void increment()
    {
        std::cout << "Invoking parent increment type 2" << std::endl;
        m_var_parent++;
    }

protected:
    int m_var_parent;

private:
    void decrement()
    {
        std::cout << "Invoking parent decrement" << std::endl;
        m_var_parent--;
    }
};

class child: public parent
{
public:
    /* Constructor for 'child' must explicilty initialize the base class 'parent' which does not have a default
     * constructor. If 'parent' did not have an explicit constructor, the compiler would have added an implicit 'empty'
     * constructor. */
    child(int var1, int var2) : parent(var1), m_var_child(var2)
    {
        std::cout << "Child constructor" << std::endl;
    }

    ~child()
    {
        std::cout << "Child destructor" << std::endl;
    }

    void increment(int num) override
    {
        std::cout << "Invoking child increment type 1" << std::endl;
        m_var_parent += 2*num;
        m_var_child += 2*num;
    }

    void increment()
    {
        std::cout << "Invoking child increment type 2" << std::endl;
        m_var_parent += 2;
        m_var_child += 2;
    }

protected:
    void decrement()
    {
        "Invoking child decrement";
        m_var_parent -= 2;
        m_var_child -= 2;
    }

    int m_var_child;
};

class grandchild: public child
{
public:
    grandchild(int var1, int var2, int var3) : child(var1, var2), m_var_grandchild(var3)
    {
        std::cout << "Grandchild constructor" << std::endl;
    }

    ~grandchild()
    {
        std::cout << "Grandchild destructor" << std::endl;
    }                                                 
    void increment(int num) override
    {
        std::cout << "Invoking grandchild increment type 1" << std::endl;
        m_var_parent  += 3*num;
        m_var_child += 3*num;
        m_var_grandchild = 3*num;
    }

protected:
    void decrement()
    {
        std::cout << "Invoking grandchild decrement" << std::endl;
        m_var_parent     -= 3;
        m_var_child      -= 3;
        m_var_grandchild -= 3;
    }

    int m_var_grandchild;
};

int main()
{
    std::cout << "-------Analyzing parent-------" << std::endl;
    {
        parent p(2);
        p.increment(3);
        p.increment();
        // p.decrement(); // cannot call private method
    }

    /* The following is not possible, as we cannot convert from base class pointer to derived class pointer */
    //std::cout << "-------Analyzing parent of type child-------" << std::endl;
    //{
    //    std::unique_ptr<child> p(new parent(2));
    //}

    /* Order of constructor invocation: parent->child
     * Order of destruction invocation: child->parent
     * Call to overriden function invokes method in child
     * Call to non-overriden function of same name invokes method in child
     * */
    std::cout << "-------Analyzing child-------" << std::endl;
    {
        child c(3,5);
        c.increment(4); // will invoke method in child
        c.increment(); // will invoke method in child
        // c.decrement(); // cannot call protected method
    }

    /* Order of constructor invocation: parent->child
     * Order of destruction invocation: parent (child destructor is not called)
     * Call to overriden function invokes method in child
     * Call to non-overriden function of same name invokes method in parent, not child
     * */
    std::cout << "-------Analyzing child of type parent-------" << std::endl;
    {
        std::unique_ptr<parent> c(new child(3,5));
        c->increment(4);
        c->increment();
        // c->decrement(); // cannot call protected method
    }

    /* Order of constructor invocation: parent->child->grandchild
     * Order of destruction invocation: grandchild->child->parent
     * Call to overriden function invokes method in grandchild
     * */
    std::cout << "-------Analyzing grandchild-------" << std::endl;
    {
        grandchild g(1,8,9);
        g.increment(6);
        // g.increment(); // cannot invoke increment() method of child
        // g.decrement(); // cannot call protected method
    }

    /* Order of constructor invocation: parent->child->grandchild
     * Order of destruction invocation: child->parent (grandchild destructor is not called)
     * Call to overriden function invokes method in grandchild
     * Call to non-overriden function of same name invokes method in child
     * */
    std::cout << "--------Analyzing grandchild of type child-------" << std::endl;
    {
        std::unique_ptr<child> g(new grandchild(1, 2, 3));
        g->increment(6);
        g->increment();
    }

    /* Order of constructor invocation: parent->child->grandchild
     * Order of destruction invocation: parent (child and grandchild destructors are not called)
     * Call to overriden function invokes method in grandchild
     * Call to non-overriden function of same name invokes method in parent
     * */
    std::cout << "--------Analyzing grandchild of type parent-------" << std::endl;
    {
        std::unique_ptr<parent> g(new grandchild(1, 2, 3));
        g->increment(6);
        g->increment();
    }
}


