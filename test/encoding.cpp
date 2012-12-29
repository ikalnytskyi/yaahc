/*
 * Copyright 2012 Igor Kalnitsky <igor@kalnitsky.org>
 *
 * This file is part of yaahc.
 *
 * yaahc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * yaahc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with yaahc.  If not, see <http://www.gnu.org/licenses/>.
 */

#define BOOST_TEST_MODULE tree encoding test
#include <boost/test/unit_test.hpp>

#include <ahc/tree.hpp>

using ahc::byte_t;
using ahc::bit_t;


/*!
 * A fixture class. All members will
 * be available in all of the test cases.
 */
struct Fixture
{
    ahc::Tree tree;
    std::vector<bit_t> code;
};


BOOST_FIXTURE_TEST_SUITE(encoding, Fixture)


BOOST_AUTO_TEST_CASE(encode_one_byte)
{
    const std::vector<bit_t> RESULT = {0, 1, 1, 0, 0, 0, 0, 1};

    code = tree.encode('a');
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT), end(RESULT), begin(code), end(code));
}


BOOST_AUTO_TEST_CASE(encode_two_bytes)
{
    const std::vector<bit_t> RESULT = {1};

    tree.encode('a');

    code = tree.encode('a');
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT), end(RESULT), begin(code), end(code));
}


BOOST_AUTO_TEST_CASE(encode_two_different_bytes)
{
    const std::vector<bit_t> A_RESULT = {0, 1, 1, 0, 0, 0, 0, 1};
    const std::vector<bit_t> B_RESULT = {0, 0, 1, 1, 0, 0, 0, 1, 0};

    code = tree.encode('a');
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(A_RESULT), end(A_RESULT), begin(code), end(code));

    code = tree.encode('b');
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(B_RESULT), end(B_RESULT), begin(code), end(code));
}


BOOST_AUTO_TEST_CASE(encode_a_few_bytes)
{
    const std::vector<bit_t> RESULT = {
        0,1,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,
        0,0,1,0,0,0,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,1,1
    };

    for (byte_t byte : {'a', 'a', ' ', 'b', 'b', 'b', ' ', 'c'})
    {
        auto bits = tree.encode(byte);
        code.insert(end(code), begin(bits), end(bits));
    }

    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT), end(RESULT), begin(code), end(code));
}


BOOST_AUTO_TEST_SUITE_END()
