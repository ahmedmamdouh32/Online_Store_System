#include"menu.h"


ofstream MenuFileWrite;  //output file stream
ifstream MenuFileRead;  //input file stream

void menu_interfacing::add_new_node(string comp_name, float price, float profit, int quantity)
{
    menu_component_node *node = new menu_component_node; //pointer for the new node

    node->name = comp_name;
    node->price = price;
    node->profit = profit;
    node->quantity = quantity;
    node->next = NULL;

    if(head == NULL)
    {
        head = node;
        index++;
    }
    else
    {
        menu_component_node *current = head; //temporary pointer to keep head pointer safe
        while(current->next != NULL)
        {
            current = current->next; //to reach end of list
            index++;
        }
        current->next = node; //to link the last node in the list with the new added node
    }
}

void menu_interfacing::store_menu_data_into_list(string data)
{
    string component_name,price_str,quantity_str,profit_str;
    float price,profit;
    int quantity;
    int counter = 0;
    while(data[counter] != ',')  //to store the name of component as a string
    {
        component_name+=data[counter];
        counter++;
    }
    counter++;

    while(data[counter] != ',') //to store the price of component as a string
    {
        price_str+=data[counter];
        counter++;
    }
    counter++;

    while(data[counter] != ',') //to store the quantity of component as a string
    {
        quantity_str+=data[counter];
        counter++;
    }
    counter++;

    while(data[counter] != '\0') //to store the profit of component as a string
    {
        profit_str+=data[counter];
        counter++;
    }


    price = str2float(price_str);
    quantity = str2int(quantity_str);
    profit = str2float(profit_str);


    add_new_node(component_name,price,profit,quantity);


}

void menu_interfacing::menu_file_init()
{
    string data_line;

    //string temp;

    MenuFileRead.open("MenuSheet.csv", ios::in);
    getline(MenuFileRead,data_line);//to skip first row
    while(getline(MenuFileRead,data_line) != 0)
    {
        store_menu_data_into_list(data_line);
    }
    MenuFileRead.close();
}

void menu_interfacing::show_menu()
{

    if(head == NULL)
    {
        cout<<"List is empty !!!"<<endl;
    }
    else
    {
        int counter=1;
        menu_component_node *current = head;
        cout<<"----------MENU----------"<<endl;
        while(current != NULL)
        {
            consoleColor(red,black);
            cout<<"("<<counter<<")";
            consoleColor(yellow,black);
            cout<<current->name<<"  ";
            consoleColor(green,black);
            cout<<current->price<<"LE";
            consoleColor(cyan,black);
            cout<<" ("<<current->quantity<<")"<<endl;
            consoleColor(white,black);

            current = current->next;
            counter++;
        }
        cout<<"------------------------"<<endl;

    }
}

void menu_interfacing::update_menu()
{
    MenuFileWrite.open("MenuSheet.csv",ios::out);
    MenuFileWrite<<"Component name,Price,Quantity,Profit"<<endl;
    menu_component_node *current = head;
    while(current != NULL)
    {
        MenuFileWrite<<current->name<<","<<current->price<<","<<current->quantity<<","<<current->profit<<endl;
        current = current->next;
    }

    MenuFileWrite.close();
}

int menu_interfacing::get_index()
{

    return index;
}

menu_component_node * menu_interfacing::return_component_adddress(int input_index)
{

    if(head == NULL)
    {
        cout<<"Searching in Empty List !!!"<<endl;
        return NULL;
    }

    else
    {
        menu_component_node *current = head; //temporary pointer to keep head pointer safe

        for(int i = 1; i< input_index; i++)
        {
            current = current->next; //to reach the node at the input index
        }
        return current;
    }

}


void menu_interfacing::show_receipt()
{
    float net_price = 0;
    float component_net_price = 0;
    if(head == NULL)
    {
        cout<<"Cart is empty !!!"<<endl;
    }
    else
    {
        menu_component_node *current = head;
        cout<<"-------------Receipt-------------"<<endl;
        cout<<endl;
        cout<<endl;
        while(current != NULL)
        {
            component_net_price = current->quantity * current->price;
            net_price += component_net_price;
            consoleColor(yellow,black);
            cout<<current->name<<"  ";
            consoleColor(white_blue,black);
            cout<<"x"<<current->quantity<<"  ";
            consoleColor(green,black);
            cout<<component_net_price<<" LE"<<endl;
            consoleColor(white,black);
            current = current->next;
        }
        cout<<endl;
        consoleColor(gray,black);
        cout<<"Net Price : ";
        consoleColor(green,black);
        cout<<net_price<<" LE"<<endl;
        consoleColor(white,black);

    }

}


menu_component_node * menu_interfacing::get_head()
{
    return head;
}


bool menu_interfacing::is_Empty()
{
    if (head == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }

}

