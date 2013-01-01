/*
 * Copyright 2012 Igor Kalnitsky <igor@kalnitsky.org>
 *
 * This file is part of YaAHC.
 *
 * YaAHC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * YaAHC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with YaAHC.  If not, see <http://www.gnu.org/licenses/>.
 */

#define BOOST_TEST_MODULE tree decoding test
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
    std::vector<byte_t> seq;
};


BOOST_FIXTURE_TEST_SUITE(decoding, Fixture)


BOOST_AUTO_TEST_CASE(decode_a_byte)
{
    const std::vector<byte_t> RESULT = {'a'};

    seq = tree.decode({0,1,1,0,0,0,0,1});
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT), end(RESULT), begin(seq), end(seq));
}


BOOST_AUTO_TEST_CASE(decode_a_sequence)
{
    const std::vector<byte_t> RESULT = {'a', 'a', ' ', 'b', 'b', 'b', ' ', 'c'};

    seq = tree.decode({
        0,1,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,
        0,0,1,0,0,0,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,1,1
    });

    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT), end(RESULT), begin(seq), end(seq));
}


BOOST_AUTO_TEST_CASE(decode_a_sequence_with_extra)
{
    const std::vector<byte_t> RESULT = {'a', 'a', ' ', 'b', 'b', 'b', ' ', 'c'};

    seq = tree.decode({
        0,1,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,
        0,0,1,0,0,0,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1
    });

    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT), end(RESULT), begin(seq), end(seq));
}


BOOST_AUTO_TEST_CASE(decode_a_sequence_in_few_steps)
{
    const std::vector<byte_t> RESULT_1 = {'a', 'a', ' ', 'b'};
    const std::vector<byte_t> RESULT_2 = {'b', 'b', ' ', 'c'};

    seq = tree.decode({0,1,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0});
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT_1), end(RESULT_1), begin(seq), end(seq));

    seq = tree.decode({0,0,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,1,1});
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT_2), end(RESULT_2), begin(seq), end(seq));
}


BOOST_AUTO_TEST_CASE(decode_a_sequence_in_few_steps_2)
{
    const std::vector<byte_t> RESULT_1 = {'a', 'a', ' '};
    const std::vector<byte_t> RESULT_2 = {'b', 'b', 'b', ' ', 'c'};

    seq = tree.decode({0,1,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0});
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT_1), end(RESULT_1), begin(seq), end(seq));

    seq = tree.decode({0,1,0,0,0,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,1,1,});
    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT_2), end(RESULT_2), begin(seq), end(seq));
}


BOOST_AUTO_TEST_CASE(decode_a_byte_sequence)
{
    const std::vector<byte_t> RESULT = {172, 172, 248, 255, 255, 255, 248, 200};

    seq = tree.decode({
        1,0,1,0,1,1,0,0,1,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,
        1,1,1,1,0,0,1,1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,0
    });

    BOOST_CHECK_EQUAL_COLLECTIONS(begin(RESULT), end(RESULT), begin(seq), end(seq));
}

BOOST_AUTO_TEST_SUITE_END()
