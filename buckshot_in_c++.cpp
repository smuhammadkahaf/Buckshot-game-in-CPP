#include <iostream>
#include <windows.h>
#include <time.h>
#include <algorithm>

using namespace std;

int gun[8];
int live=0,blank=0,total_bullets=live+blank;
int health_player=5,health_dealer=5,gun_damage=1;
int inventory_player[4],inventory_dealer[4];
int player_stock =0,dealer_stock=0;
char current_player,dealer_handcuff=' ',player_handcuff=' ';
int gun_index=0,skip_dealer=1,skip_player=1;
bool turn;


//functions

int crand(int x)    //this function return random  numbers from 0 to x-1,
{
    int y;
    y=rand();
    y=y%x;
    return y;
}
void load_gun()//this function will load the gun with blank and live rounds and shuffle them
{
    //---> In gun 0 means empty slot,     1 means live, 2 means blank bullet
    srand(time(0));
    int y= crand(3);
    if (y==0)
    {
        gun[0]=1;
        gun[1]=2;
        gun[2]=1;
        gun[3]=2;
        gun[4]=2;
        gun[5]=1;
        gun[6]=2;
        gun[7]=1;
        live=4;
        blank=4;
    }
    else if(y==1)
    {
        gun[0]=2;
        gun[1]=1;
        gun[2]=1;
        gun[3]=2;
        gun[4]=2;
        gun[5]=1;
        gun[6]=2;
        gun[7]=2;
        live=3;
        blank=5;
    }
    else
    {
        gun[0]=2;
        gun[1]=1;
        gun[2]=2;
        gun[3]=1;
        gun[4]=1;
        gun[5]=1;
        gun[6]=2;
        gun[7]=1;
        live=5;
        blank=3;
    }

    total_bullets=live+blank;
    cout<<live<<" Live Bullets"<<endl;
    cout<<blank<<" Blank Bullets"<<endl;
    char x;// x used to hold the program for user response
    cout<<"Enter any character to shuffle the bullets"<<endl;
    cin >> x;

    cout<<endl<<"Reloading... and distributing items..."<<endl;
    Sleep(2000);

    random_shuffle(&gun[0],&gun[8]);
}
void item_generator()//this function randomly distribute 4 type of product to both players
{
    int y;

    //distribute 3 or less products to player max inventory size 8
    for(int i=0; (i<3) && (player_stock<8) ; i++)
    {
        y=crand(4);
        if (y==0)
        {
            inventory_player[0]++; //cutter

        }
        else if(y==1)
        {
            inventory_player[1]++; //handcuffs

        }
        else if(y==2)
        {
            inventory_player[2]++; //spy glass
        }
        else
        {
            inventory_player[3]++;//health kit
        }

        player_stock++;
    }
    //distribute 3 or less items to dealer

    for(int i=0; (i<3) && (dealer_stock<8); i++)
    {
        y=crand(4);
        if(y==0)
        {
            inventory_dealer[0]++;//cutter
        }
        else if(y==1)
        {
            inventory_dealer[1]++;//handcuff
        }
        else if(y==2)
        {
            inventory_dealer[2]++;//spy glass
        }
        else
        {
            inventory_dealer[3]++;//health item
        }
        dealer_stock++;
    }
}
void spy_glass(int x)//peek what inside the current shell
{
    cout<<endl<<"<Checking Current Shell...>"<<endl;
    if(gun[x]==1)
    {
        cout<<"Live Round Be Careful"<<endl;
    }
    else if(gun[x]==2)
    {
        cout<<"Blank Round Just Chill"<<endl;
    }
    Sleep (3000);
    system("cls");
}
void cutter()//take 2 health from the enemy or double the damage
{
    gun_damage=2;
}
void health_kit()// recover health by 1 , max health =5
{
    if ((current_player=='p') && (health_player<5))
    {
        health_player++;
    }
    else if ((current_player=='d') && (health_dealer<5))
    {
        health_dealer++;
    }
}

void display();//prototype for the display function

