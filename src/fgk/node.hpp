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

#ifndef YAAHC_FGKNODE_HPP_
#define YAAHC_FGKNODE_HPP_

#include <ahc/common.hpp>


namespace ahc
{
namespace fgk
{

struct Node
{
    byte_t byte;
    int16_t number;
    int64_t weight;

    Node* parent;
    Node* left;
    Node* right;

    Node(byte_t byte_,
         int number_,
         int weight_ = 0,
         Node* parent_ = nullptr,
         Node* left_ = nullptr,
         Node* right_ = nullptr) noexcept
        : byte(byte_)
        , number(number_)
        , weight(weight_)
        , parent(parent_)
        , left(left_)
        , right(right_)
    { }
};

} // namespace fgk
} // namespace ahc

#endif // YAAHC_FGKNODE_HPP_
