#include <stdio.h>
#include "card.h"

int main(){
    ST_cardData_t myCard = {"YOUSSEF MOHAMED MOSTAFA KA", "012345678901234565684", "0122"};

    printf("Card Name Status: %d \n", getCardHolderName(&myCard));
    printf("Card Expiry Status: %d \n", getCardExpiryDate(&myCard));
    printf("Card PAN Status: %d \n", getCardPAN(&myCard));
}