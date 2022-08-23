#include <stdio.h>
#include "card.h"

int main(){
    ST_cardData_t myCard = {"YOUSSEF MOHAMED MOSTAFA", "01234567890123456", "01/06"};
    /*getCardHolderName(&myCard);
    getCardExpiryDate(&myCard);
    getCardPAN(&myCard);*/

    printf("Card Name Status: %d \n", getCardHolderName(&myCard));
    printf("Card Expiry Status: %d \n", getCardExpiryDate(&myCard));
    printf("Card PAN Status: %d \n", getCardPAN(&myCard));
}