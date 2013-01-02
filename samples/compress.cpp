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

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <ahc/tree.hpp>


using ahc::byte_t;
using ahc::bit_t;

void compress(std::istream& in, std::ostream& out);
void flush_buffer(std::vector<bit_t>& w_buffer, std::ostream& out);


int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Help: compress <source> <destination>" << std::endl;
        return -1;
    }

    const char* src = argv[1];
    const char* dst = argv[2];

    std::ifstream in(src, std::ios::binary);
    std::ofstream out(dst, std::ios::binary);

    compress(in, out);
    return 0;
}


void compress(std::istream& in, std::ostream& out)
{
    const size_t BUFFER_SIZE = 512;

    std::vector<byte_t> r_buffer(BUFFER_SIZE);
    std::vector<bit_t>  w_buffer;

    ahc::Tree tree(ahc::FGK);
    w_buffer.reserve(8 * BUFFER_SIZE + BUFFER_SIZE);

    while (in)
    {
        in.read(reinterpret_cast<char*>(r_buffer.data()), BUFFER_SIZE);
        size_t read_bytes = in.gcount();

        // encode read bytes
        for (size_t i = 0; i < read_bytes; ++i)
        {
            std::vector<bit_t> code = tree.encode(r_buffer[i]);
            std::copy(std::begin(code), std::end(code), std::back_inserter(w_buffer));
        }

        // flush buffer if it almost fill
        if (w_buffer.size() >= 8 * BUFFER_SIZE)
            flush_buffer(w_buffer, out);
    }

    // fill buffer with zeroes if byte is not complete
    byte_t extra_bits = 0;
    if (w_buffer.size() % 8 != 0)
    {
        extra_bits = 8 - w_buffer.size() % 8;
        std::fill_n(std::back_inserter(w_buffer), extra_bits, 0);
    }

    flush_buffer(w_buffer, out);
    out.write(reinterpret_cast<char*>(&extra_bits), 1);
}


void flush_buffer(std::vector<ahc::bit_t>& w_buffer, std::ostream& out)
{
    std::vector<byte_t> bytes;
    bytes.reserve(w_buffer.size() / 8);

    for (size_t i = 0; i + 8 <= w_buffer.size(); i += 8)
    {
        byte_t byte = 0;
        for (size_t j = 0; j < 8; ++j)
            byte |= w_buffer[i + j] << (7 - j);
        bytes.push_back(byte);
    }

    w_buffer.erase(std::begin(w_buffer), std::begin(w_buffer) + bytes.size() * 8);
    out.write(reinterpret_cast<char*>(bytes.data()), bytes.size());
}
