#include "app.h"

void appStart(){
    /****************** CARD *******************/
    /*
    //ST_cardData_t myCard = {"YOUSSEF MOHAMED MOSTAFA", "1235445", "0122"};
    ST_cardData_t myCard = {"YOUSSEF MOHAMED MOSTAFA", "01234567890123456", "01/22"};
    

    printf("Card Name Status: %d \n", getCardHolderName(&myCard));
    printf("Card Expiry Status: %d \n", getCardExpiryDate(&myCard));
    printf("Card PAN Status: %d \n", getCardPAN(&myCard));

    getCardHolderNameTest();
    getCardExpiryDateTest();
    getCardPANTest();
    */

    /***************** TERMINAL ******************/
    /*
    ST_cardData_t myCard = {"YOUSSEF MOHAMED MOSTAFA", "01234567890123456", "09/22"};
    ST_terminalData_t terminal = {21.11, 2000, "23/10/2021"};
    
    printf("Card Name Status: %d \n", getCardHolderName(&myCard));
    printf("Card Expiry Status: %d \n", getCardExpiryDate(&myCard));
    printf("Card PAN Status: %d \n", getCardPAN(&myCard));
    printf("Transaction Date Status: %d \n", getTransactionDate(&terminal));
    printf("Card Expiry Status: %d \n", isCardExpired(&myCard, &terminal));
    //printf("Card Validity Status: %d \n", isValidCardPAN(&myCard));
    printf("Transaction Amount Status: %d \n", getTransactionAmount(&terminal));
    printf("Amount Status: %d \n", isBelowMaxAmount(&terminal));
    printf("Set Max Amount: %d \n", setMaxAmount(&terminal, 185.1));
    
    
    getTransactionDateTest();
    isCardExpriedTest();
    getTransactionAmountTest();
    isBelowMaxAmountTest();
    setMaxAmountTest();
    */

   /******************* server **********************/
    
    ST_transaction_t myTrans = {
        {"YOUSSEF MOHAMED MOSTAFA", "01234567890123456", "08/22"}, 
        {22.12, 1005.2, "21/08/2021"}, 
        IDLE, 
        0
    };
    /*
    recieveTransactionData(&myTrans);
    recieveTransactionData(&myTrans);
    saveTransaction(&myTrans);
    listSavedTransactionsTest();*/
    
    getTransaction();
    listSavedTransactionsTest();
    recieveTransactionDataTest();
    isValidAccountTest();
    isBlockedAccountTest();
    isAmountAvailableTest();
    saveTransactionTest();
}