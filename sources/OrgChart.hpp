#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <deque>
#include <iterator>
#include <iostream> // std::cout
#include <vector>
using namespace std;
#pragma once

namespace ariel
{
    class OrgChart
    {
        class Node
        {
        public:
            string info;
            Node *child;
            Node *brother;
            Node *parent;
             Node(string const& data)
            {
                this->info=data;
                this->brother=nullptr;
                this->child=nullptr;
                this->parent=nullptr;
            }
        };

    public:
        Node *root;
        OrgChart()
        {
            this->root=nullptr;
        }
        OrgChart &add_root(string const &value);

        OrgChart &add_sub(string const &value1, string const &value2);

        class iterator
        {
        public:
            vector<Node *> iter;
            Node *pointer_to_current_node;
            unsigned int index;
            string type;
            iterator(string const& order,Node *ptr) //when we call the iterator we will also send the data transfer method
            {
                this->pointer_to_current_node=ptr;
                this->index = 0;
                this->type=order;
                if(this->type=="level")
                {
                    create_vec_level_order(ptr);
                }
                if(this->type=="reverse")
                {
                    create_vec_reverse_order(ptr);
                }
                if(this->type=="preorder")
                {
                    create_vec_preorder(ptr);
                }
            }
            void create_vec_level_order(Node *ptr);

            void create_vec_reverse_order(Node *ptr);

            void create_vec_preorder(Node *ptr);

            iterator &operator++();

            iterator operator++(int a);

            bool operator==(const iterator &rhs) const;

            bool operator!=(const iterator &rhs) const;

            string &operator*();

            string *operator->() const;

        };

        iterator begin();

        static iterator end();

        iterator begin_level_order();

        static iterator end_level_order();

        iterator begin_reverse_order();

        static iterator reverse_order();

        iterator begin_preorder();

        static iterator end_preorder();
  
        friend ostream &operator<<(ostream &out, const OrgChart &a);

    };
}