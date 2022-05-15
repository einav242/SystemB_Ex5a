
#include "doctest.h"
#include "OrgChart.hpp"

using namespace ariel;

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
using namespace std;

TEST_CASE("Good input")
{
    OrgChart organization; //first organization
    organization.add_root("President") //add root
        .add_sub("President", "Vice President") //build the organiztion
        .add_sub("Vice President", "Decisions")
        .add_sub("Vice President", "Managers")
        .add_sub("Vice President", "Legal")
        .add_sub("Managers", "Human Resources");
    vector<string> a = {"President", "Vice President", "Decisions", "Managers", "Legal", "Human Resources"};
    unsigned int i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) //check level_order
    {
        CHECK(a[i] == (*it));
        i++;
    }
    a = {"President", "Vice President", "Decisions", "Managers", "Human Resources", "Legal"}; //check preorder
    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK(a[i] == (*it));
        i++;
    }
    a = {"Human Resources", "Decisions", "Managers", "Legal", "Vice President", "President"};
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it) //check rverse
    {
        CHECK(a[i] == (*it));
        i++;
    }
    vector<int> b = {9, 14, 9, 8, 5, 15};
    i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it) //check size of all the item in the level order
    {
        CHECK(b[i] == it->size());
        i++;
    } 
    OrgChart police_organization;
    police_organization.add_root("Chief of police")//second organization
        .add_sub("Chief of police", "Business Manager") //build the organiztion
        .add_sub("Chief of police", "Deputy chief")
        .add_sub("Chief of police", "Administrative support")
        .add_sub("Deputy chief", "Training")
        .add_sub("Deputy chief", "Professional");
    a = {"Chief of police", "Business Manager", "Deputy chief", "Administrative support", "Training", "Professional"};
    i = 0;
    for (auto it = police_organization.begin_level_order(); it != police_organization.end_level_order(); ++it)//check level_order
    {
        CHECK(a[i] == (*it));
        i++;
    }
    a = {"Chief of police", "Business Manager", "Deputy chief", "Training", "Professional", "Administrative support"};
    i = 0;
    for (auto it = police_organization.begin_preorder(); it != police_organization.end_preorder(); ++it)//check preorder
    {
        CHECK(a[i] == (*it));
        i++;
    }
    a = {"Training", "Professional", "Business Manager", "Deputy chief", "Administrative support", "Chief of police"};
    i = 0;
    for (auto it = police_organization.begin_reverse_order(); it != police_organization.reverse_order(); ++it) //check rverse
    {
        CHECK(a[i] == (*it));
        i++;
    }
    b = {15, 16, 12, 22, 8, 12};
    i = 0;
    for (auto it = police_organization.begin_level_order(); it != police_organization.end_level_order(); ++it)//check size of all the item in the level order
    {
        CHECK(b[i] == it->size());
        i++;
    } 

    OrgChart army_organization;
    army_organization.add_root("General")//third organization
        .add_sub("General", "Colonel A") //build the organiztion
        .add_sub("General", "Colonel B")
        .add_sub("Colonel B", "Captain A")
        .add_sub("Colonel B", "Captain B")
        .add_sub("Colonel B", "Captain C");
    a = {"General", "Colonel A", "Colonel B", "Captain A", "Captain B", "Captain C"};
    i = 0;
    for (auto it = army_organization.begin_level_order(); it != army_organization.end_level_order(); ++it)//check level_order
    {
        CHECK(a[i] == (*it));
        i++;
    }
    a = {"General", "Colonel A", "Colonel B", "Captain A", "Captain B", "Captain C"};
    i = 0;
    for (auto it = army_organization.begin_preorder(); it != army_organization.end_preorder(); ++it)//check preorder
    {
        CHECK(a[i] == (*it));
        i++;
    }
    a = {"Captain A", "Captain B", "Captain C", "Colonel A", "Colonel B", "General"};
    i = 0;
    for (auto it = army_organization.begin_reverse_order(); it != army_organization.reverse_order(); ++it) //check rverse
    {
        CHECK(a[i] == (*it));
        i++;
    }
    b = {7, 9, 9, 9, 9, 9};
    i = 0;
    for (auto it = army_organization.begin_level_order(); it != army_organization.end_level_order(); ++it)//check size of all the item in the level order
    {
        CHECK(b[i] == it->size());
        i++;
    } 

    
}

TEST_CASE("Bad use of operators")
{
    OrgChart organization;
    organization.add_root("President");
    //the first input does not exist in the tree
    CHECK_THROWS(organization.add_sub("Entry Level","Vice President")); 
    CHECK_THROWS(organization.add_sub("Marketing","Decisions"));
    CHECK_THROWS(organization.add_sub("Accounting","Legal"));

    OrgChart police_organization;
    police_organization.add_root("Chief of police");
    //the first input does not exist in the tree
    CHECK_THROWS(police_organization.add_sub("Captain","Business Manager"));
    CHECK_THROWS(police_organization.add_sub("Patrol","Professional"));
    CHECK_THROWS(police_organization.add_sub("Investigation","Administrative support"));

    OrgChart army_organization;
    army_organization.add_root("General");
    //the first input does not exist in the tree
    CHECK_THROWS(army_organization.add_sub("Sergeant A","Captain B"));
    CHECK_THROWS(army_organization.add_sub("Sergeant B","Colonel A"));
    CHECK_THROWS(army_organization.add_sub("PrivateA","Captain C"));
}