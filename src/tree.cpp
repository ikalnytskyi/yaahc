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

#include <ahc/tree.hpp>

#include "fgk/tree.hpp"


namespace ahc
{

Tree::Tree(Algorithm algorithm_type)
{
    switch (algorithm_type)
    {
    case Algorithm::FGK:
        _impl.reset(new fgk::Tree);
    }
}


Tree::~Tree()
{ }


std::vector<bit_t> Tree::encode(byte_t byte)
{
    return _impl->encode(byte);
}


std::vector<byte_t> Tree::decode(const std::vector<bit_t>& bits)
{
    return _impl->decode(bits);
}

} // namespace ahc
