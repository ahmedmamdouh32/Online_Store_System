#ifndef USERS_H_INCLUDED
#define USERS_H_INCLUDED

#include<iostream>
#include<fstream> //library used for file I/O
#include"Console_color.h"

using namespace std;

struct login_data_node
{
    string username;
    string password;

    login_data_node * next; //to point to next node

};


class users_interfacing
{

private :
    string login_user_password;
    string login_user_name;
    login_data_node *head ; //the head pointer of the list


    bool is_empty_list(); //helper function to check if the list is empty or not

    bool is_username_occupied(string username_input); //helper function th know if Username is already taken or not

    void add_node(string username, string password);  //this function creates new node in list

    void store_file_data_into_list(string data_line); //this function takes string and extract name and password from it then store them in a new node in list

public:

    users_interfacing()
    {
        head = NULL;
        login_user_name="nobody";
    };


    void data_file_init(); //this function stores initial data of users file in the list

    void signup(); //for user signup

    void login(); //for user Login algorithm

    //void show_users_data(); //this function prints the content of the linked list on CMD

    string get_username();

};

#endif // USERS_H_INCLUDED
