#include <stdio.h>
#include "server.h"

int main(){
    ST_transaction_t myTrans = {
        {"YOUSSEF MOHAMED MOSTAFA", "01234567890123456", "08/22"}, 
        {22.12, 1005.2, "21/08/2021"}, 
        IDLE, 
        0
    };

    isValidAccount(&myTrans.cardHolderData);
}