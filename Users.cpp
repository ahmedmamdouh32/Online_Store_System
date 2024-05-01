#include "Users.h"

using namespace std;

ofstream UserFileWrite;  //output file stream
ifstream UserFileRead;  //input file stream


bool users_interfacing::is_empty_list()
{
    if(head == NULL)
    {
        return true; //the list is empty
    }
    else
    {
        return false; //the list is full
    }
}

bool users_interfacing::is_username_occupied(string username_input)
{
    if(head == NULL)
    {
        return false; //if the list is empty so the name is not occupied
    }

    else
    {
        login_data_node *current = head;
        while(current != NULL)
        {
            if(current->username == username_input)
            {
                login_user_password = current->password; //to get the password for login property
                return true; //the name is occupied in this case so return true
            }
            current = current->next;
        }
    }
    return false; //reaching this case means that the name is not taken
}

void users_interfacing::add_node(string username, string password)
{
    login_data_node *node = new login_data_node; // define new pointer to node
    node->username = username;
    node->password = password;
    node->next = NULL;
    if(head == NULL)
    {
        head = node;
    }
    else
    {
        login_data_node *current = head; //pointer to save head node address
        while(current->next != NULL)
        {
            current = current->next; //the current pointer points to address of next node
        }
        current->next = node;
    }
}

void users_interfacing::store_file_data_into_list(string data_line)
{
    string name;
    string password;
    int index = 0;

    while(data_line[index] != ' ')
    {
        name=name + data_line[index];
        index++;
    }
    index++;
    while(data_line[index] != '\0')
    {
        password=password + data_line[index];
        index++;
    }
    add_node(name,password);
}

void users_interfacing::data_file_init()
{

    string data_line; //to read data from file and store it line by line

    UserFileRead.open("Users.txt", ios::in);
    while(getline(UserFileRead,data_line) != 0)
    {
        store_file_data_into_list(data_line);
    }
    UserFileRead.close();
}

void users_interfacing::signup()
{
    bool username_check = 1; //variable to check if the user name is already taken before or not
    string name,password;

    while(username_check == 1)
    {
        cout<<"Enter your name : ";
        cin>>name;
        if(is_username_occupied(name) == false)
        {
            username_check = 0;
        }
        else
        {
            consoleColor(red,black);
            cout<<"Username is already taken !!"<<endl;
            consoleColor(white,black);
        }
    }

    cout<<"Enter Password : ";
    cin>>password;

    add_node(name,password);

    UserFileWrite.open("Users.txt", ios::app); //(app) to make all outputs at the end of file
    UserFileWrite<<name<<' '<<password<<endl; //to print data in Users file
    UserFileWrite.close();

}


void users_interfacing::login()
{

    if(is_empty_list() == true)
    {
        cout<<"List of users is empty !!!"<<endl;
        return ;
    }
    string username,password;
    bool username_check = false;
    bool password_check = false;
    // ask for Username :
    while(username_check == false)
    {
        cout<<"Enter username : ";
        cin>>username;
        if(is_username_occupied(username) == true)
        {
            username_check = true;
        }
        else
        {
            consoleColor(red,black);
            cout<<"Username not found !!!"<<endl;
            consoleColor(white,black);
        }
    }

    //ask for Password :


    while(password_check == false)
    {
        cout<<"Enter Password : ";
        cin>>password;
        if(password == login_user_password)
        {
            password_check = true;
        }
        else
        {
            consoleColor(red,black);
            cout<<"Incorrect Password !!!"<<endl;
            consoleColor(white,black);
        }
    }
    cout<<"Welcome Back "<<username<<endl;//final destination
    login_user_name = username;
}

/*
void users_interfacing::show_users_data()
    {



        if(head == NULL)
        {
            cout<<"List is empty !!!"<<endl;
        }
        else
        {
            login_data_node *current = head;
            while(current != NULL)
            {
                cout<<"Username : "<<current->username<<"    Password : "<<current->password<<endl;
                current = current->next;
            }
        }
    }


*/

string users_interfacing::get_username()
{
    return login_user_name;
}

