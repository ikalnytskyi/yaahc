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

void uncompress(std::istream& in, std::ostream& out);


int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Help: uncompress <source> <destination>" << std::endl;
        return -1;
    }

    const char* src = argv[1];
    const char* dst = argv[2];

    std::ifstream in(src, std::ios::binary);
    std::ofstream out(dst, std::ios::binary);

    uncompress(in, out);
    return 0;
}


void uncompress(std::istream& in, std::ostream& out)
{
    const size_t BUFFER_SIZE = 512;

    std::vector<byte_t> r_buffer(BUFFER_SIZE);
    std::vector<bit_t>  w_buffer;

    ahc::Tree tree(ahc::FGK);
    w_buffer.reserve(8 * BUFFER_SIZE + BUFFER_SIZE);

    in.seekg(0, std::ios::end);
    std::streampos eof = in.tellg();
    in.seekg(0, std::ios::beg);

    while (in)
    {
        in.read(reinterpret_cast<char*>(r_buffer.data()), BUFFER_SIZE);
        size_t read_bytes = in.gcount();

        for (size_t i = 0; i < read_bytes; ++i)
        {
            std::vector<bit_t> byte(8);
            for (size_t j = 0; j < 8 * sizeof(byte_t); ++j)
                byte[j] = (0x1 & (r_buffer[i] >> (7 - j)));
            std::copy(std::begin(byte), std::end(byte), std::back_inserter(w_buffer));
        }

        if (in.tellg() >= eof || in.eof())
        {
            byte_t extra_bits = r_buffer[read_bytes - 1];
            w_buffer.resize(w_buffer.size() - extra_bits - 8);
        }

        std::vector<byte_t> output = tree.decode(w_buffer);
        out.write(reinterpret_cast<char*>(output.data()), output.size());
        w_buffer.clear();
    }
}
