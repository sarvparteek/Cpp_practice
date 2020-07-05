/*!
 * @brief Finds sum of two non-empty linked lists representing two non-negative integers stored in reverse order.
 * @author Sarv Parteek Singh
 * @date July-04-2020
 * @details: Sourced from https://leetcode.com/problems/add-two-numbers/
 * You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse
 * order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list. You may
 * assume the two numbers do not contain any leading zero, except the number 0 itself.
 * Example:
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 */

#ifndef CPP_PRACTICE_REVERSED_LIST_SUM_HPP
#define CPP_PRACTICE_REVERSED_LIST_SUM_HPP

namespace data_structures
{
namespace linked_list
{
    struct ListNodeRawInt
    {
        int val;
        ListNodeRawInt *next;

        ListNodeRawInt() : val(0), next(nullptr)
        {}

        ListNodeRawInt(int x) : val(x), next(nullptr)
        {}

        ListNodeRawInt(int x, ListNodeRawInt *next) : val(x), next(next)
        {}
    };

    void pushBack(ListNodeRawInt* head, int data)
    {
        auto node = head;
        while (node->next != nullptr)
        {
            node = node->next;
        }
        node->next = new ListNodeRawInt(data);
    }

    void printList(ListNodeRawInt* head)
    {
        auto node = head;
        while (node->next != nullptr)
    {
        std::cout << node->val << "->";
        node = node->next;
    }
        std::cout << node->val << std::endl;
    }

    class ReverseListSum
    {
    public:
        ListNodeRawInt* addTwoNumbers(ListNodeRawInt* l1, ListNodeRawInt* l2)
        {
            int total_sum  = 0;
            int multiplier = 1;
            int carry      = 0;
            auto list1     = l1;
            auto list2     = l2;
            while (list1 != nullptr)
            {
                auto step_sum       = list1->val + list2->val;
                auto previous_carry = carry;
                if (step_sum > 9)
                {
                    carry    = 1;
                    step_sum = step_sum - 10;
                }
                else
                {
                    carry = 0;
                }
                total_sum  += (step_sum + previous_carry) * multiplier;
                multiplier *= 10;
                list1 = list1->next;
                list2 = list2->next;
            }

            std::cout << "List 1: ";
            printList(l1);
            std::cout << "List 2: ";
            printList(l2);
            std::cout << "Numbers sum to " << total_sum << std::endl;
            multiplier /= 10; // to accomodate for the last extra multiplication before exiting while loop
            auto l_sum_head = new ListNodeRawInt(); // adds a 0 element in the front (can be handled later)

            while (multiplier >= 1)
            {
                auto quotient = total_sum/multiplier;
                pushBack(l_sum_head, quotient);
                total_sum -= quotient * multiplier;
                multiplier   /= 10;
            }

            return l_sum_head->next;
        }
    };

    void testReverseListSum()
    {
        auto head1 = new ListNodeRawInt(2);
        pushBack(head1, 4);
        pushBack(head1, 3);
        auto head2 = new ListNodeRawInt(5);
        pushBack(head2, 6);
        pushBack(head2, 4);
        ReverseListSum rls;
        auto sum_head = rls.addTwoNumbers(head1, head2);
        std::cout << "Summed list: ";
        printList(sum_head);
    }
}
}

#endif //CPP_PRACTICE_REVERSED_LIST_SUM_HPP
