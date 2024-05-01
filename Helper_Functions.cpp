#include"Helper_Functions.h"


unsigned short get_size(string data)
{
    unsigned short counter =0;

    while(data[counter] != '\0')
    {
        counter++;
    }
    return counter;
}


long long power(int number, int power)
{
    long long answer = 1;
    for(int i=0 ; i<power ; i++)
    {
        answer*=number;
    }
    return answer;
}


int str2int(string number)
{
    int answer = 0;
    unsigned short Size = get_size(number);
    int digit = 0;
    for(int i=0 ; i<Size ; i++)
    {
        digit = number[i] - 0x30; //to be integer value
        answer+= digit*power(10,Size-i-1);
    }
    return answer;
}


float str2float(string number)
{
    float answer;

    int counter = 0;
    while(number[counter] != '\0')
    {
        if(number[counter] == '.')
        {
            goto Start_Conversion;
        }
        counter++;
    }

    answer = float(str2int(number));
    return answer;

Start_Conversion:
    counter = 0;
    unsigned short Size = get_size(number);

    string left,right;

    while(number[counter] != '.')
    {
        left+=number[counter];
        counter++;
    }
    counter++;

    answer = str2int(left);

    while(number[counter] != '\0')
    {
        right+=number[counter];
        counter++;
    }

    answer+= float(str2int(right)) / power(10,get_size(right));

    return answer;
}




