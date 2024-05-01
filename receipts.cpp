#include "receipts.h"

using namespace std;

ofstream user_receipt;


void user_receipt_file(string username, menu_component_node *my_cart)
{
    float net_profit, net_price, component_net_price = 0;
    string file_username="receipts//";
    file_username+=username;
    file_username+=".txt";
    user_receipt.open(file_username.c_str(),ios::app);
    time_t now = time(0);
    tm *Clock = localtime(&now);

    string months[12]= {"January",
                        "February",
                        "March",
                        "April",
                        "May",
                        "June",
                        "July",
                        "August",
                        "September",
                        "October",
                        "November",
                        "December"
                       };

    user_receipt<<Clock->tm_mday<<"/"<<months[Clock->tm_mon]<<"/"<<Clock->tm_year+1900<<"   ";
    if(Clock->tm_hour > 12)
    {
        user_receipt<<Clock->tm_hour-12<<':' << Clock->tm_min << ':' << Clock->tm_sec <<" PM"<<endl;
    }
    else
    {
        user_receipt<<Clock->tm_hour<<':' << Clock->tm_min << ':' << Clock->tm_sec <<" AM"<<endl;
    }

    menu_component_node *current = my_cart; //temporary pointer to keep head pointer safe

    while(current != NULL)
    {
        component_net_price = current->quantity * current->price;
        net_price += component_net_price;
        net_profit+= component_net_price * current->profit;
        user_receipt<<current->name<<"  "<<"x"<<current->quantity<<"  "<<component_net_price<<" LE"<<endl;
        current = current->next;
    }
    user_receipt<<"Net Price : "<<net_price<<" LE"<<endl;
    user_receipt<<"------------------------------------------------------"<<endl;
    user_receipt.close();

    //for the cashier :

    component_net_price = 0; //clearing the variable

    user_receipt.open("cashier.csv",ios::app);
    user_receipt<<Clock->tm_mday<<"/"<<months[Clock->tm_mon]<<"/"<<Clock->tm_year+1900<<"   ";
    if(Clock->tm_hour > 12)
    {
        user_receipt<<Clock->tm_hour-12<<':' << Clock->tm_min << ':' << Clock->tm_sec <<" PM";
    }
    else
    {
        user_receipt<<Clock->tm_hour<<':' << Clock->tm_min << ':' << Clock->tm_sec <<" AM";
    }

    user_receipt<<",";
    current = my_cart;
    while(current != NULL)
    {
        component_net_price = current->quantity * current->price;
        user_receipt<<current->name<<"  "<<"x"<<current->quantity<<"  "<<component_net_price<<" LE   ";
        current = current->next;
    }

    user_receipt<<","<<net_price<<" LE,"<<username<<","<<net_profit<<" LE"<<endl;

    user_receipt.close();
}
