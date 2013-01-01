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

#include <cstdlib>
#include <ctime>

#define BOOST_TEST_MODULE tree encoding-decoding test
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
    ahc::Tree encoder;
    ahc::Tree decoder;

    std::vector<bit_t> code;
    std::vector<byte_t> seq;
};


BOOST_FIXTURE_TEST_SUITE(encdec, Fixture)


BOOST_AUTO_TEST_CASE(encoding_decoding)
{
    const std::vector<byte_t> SEQUENCE = {'a', 'a', ' ', 'b', 'b', 'b', ' ', 'c'};

    for (byte_t byte : SEQUENCE)
    {
        auto bits = encoder.encode(byte);
        code.insert(end(code), begin(bits), end(bits));
    }

    seq = decoder.decode(code);

    BOOST_CHECK_EQUAL_COLLECTIONS(begin(SEQUENCE), end(SEQUENCE), begin(seq), end(seq));
}


BOOST_AUTO_TEST_CASE(encoding_decoding_random)
{
    const size_t SEQUENCES_AMOUNT = 1024;
    const size_t MIN_SEQ_SIZE = 1;
    const size_t MAX_SEQ_SIZE = 512;

    std::srand(static_cast<unsigned int>(time(0)));

    for (size_t i = 0; i < SEQUENCES_AMOUNT; ++i)
    {
        ahc::Tree encoder;
        ahc::Tree decoder;

        std::vector<bit_t> code;
        std::vector<byte_t> seq;

        size_t seq_size = rand() % (MAX_SEQ_SIZE - MIN_SEQ_SIZE) + MIN_SEQ_SIZE + 1;

        // generate a sequence
        std::vector<byte_t> sequence(seq_size);
        std::generate(begin(sequence), end(sequence), [] {
            return rand() % 255;
        });

        // encoding
        for (byte_t byte : sequence)
        {
            auto bits = encoder.encode(byte);
            code.insert(end(code), begin(bits), end(bits));
        }

        // decoding
        seq = decoder.decode(code);

        // test
        BOOST_CHECK_EQUAL_COLLECTIONS(begin(sequence), end(sequence), begin(seq), end(seq));
    }
}


BOOST_AUTO_TEST_SUITE_END()