bool player_input()//take input from the player or gamer
{
    system("cls");
    system("color 02");
    display();
    cout<<"gamer turns:"<<endl;
    char choice;
    cout<<"Enter option number : ";
    cin >>choice;

    switch(choice)
    {
    case '1'://user want to double damage
    {
        if(inventory_player[0]>0)
        {
            cout<<"using item..."<<endl;
            gun_damage=2;
            Sleep(1000);
            inventory_player[0]--;
            player_stock--;
        }
        else
        {
            cout<<"You don't have the item."<<endl;
            Sleep (1000);
        }
        return true;
        break;
    }
    case '2'://user want to skip the next turn of the enemy
    {
        if (inventory_player[1]>0)
        {
            if (skip_dealer==1)
            {
                skip_dealer=2;
                dealer_handcuff='H';
                inventory_player[1]--;
                player_stock--;

            }
            else if(skip_dealer==3)
            {
                cout<<"you can not use the item consecutively"<<endl;
                Sleep(1500);
            }

        }
        else
        {
            cout<<"you don't have the item"<<endl;
            Sleep(1500);
        }
        return true;
        break;
    }
    case '3'://user want to check the current shell
    {
        if(inventory_player[2]>0)
        {
            spy_glass(gun_index);
            inventory_player[2]--;
            player_stock--;
        }
        else
        {
            cout<<"you don't have the item."<<endl;
            Sleep(1000);
        }
        return true;
        break;
    }
    case '4'://recover health
    {
        if (inventory_player[3]>0)
        {
            health_kit();
            inventory_player[3]--;
            player_stock--;
        }
        else
        {
            cout<<"You don't have the item."<<endl;
        }
        return true;
        break;
    }
    case '5'://shoot
    {
        while (true)
        {
            char x;
            system("cls");
            display();
            cout<<"1. shoot enemy"<<endl;
            cout<<"2. shoot you"<<endl;
            cin >>x;

            if (x=='1')
            {
                if (gun[gun_index]==1)
                {
                    gun_index++;
                    health_dealer-=gun_damage;
                    live--;
                    total_bullets--;
                    cout<<"It was live enemy health down"<<endl;
                    Sleep(1500);
                    gun_damage=1;
                    return false;
                }
                else if(gun[gun_index]==2)
                {
                    gun_index++;
                    blank--;
                    total_bullets--;
                    cout<<"it was blank"<<endl;
                    Sleep(1500);
                    gun_damage=1;
                    return false;
                }
            }
            else if(x=='2')
            {
                if (gun[gun_index]==1)
                {
                    gun_index++;
                    health_player-=gun_damage;
                    live--;
                    total_bullets--;
                    cout<<"It was live your health down"<<endl;
                    Sleep(1500);
                    gun_damage=1;
                    return false;
                }
                else if(gun[gun_index]==2)
                {
                    gun_index++;
                    blank--;
                    total_bullets--;
                    cout<<"it was blank"<<endl;
                    Sleep(1500);
                    gun_damage=1;
                    return true;
                }
            }
            else
            {
                cout<<"invalid choice";
                Sleep(1500);
            }

        }
        break;
    }
    default:
    {
        cout<<"invalid choice";
        Sleep(1500);
        return true;
    }

    }
}

bool dealer_input()//take input from the dealer
{
    system("cls");
    system("color 04");
    display();
    cout<<"Dealer turns:"<<endl;
    char choice;
    cout<<"Enter option number : ";
    cin >>choice;

    switch(choice)
    {
    case '1'://double damage
    {
        if(inventory_dealer[0]>0)
        {
            cout<<"using item..."<<endl;
            gun_damage=2;
            Sleep(1000);
            inventory_dealer[0]--;
            dealer_stock--;
        }
        else
        {
            cout<<"You don't have the item."<<endl;
            Sleep (1000);
        }
        return true;
        break;
    }
    case '2'://handcuffs
    {
        if (inventory_dealer[1]>0)
        {
            if (skip_player==1)
            {
                skip_player=2;
                inventory_dealer[1]--;
                dealer_stock--;
                player_handcuff='H';

            }
            else
            {
                cout<<"You can not use the item consecutively"<<endl;
                Sleep(1500);
            }
        }

        else
        {
            cout<<"You don't have item"<<endl;
            Sleep(1500);
        }

        return true;
        break;
    }
    case '3'://peek inside the shell
    {
        if(inventory_dealer[2]>0)
        {
            spy_glass(gun_index);
            inventory_dealer[2]--;
            dealer_stock--;
        }
        else
        {
            cout<<"you don't have the item."<<endl;
            Sleep(1000);
        }
        return true;
        break;
    }
    case '4'://health kit
    {
        if (inventory_dealer[3]>0)
        {
            health_kit();
            inventory_dealer[3]--;
            dealer_stock--;
        }
        else
        {
            cout<<"You don't have the item."<<endl;
        }
        return true;
        break;
    }
    case '5'://shoot
    {
        while (true)
        {
            char x;
            system("cls");
            display();
            cout<<"1. shoot enemy"<<endl;
            cout<<"2. shoot you"<<endl;
            cin >>x;

            if (x=='1')
            {

                if (gun[gun_index]==1)
                {
                    gun_index++;
                    health_player-=gun_damage;
                    live--;
                    total_bullets--;
                    cout<<"It was live enemy health down"<<endl;
                    Sleep(1500);
                    gun_damage=1;
                    return false;
                }
                else if(gun[gun_index]==2)
                {
                    gun_index++;
                    blank--;
                    total_bullets--;
                    cout<<"it was blank"<<endl;
                    Sleep(1500);
                    gun_damage=1;
                    return false;
                }
            }
            else if(x=='2')
            {
                if (gun[gun_index]==1)
                {
                    gun_index++;
                    health_dealer-=gun_damage;
                    live--;
                    total_bullets--;
                    cout<<"It was live your health down"<<endl;
                    Sleep(1500);
                    gun_damage=1;
                    return false;
                }
                else if(gun[gun_index]==2)
                {
                    gun_index++;
                    blank--;
                    total_bullets--;
                    cout<<"it was blank"<<endl;
                    Sleep(1500);
                    gun_damage=1;
                    return true;
                }
            }
            else
            {
                cout<<"invalid choice";
                Sleep(1500);
            }

        }
        break;
    }
    default:
    {
        cout<<"invalid choice";
        return true;
    }

    }
}

