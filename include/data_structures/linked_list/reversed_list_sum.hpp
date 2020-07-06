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
            int carry       = 0;
            auto list1      = l1;
            auto list2      = l2;
            auto l_sum_head = new ListNodeRawInt(); // adds a 0 element in the front (can be handled later)

            while (!(list1 == nullptr && list2 == nullptr))
            {

                auto sum_info = getSingleDigitSum(list1 == nullptr? 0 :list1->val,
                                                  list2 == nullptr? 0: list2->val,
                                                  carry);
                auto digit    = sum_info.first;
                carry         = sum_info.second;
                pushBack(l_sum_head, digit);
                list1  = (list1 == nullptr? nullptr : list1->next);
                list2  = (list2 == nullptr? nullptr : list2->next);
            }

            if (carry)
            {
                pushBack(l_sum_head, carry);
            }

            return l_sum_head->next;
        }

    private:
        std::pair<int, int> getSingleDigitSum(int const &num1, int const &num2, int const &previous_carry)
        {
            int sum   = num1 + num2 + previous_carry;
            int carry = 0;
            if (sum > 9)
            {
                sum  -= 10;
                carry = 1; // sum of two digits cannot exceed 18 => max carry = 1
            }
            return std::make_pair(sum, carry);
        }
    };

    void testSingleSet(std::vector<int> const &vec1, std::vector<int> const &vec2)
    {
        auto head1 = new ListNodeRawInt(vec1.at(0));
        for (std::size_t i = 1; i < vec1.size(); ++i)
        {
            pushBack(head1, vec1.at(i));
        }

        auto head2 = new ListNodeRawInt(vec2.at(0));
        for (std::size_t i = 1; i < vec2.size(); ++i)
        {
            pushBack(head2, vec2.at(i));
        }

        ReverseListSum rls;
        auto sum_head = rls.addTwoNumbers(head1, head2);
        std::cout << "List 1: ";
        printList(head1);
        std::cout << "List 2: ";
        printList(head2);
        std::cout << "Summed list: ";
        printList(sum_head);
    }

    void testReverseListSum()
    {
        std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
        testSingleSet(std::vector<int> {2,4,3}, std::vector<int> {5,6,4});
        testSingleSet(std::vector<int> {0}, std::vector<int> {1,8});
        testSingleSet(std::vector<int> {1}, std::vector<int> {9,9});
    }

} // linked_list
} // data_structures

#endif //CPP_PRACTICE_REVERSED_LIST_SUM_HPP
