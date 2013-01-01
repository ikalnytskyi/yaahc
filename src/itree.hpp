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

#ifndef YAAHC_ITREE_HPP_
#define YAAHC_ITREE_HPP_

#include <vector>
#include <ahc/common.hpp>


namespace ahc
{

/*!
 * An interface for adaptive huffman tree implementations.
 * Derived by FGK and Vitter trees. Used in pimpl idiom by Tree class.
 */
class ITree
{
public:
    virtual std::vector<bit_t> encode(byte_t byte) = 0;
    virtual std::vector<byte_t> decode(const std::vector<bit_t>& bits) = 0;
    virtual ~ITree() = default;
};

} // namespace ahc


#endif // YAAHC_ITREE_HPP_
