#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include<iostream>
#include<string>
#include<fstream>
#include"Helper_Functions.h"
#include"Console_color.h"


using namespace std;

struct menu_component_node  //creating list node
{
    string name;
    float price;
    float profit;
    int quantity;
    menu_component_node * next;
};


class menu_interfacing
{

private :
    menu_component_node* head; //the head pointer of the list
    void store_menu_data_into_list(string data);

    int index;

public:

    menu_interfacing()
    {
        head = NULL;
        index = 1;
    };


    void add_new_node(string comp_name, float price, float profit, int quantity); //this function adds new node to the linked list

    void menu_file_init(); //this function reads the menu and save it in the linked list

    void show_menu(); //this function shows menu in good view

    void update_menu(); //after each selling process this function updates the quantity of components in store

    int get_index();

    menu_component_node *return_component_adddress(int input_index);

    void show_receipt(); //this functions shows name of component and its quantity only

    menu_component_node *get_head();

    bool is_Empty();

};

#endif // MENU_H_INCLUDED
