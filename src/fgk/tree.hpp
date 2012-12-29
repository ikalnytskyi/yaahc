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

#ifndef YAAHC_FGKTREE_HPP_
#define YAAHC_FGKTREE_HPP_

#include <cstddef>
#include <limits>

#include "../itree.hpp"


namespace ahc
{

namespace fgk
{

/*!
 * A FGK node class.
 *
 * Contains original byte, node weight and pointers to the relative nodes.
 * Also contains a number which used for fast-access to the nodes.
 */
class Node;


/*!
 * A Faller-Gallager-Knuth (FGK) tree implementation.
 */
class Tree : public ITree
{
    static const size_t MAX_BYTES = std::numeric_limits<byte_t>::max();
    static const size_t MAX_NODES = 2 * (MAX_BYTES + 1);

public:
    Tree();

    std::vector<bit_t> encode(byte_t byte) override;
    std::vector<byte_t> decode(const std::vector<bit_t>& code) override;

private:
    Node* _escape;                 //! a pointer to the special escape node
    Node* _root;                   //! a tree root
    Node* _leaves[MAX_BYTES + 1];  //! fast access to the leaves by byte
    Node* _nodes[MAX_NODES + 1];   //! fast access to the nodes by number
    Node* _decoder;                //! pointer to the current decoding node
    std::vector<bit_t> _ascii;     //! decoder ASCII buffer

    // internal methods
    // descriptions provides in .cpp file
    std::vector<bit_t> get_code(const Node* node) const;
    void add_new_byte(byte_t byte);
    void update_tree(Node* node);
    void exchange(Node* a, Node* b);
    Node* highest_node(Node* node) const;
};


} // namespace fgk
} // namespace ahc


#endif // YAAHC_FGKTREE_HPP_
