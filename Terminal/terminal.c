#include <stdio.h>
#include "terminal.h"

int main(){
    ST_cardData_t myCard = {"YOUSSEF MOHAMED MOSTAFA", "01234567890123456", "01/22"};
    ST_terminalData_t termianl = {21.11, 165.54, "23/08/2021"};

    char* newDate = trimDate(&termianl);
    //printf("%s \n", newDate);

}