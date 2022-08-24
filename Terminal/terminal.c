#include <stdio.h>
#include "terminal.h"

int main(){
    ST_cardData_t myCard = {"YOUSSEF MOHAMED MOSTAFA", "01234567890123456", "09/21"};
    ST_terminalData_t terminal = {-221.11, -165.54, "23/08/2021"};

    printf("Card Name Status: %d \n", getCardHolderName(&myCard));
    printf("Card Expiry Status: %d \n", getCardExpiryDate(&myCard));
    printf("Card PAN Status: %d \n", getCardPAN(&myCard));
    printf("Transaction Date Status: %d \n", getTransactionDate(&terminal));
    printf("Card Expiry Status: %d \n", isCardExpired(&myCard, &terminal));
    printf("Card Validity Status: %d \n", isValidCardPAN(&myCard));
    printf("Transaction Amount Status: %d \n", getTransactionAmount(&terminal));
    printf("Amount Status: %d \n", isBelowMaxAmount(&terminal));
    printf("Set Max Amount: %d \n", setMaxAmount(&terminal));
}