#include "inheritance/single_two_level/access_specifiers.hpp"
#include "inheritance/single_two_level/basics.hpp"
#include "stl/vector_iteration.hpp"
#include "stl/two_sum.hpp"
#include "smart_pointers/test.hpp"

int main(int argc, char* argv[])
{
    inheritance::basics::test();
    inheritance::access_specifiers::test();

    std::vector<int> v{1,2,6,28,924};
    int target = 930;
    stl::TwoSum ts;
    auto s = ts.solution(v, target);
    stl::TwoSum2 ts2;
    auto s2 = ts2.solution(v, target);
    std::cout << "Algo1:" << s[0] << ", " << s[1] << std::endl;
    std::cout << "Algo2:" << s2[0] << ", " << s2[1] << std::endl;

    smart_pointers::testSharedPtr();

    return 0;
}
