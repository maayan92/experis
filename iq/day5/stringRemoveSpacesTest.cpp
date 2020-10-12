#include "mu_test.h"

#include "stringRemoveSpaces.hpp"
using namespace iq;

BEGIN_TEST(test_string_remove_space_extra_spaces)
    char str[] = "he     was    a  good     guy";

    char* result = RemoveDuplicateSpaces(str);

    char wantedResult[] = "he was a good guy";

    size_t size = strlen(wantedResult);
    for(size_t i = 0; i < size; ++i) {
        ASSERT_EQUAL(wantedResult[i], result[i]);
    }
END_TEST

BEGIN_SUITE(test_string_remove_space)
    TEST(test_string_remove_space_extra_spaces)
END_SUITE