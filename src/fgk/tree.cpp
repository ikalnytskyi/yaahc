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

#include <algorithm>

#include "node.hpp"
#include "tree.hpp"


namespace ahc
{
namespace fgk
{

const size_t Tree::MAX_BYTES;
const size_t Tree::MAX_NODES;


Tree::Tree()
    : _escape(new Node(0, MAX_NODES))
    , _root(_escape)
    , _decoder(_root)
{
    std::fill(std::begin(_leaves), std::end(_leaves), nullptr);
    std::fill(std::begin(_nodes), std::end(_nodes), nullptr);

    _nodes[_root->number] = _root;
    _ascii.reserve(8);
}


std::vector<bit_t> Tree::encode(byte_t byte)
{
    std::vector<bit_t> code;

    // if node already encoded
    // note: the `_leaves` array is filled with nullptr by default
    if (_leaves[byte])
    {
        code = get_code(_leaves[byte]);
        update_tree(_leaves[byte]);
    }
    else
    {
        // output code = `escape code` + `ascii code`
        code = get_code(_escape);
        for (size_t i = 0; i < 8 * sizeof(byte_t); ++i)
            code.push_back(0x1 & (byte >> (7 - i)));
        add_new_byte(byte);
    }

    return code;
}


std::vector<byte_t> Tree::decode(const std::vector<bit_t>& code)
{
    std::vector<byte_t> result;

    for (bit_t bit : code)
    {
        // Decode a new byte.
        //
        // This stage occurs when decoder comes to the escape node.
        // That means a new byte occur. So read next 8 bits from input sequence.
        if (_decoder == _escape)
        {
            _ascii.push_back(bit);

            if (_ascii.size() == 8 * sizeof(byte_t))
            {
                // convert a bit sequence into the byte
                byte_t byte = 0;
                for (size_t i = 0; i < 8 * sizeof(byte_t); ++i)
                    byte |= (_ascii[i] << (7 - i));
                _ascii.clear();

                result.push_back(byte);
                add_new_byte(byte);
                _decoder = _root;
            }

            continue;
        }

        //  Go to the next node.
        _decoder = (bit == 1 ? _decoder->left : _decoder->right);

        // Decode an existing node.
        // This stage occurs when decoder comes to a leaf but not the escape node.
        if (!_decoder->left && _decoder != _escape)
        {
            result.push_back(_decoder->byte);
            update_tree(_leaves[_decoder->byte]);
            _decoder = _root;
        }
    }

    return result;
}


std::vector<byte_t> Tree::get_code(const Node* node) const
{
    // note: the left child represents as `1` bit
    //       while the `right` child -- `0` bit
    std::vector<bit_t> code;

    for (; node != _root; node = node->parent)
        code.push_back(node->parent->left == node);
    std::reverse(begin(code), end(code));

    return code;
}


void Tree::add_new_byte(byte_t byte)
{
    // create a node with data
    _escape->left  = new Node(byte, _escape->number - 1, 0, _escape);
    // create a new escape node
    _escape->right = new Node(   0, _escape->number - 2, 0, _escape);

    // save fast-access pointers to the nodes
    _leaves[byte] = _escape->left;
    _nodes[_escape->left->number] =  _escape->left;
    _nodes[_escape->right->number] = _escape->right;
    _escape = _escape->right;

    update_tree(_leaves[byte]);
}


void Tree::update_tree(Node* node)
{
    for (; node != nullptr; node = node->parent)
    {
        Node* highest = highest_node(node);
        exchange(node, highest);
        node->weight++;
    }
}


void Tree::exchange(Node* a, Node* b)
{
    // avoid unnecessary and danger situations
    if (a == _root || b == _root || a == b || a->parent == b || b->parent == a)
        return;

    // swap subtrees
    if (a->parent->left == a && b->parent->left == b)
        std::swap(a->parent->left, b->parent->left);
    else if (a->parent->left == a && b->parent->right == b)
        std::swap(a->parent->left, b->parent->right);
    else if (a->parent->right == a && b->parent->left == b)
        std::swap(a->parent->right, b->parent->left);
    else if (a->parent->right == a && b->parent->right == b)
        std::swap(a->parent->right, b->parent->right);

    std::swap(_nodes[a->number], _nodes[b->number]);
    std::swap(a->number, b->number);
    std::swap(a->parent, b->parent);
}


Node* Tree::highest_node(Node* node) const
{
    Node* highest = node;

    for (size_t i = node->number + 1; i <= MAX_NODES
         && _nodes[i]->weight == node->weight; ++i)
    {
        highest = _nodes[i];
    }

    return highest;
}

} // namespace fgk
} // namespace ahc
