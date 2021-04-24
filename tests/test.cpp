#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE main_test
#include <boost/test/unit_test.hpp>

int add(int i, int j) { return i + j; }

BOOST_AUTO_TEST_CASE(main_test) { BOOST_CHECK(add(2, 2) == 4); }