/*
*/
int main ()
{
    srand(time(0));
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);//to maximize the window

load://to reload the gun
    display();
    load_gun();
    item_generator();
    display();
    gun_index=0;

    dealer_handcuff=' ';
    player_handcuff=' ';

    while(true)
    {
        skip_dealer=1;
gamer://to  skip the dealer turn

        turn=true;
        while (turn)
        {
            current_player='p';
            turn=player_input();
            if(health_dealer<=0 || health_player<=
                    0)
            {
                goto game_over;
            }
            if (total_bullets==0)
            {
                goto load;
            }
        }

        if(skip_dealer==2)
        {
            skip_dealer=3;
            goto gamer;
        }

        skip_dealer=1;
        dealer_handcuff=' ';


        skip_player=1;
dealer://to skip the gamer turn

        turn=true;
        while(turn)
        {
            current_player='d';
            turn=dealer_input();
            if(health_dealer<=0 || health_player<=0)
            {
                goto game_over;
            }
            if(total_bullets==0)
            {
                goto load;
            }
        }
        if(skip_player==2)
        {
            skip_player=3;
            goto dealer;
        }
        skip_player=1;
        player_handcuff=' ';


    }
game_over:
    display();


    if(health_dealer<=0)
    {
        cout<<"gamer wins";
    }
    else if(health_player<=0)
    {
        cout<<"dealer wins";
    }

    return 0;
}


void display()
{
    system("cls");
    cout<<"#####################################################################################################################"<<endl;
    cout<<"# Gamer "<<player_handcuff<<"                                      Health = "<<health_player<<" # Dealer "<<dealer_handcuff<<"                                     Health = "<<health_dealer<<" #"<<endl;
    cout<<"#                                                         #                                                         #"<<endl;
    cout<<"# Items/Options                             Inventory = "<<player_stock<<" # Items/Options                             Inventory = "<<dealer_stock<<" #"<<endl;
    cout<<"#                                                         #                                                         #"<<endl;
    cout<<"# 1. Cutter (double damage)         = "<<inventory_player[0]<<"                   # 1. cutter (double damage)         = "<<inventory_dealer[0]<<"                   #"<<endl;
    cout<<"# 2. Hand Cuffs (skip dealer turn)  = "<<inventory_player[1]<<"                   # 2. Hand Cuffs (skip gamer turn)   = "<<inventory_dealer[1]<<"                   #"<<endl;
    cout<<"# 3. Spy Glass (peek inside gun)    = "<<inventory_player[2]<<"                   # 3. Spy Glass (peek inside gun)    = "<<inventory_dealer[2]<<"                   #"<<endl;
    cout<<"# 4. Health Kit (recover health)    = "<<inventory_player[3]<<"                   # 4. Health Kit (recover health)    = "<<inventory_dealer[3]<<"                   #"<<endl;
    cout<<"# 5. Take Gun And Shoot Immediately                       # 5. Take Gun And Shoot Immediately                       #"<<endl;
    cout<<"#                                                         #                                                         #"<<endl;
    cout<<"#####################################################################################################################"<<endl;
}









