/*!
 * @brief Implements a linked list
 * @author Sarv Parteek Singh
 * @date July-04-2020
 */

#ifndef CPP_PRACTICE_IMPL_HPP
#define CPP_PRACTICE_IMPL_HPP

#include <iostream>
#include <memory> // for shared_ptr
#include <utility>
#include <string>
namespace data_structures
{
namespace linked_list
{
    template <typename T>
    struct ListNode
    {
        T data;
        std::shared_ptr<ListNode<T>> next; // pointer could be shared because multiple nodes can point to a data element,
        // For instance, 1->2->3->4->5->6
        //                  ^           |
        //                  |------<----|
        // Source: Ch 7, Linked Lists, Elements of Programming Interviews
        // This is not recommended in general though:
        // https://www.quora.com/Should-I-use-a-shared_ptr-or-raw-pointer-when-designing-the-node-class-of-a-linked-list-or-BST-in-C++

        ListNode(T const &in_data): data(in_data), next(nullptr)
        {}
        ListNode(T const &in_data, std::shared_ptr<ListNode<T>> node): data(in_data), next(std::move(node))
        {}
    };


    template <typename T>
    void pushBack(std::shared_ptr<ListNode<T>> &head, T const &data)
    {
        auto node = head;
        while (node->next != nullptr)
        {
            node = node->next;
        }
        node->next = std::shared_ptr<ListNode<T>>(new ListNode<T>(data));
    }

    template <typename T>
    void pushFront(std::shared_ptr<ListNode<T>> &head, T const &data)
    {
        head = std::make_shared<ListNode<T>>(data, head);
    }

    template <typename T>
    void insertAfter(std::shared_ptr<ListNode<T>> const &node, T const &data)
    {
        node->next = std::make_shared<ListNode<T>>(ListNode<T>(data, node->next));
    }

    template <typename T>
    void deleteAfter(std::shared_ptr<ListNode<T>> &node)
    {
        assert(node->next != nullptr);
        node->next = node->next->next;
    }

    template <typename T>
    std::shared_ptr<ListNode<T>> findNode(std::shared_ptr<ListNode<T>> const &head, T const &data)
    {
        auto node = head;
        while (node != nullptr && node->data != data)
        {
            node = node->next;
        }
        return node;
    }

    template <typename T>
    void printList(std::shared_ptr<ListNode<T>> const &head)
    {
        auto node = head;
        while (node->next != nullptr)
        {
            std::cout << node->data << "->";
            node = node->next;
        }
        std::cout << node->data << std::endl;
    }

    template <typename T>
    void reverse(std::shared_ptr<ListNode<T>> &head)
    {
        std::shared_ptr<ListNode<T>> left(nullptr);
        auto center = head;
        auto right  = head->next;

        while (true)
        {
            /* Update (reversing link direction) */
            center->next = left; // have center point to left instead of right

            /* Break condition */
            if (right == nullptr) // center is now list's last element
            {
                head = center;
                return;
            }

            /* Iteration: shift everything to the right. L->C, C->R, C->R's right */
            left   = center;
            center = right;
            right  = right->next;
        }
    }

    // TODO: Move function definitions to src, tests to src/ with GTEST framework

    void testIntList()
    {
        std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl ;

        /* Test pushBack() */
        auto head = std::make_shared<ListNode<int>>(ListNode<int>(4));
        pushBack<int>(head, 5);
        pushBack<int>(head, 6);
        pushBack<int>(head, 7);
        std::cout <<"Original list : ";
        printList<int>(head);

        /* Test insertAfter() */
        std::cout << "Adding 105 after 6" << std::endl;
        insertAfter<int>(head->next->next, 105);
        std::cout << "New list: ";
        printList<int>(head);

        /* Test deleteAfter() */
        std::cout << "Removing node after 6" << std::endl;
        deleteAfter(head->next->next);
        std::cout << "New list: ";
        printList<int>(head);

        /* Test pushFront() */
        std::cout << "Pushing 3 in front of list" << std::endl;
        pushFront(head, 3);
        std::cout << "New list: ";
        printList<int>(head);

        /* Test findNode() */
        std::cout << "Searching for node with data 4" << std::endl;
        auto node = findNode(head, 4);
        std::cout << "Found node " << std::string(node == nullptr?
                                                  "is NULL"
                                                                 : "has value: " + std::to_string(node->data))
                  << std::endl;
        std::cout << "Searching for node with data -1 " << std::endl;
        node = findNode(head, -1);
        std::cout << "Found node " << std::string(node == nullptr?
                                                  "is NULL"
                                                                 : "has value: " + std::to_string(node->data))
                  << std::endl;

        /* Test reverse() */
        std::cout << "Reversing list" << std::endl;
        reverse(head);
        std::cout << "New list: ";
        printList<int>(head);
    }
} // linked_list
} // data_structures
#endif //CPP_PRACTICE_IMPL_HPP
