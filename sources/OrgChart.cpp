#include "OrgChart.hpp"
using namespace std;
namespace ariel
{


    OrgChart &OrgChart::add_root(string const &value)
    {
        if (root == nullptr) //if there is not root create one
        {
            this->root = new Node(value);
        }
        else
        {
            this->root->info = value; //if there is a root change the value
        }
        this->root->depth=0;
        return *this;
    }

    OrgChart &OrgChart::add_sub(string const &value1, string const &value2)
    {
        bool check = false;
        unsigned int i;
        for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it) //we will go through the whole tree with the iterator to find the right node
        {
            if (*it == value1)
            {
                Node *child = new Node(value2); //create a new node
                if (it.pointer_to_current_node->child== nullptr) //if this is the first child we will define him as a child
                {
                    it.pointer_to_current_node->child = child;
                }
                else //if there is already a child in this vertex then we will put the child as the brother of the last brother we get in
                {
                    Node *tmp = it.pointer_to_current_node->child;
                    while (tmp->brother != nullptr)
                    {
                        tmp = tmp->brother;
                    }
                    tmp->brother = child;
                }
                child->parent=it.pointer_to_current_node; //We will define the parent
                child->depth=it.pointer_to_current_node->depth+1;
                check = true; //we dont need to throw exception
                break;
            }
        }
        if (!check) //If we did not find the requested Node we would throw an exception
        {
            throw std::invalid_argument("value does not exit");
        }
        return *this;
    }

    void OrgChart::iterator::create_vec_level_order(Node *ptr = nullptr)
    {
        /*
            To go through the tree in this method we will use a queue, 
            each time we enter a Node and its children and 
            we take out the first Node we entered
        */
        if (ptr != nullptr)
        {
            vector<Node *> queue;
            this->iter.clear();
            queue.push_back(this->pointer_to_current_node);
            this->iter.push_back(this->pointer_to_current_node);
            while (!queue.empty())
            {
                Node *tmp = queue[0];
                queue.erase(queue.begin());
                if (tmp->child == nullptr)
                {
                    continue;
                }
                tmp = tmp->child;
                this->iter.push_back(tmp);
                queue.push_back(tmp);
                while (tmp->brother != nullptr)
                {
                    tmp = tmp->brother;
                    this->iter.push_back(tmp);
                    queue.push_back(tmp);
                }
            }
        }
    }

    void OrgChart::iterator::create_vec_reverse_order(Node *ptr = nullptr)
    {
        /*
         To go through the tree in this method we will use a queue only this
         time every time we enter to the vector a node we will enter from 
        the beginning and so whoever enters last will be the first
        */
        if (ptr != nullptr)
        {
            this->iter.clear();
            vector<Node *> queue;
            queue.push_back(this->pointer_to_current_node);
            this->iter.insert(this->iter.begin(), this->pointer_to_current_node);
            while (!queue.empty())
            {
                Node *tmp = queue[queue.size() - 1];
                queue.erase(queue.begin() + (int)queue.size() - 1);
                if (tmp->child == nullptr)
                {
                    continue;
                }
                tmp = tmp->child;
                this->iter.insert(this->iter.begin(), tmp);
                queue.push_back(tmp);
                unsigned int i = 1;
                while (tmp->brother != nullptr)
                {
                    tmp = tmp->brother;
                    this->iter.insert(this->iter.begin() + i, tmp);
                    queue.push_back(tmp);
                    i++;
                }
            }
            unsigned int i=0;
            while (i<this->iter.size()-1 && this->iter[i]->depth<this->iter[i+1]->depth)
            {
                Node *tmp=this->iter[i];
                this->iter[i]=this->iter[i+1];
                this->iter[i+1]=tmp;
                i++;
            }
            
            
            this->pointer_to_current_node = this->iter[0];
        }
    }

    void OrgChart::iterator::create_vec_preorder(Node *ptr = nullptr)
    {
        /*
        To go through the tree in this method we will use a stack, 
        which means that each time we insert 
        the Node and its children and remove the one we inserted last.
        */
        if (ptr != nullptr)
        {
            this->iter.clear();
            vector<Node *> stack;
            stack.insert(stack.begin(), this->pointer_to_current_node);
            while (!stack.empty())
            {
                Node *tmp = stack[0];
                this->iter.push_back(tmp);
                stack.erase(stack.begin());
                if (tmp->child == nullptr)
                {
                    continue;
                }
                tmp = tmp->child;
                stack.insert(stack.begin(), tmp);
                unsigned int i = 1;
                while (tmp->brother != nullptr)
                {
                    tmp = tmp->brother;
                    stack.insert(stack.begin() + i, tmp);
                    i++;
                }
            }
        }
    }

    OrgChart::iterator &OrgChart::iterator::operator++() //We will first advance the index and then send the iterator back
    {
        this->index++;
        this->pointer_to_current_node = this->iter[this->index];
        return *this;
    }

    OrgChart::iterator OrgChart::iterator::operator++(int a) //We will first send the iterator back and then advance the index
    {
        iterator tmp=*this;
        index++;
        return tmp;
    }

    bool OrgChart::iterator::operator==(const iterator &rhs) const //We will check if the two pointers are points for the same address
    {
        return pointer_to_current_node == rhs.pointer_to_current_node;
    }

    bool OrgChart::iterator::operator!=(const iterator &rhs) const
    {
        return pointer_to_current_node != rhs.pointer_to_current_node;
    }

    string &OrgChart::iterator::operator*() //return the value of the current node
    {
        return pointer_to_current_node->info;
    }

    string *OrgChart::iterator::operator->() const //return a pointer to the value of the current node
    {
        return &(this->pointer_to_current_node->info);
    }

    OrgChart::iterator OrgChart::begin() //so we can go throw the tree
    {
        return iterator{"level", root};
    }

    OrgChart::iterator OrgChart::end()
    {
        return iterator{"level", nullptr};
    }

    OrgChart::iterator OrgChart::begin_level_order()
    {
        return iterator{"level", root};
    }

    OrgChart::iterator OrgChart::end_level_order()
    {
        return iterator{"level", nullptr};
    }

    OrgChart::iterator OrgChart::begin_reverse_order()
    {
        return iterator{"reverse", root};
    }

    OrgChart::iterator OrgChart::reverse_order()
    {
        return iterator{"reverse", nullptr};
    }

    OrgChart::iterator OrgChart::begin_preorder()
    {
        return iterator{"preorder", root};
    }

    OrgChart::iterator OrgChart::end_preorder()
    {
        return iterator{"preorder", nullptr};
    }

    ostream &operator<<(ostream &out, const OrgChart &a)
    {
        vector<OrgChart:: Node *> stack;
        stack.insert(stack.begin(), a.root);
        a.root->depth=0;
        while (!stack.empty())
        {
            OrgChart:: Node *tmp = stack[0];
            out<<"("<<tmp->depth<<")"<<tmp->info<<"-->";
            stack.erase(stack.begin());
            if (tmp->child == nullptr)
            {
                out<<"nullptr\n\n";
                unsigned int s=(unsigned int)stack[0]->depth*6+stack[0]->parent->info.size();
                for(unsigned int i=0;i<s;i++)
                {
                    out<<" ";
                }
                if(!stack.empty())
                {
                     out<<"-->";
                }
                continue;
            }
            tmp = tmp->child;
            tmp->depth=tmp->parent->depth+1;
            stack.insert(stack.begin(), tmp);
            unsigned int i = 1;
            while (tmp->brother != nullptr)
            {
                tmp = tmp->brother;
                stack.insert(stack.begin() + i, tmp);
                i++;
            }
        }
        return out;
    }

}