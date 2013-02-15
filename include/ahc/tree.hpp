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

#ifndef YAAHC_TREE_HPP_
#define YAAHC_TREE_HPP_

#include <vector>
#include <memory>

#include "common.hpp"


namespace ahc
{

/*!
 * The base class for different implementations.
 */
class ITree;


/*!
 * The algorithm type.
 * Just FGK (Faller-Gallager-Knuth) algorithm supports now.
 */
enum class Algorithm : byte_t { FGK };


/*!
 * An adaptive huffman tree.
 *
 * There are two implementations of this tree: FGK and Vitter.
 * This class is a bridge for using this implementations.
 *
 * Just send an algorithm type to the Tree constructor for
 * choosing desired method.
 */
class DLL_PUBLIC Tree
{
public:
    Tree (Algorithm algorithm_type = Algorithm::FGK);
    ~Tree();

    std::vector<bit_t> encode(byte_t byte);
    std::vector<byte_t> decode(const std::vector<bit_t>& bits);

private:
    // a pimpl idiom, which very useful for libraries
    std::unique_ptr<ITree> _impl;
};

} // namespace ahc

#endif // YAAHC_TREE_HPP_
