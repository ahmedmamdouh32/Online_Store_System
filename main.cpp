#include<iostream>
#include"Users.h"
#include"Helper_Functions.h"
#include"menu.h"
#include<ctime>
#include"receipts.h"
#include"Console_color.h"

using namespace std;




int main()
{

    bool login_signup_stage = 1;
    bool contiune_shopping_flag = 1;
    bool element_is_repeated = 0;
    users_interfacing users; //creating object form the class
    users.data_file_init(); //to save usernames and passwords in the list
    string user_choice;
    int user_choice_quantity;
    menu_interfacing menu;
    menu.menu_file_init();

    while(login_signup_stage)
    {
        cout<<"-------------------------------------------------"<<endl;

        cout<<"Enter (1) to";
        consoleColor(lime,black);
        cout<<" LOGIN"<<endl;
        consoleColor(white,black);
        cout<<"Enter (2) to";
        consoleColor(white_blue,black);
        cout<<" SIGNUP"<<endl;
        consoleColor(white,black);
        //cout<<"Enter (3) to Show users data"<<endl;
        consoleColor(white,black);
        cin>>user_choice;
        cout<<endl;

        if(get_size(user_choice) != 1)  //in case the user entered more than one character
        {
            consoleColor(red,black);
            cout<<"Invalid input !!!"<<endl;
            consoleColor(white,black);
            continue;
        }

        switch (user_choice[0])
        {
        case '1' :
            users.login();
            login_signup_stage = 0; // to end login/sign-up stage
            break;

        case '2' :
            users.signup();
            break;

        default :
            consoleColor(red,black);
            cout<<"Invalid input !!!"<<endl;
            consoleColor(white,black);
        }
    }



    menu_component_node *user_choice_component; //this pointer is used to access component's information that user choose



    menu_interfacing cart; //this element is for the components that user will buy
    while(contiune_shopping_flag)
    {
        menu.show_menu();
        cout<<"Choose Component according to their";
        consoleColor(red,black);
        cout<<" Index";
        consoleColor(white,black);
        cout<<" !!!"<<endl;
        consoleColor(white_cyan,black);
        cout<<"Enter index : ";
        consoleColor(red,black);
        cin>>user_choice;
        consoleColor(white,black);
        while(str2int(user_choice)>menu.get_index())
        {
            consoleColor(red,black);
            cout<<"Invalid input"<<endl;
            consoleColor(white_cyan,black);
            cout<<"Enter index : ";
            consoleColor(white,black);
            cin>>user_choice;
        }


        user_choice_component = menu.return_component_adddress(str2int(user_choice));

        cout<<"How Much [";
        consoleColor(yellow,black);
        cout<<user_choice_component->name;
        consoleColor(white,black);
        cout<<"] do you want ?"<<endl;
        consoleColor(white,black);
        cin>>user_choice_quantity;
        if(cart.is_Empty())
        {
            while(user_choice_quantity > user_choice_component->quantity)
            {
                cout<<"TOO MUCH !!!, the available amount is only "<<user_choice_component->quantity<<" pieces"<<endl;
                cout<<"How Much [";
                consoleColor(yellow,black);
                cout<<user_choice_component->name;
                consoleColor(white,black);
                cout<<"] do you want ?"<<endl;
                consoleColor(white,black);
                cin>>user_choice_quantity;
            }



            cart.add_new_node(user_choice_component->name,user_choice_component->price,
                              user_choice_component->profit,user_choice_quantity);
        }

        else
        {

            menu_component_node *cart_head = cart.get_head(); //this pointer is used to access elements of the cart

            while(cart_head != NULL)
            {
                if(user_choice_component->name == cart_head->name)
                {

                    while(user_choice_quantity + cart_head->quantity > user_choice_component->quantity)
                    {
                        cout<<"TOO MUCH !!!, the available amount is only "<<user_choice_component->quantity<<" pieces"<<endl;
                        cout<<"How Much [";
                        consoleColor(yellow,black);
                        cout<<user_choice_component->name;
                        consoleColor(white,black);
                        cout<<"] do you want ?"<<endl;
                        consoleColor(white,black);
                        cin>>user_choice_quantity;
                    }  //breaking this loop means that the user entered sufficient quantity

                    cart_head->quantity+=user_choice_quantity;  //go now and update the cart with the new quantity
                    element_is_repeated = 1;
                    break;
                }
                else
                {
                    cart_head=cart_head->next;
                }
            }

            if(!element_is_repeated)
            {
                cart.add_new_node(user_choice_component->name,user_choice_component->price,
                                  user_choice_component->profit,user_choice_quantity);
            }
        }

ask_again:
        cout<<"(1) continue shopping"<<endl;
        cout<<"(2) check to proceed"<<endl;
        consoleColor(white_cyan,black);
        cout<<"Your input :";
        consoleColor(white,black);
        cin>>user_choice;
        consoleColor(white,black);
        switch(user_choice[0])
        {
        case '1' :
            element_is_repeated = 0;
            cout<<endl;
            cout<<endl;
            break;

        case '2' :
            contiune_shopping_flag = 0;
            break;

        default :
            consoleColor(red,black);
            cout<<"invalid input"<<endl;
            consoleColor(white,black);
            goto ask_again;
        }
    }

    cart.show_receipt();
    user_receipt_file(users.get_username(),cart.get_head());
    cout<<endl;
    cout<<"Thank you ";
    consoleColor(pink,black);
    cout<<users.get_username()<<endl;
    consoleColor(white,black);

    //for updating the storage

    menu_component_node * cart_node = cart.get_head(); //pointer for cart
    menu_component_node * menu_node = menu.get_head(); //pointer for menu

    while(cart_node != NULL)
    {
        while(menu_node != NULL)
        {
            if(menu_node->name == cart_node->name)
            {
                menu_node->quantity -= cart_node->quantity;
                break;
            }
            else
            {
                menu_node= menu_node->next;
            }
        }
        cart_node = cart_node->next;
        menu_node = menu.get_head(); //to return the pointer to the first element in the menu
    }


    menu.update_menu();

    return 0;
}
