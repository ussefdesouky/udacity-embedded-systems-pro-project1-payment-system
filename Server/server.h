/*
Implement the server module

    1- Fill in server.h file with functions' prototypes and typedefs
    2- Implement server-side accounts' database
    3- Implement server-side transactions' database
    4- Implement recieveTransactionData function
    5- Implement isValidAccount function
    6- Implement isAmountAvailable function
    7- Implement saveTransaction function
*/
#ifndef SERVER_H
#define SERVER_H

#include "../Terminal/terminal.h"

typedef unsigned long int uint32_t;

typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t ;

typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR, IDLE
}EN_transState_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef struct ST_accountsDB_t
{
    float balance;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

ST_accountsDB_t accountsArr[255] = {
    {1545, "1234845441201"},
    {1545, "4484848751695"},
    {1545, "1454844545"},
    {154, "012345678890123456"},
    {1134, "48544484546"}
};

ST_transaction_t transactionArr[255] = {
    {{"YOUSSEF MOHAMED MOSTAFA", "01234567890123456", "08/22"}, 
        {22.12, 1005.2, "21/08/2021"}, 
        IDLE, 
        0},
    {{"MOHAMED AHMED MOHAMED", "65432109876543210", "05/21"}, 
        {22.12, 1005.2, "21/08/2022"}, 
        IDLE, 
        0},
    {{"ABO MOHAMED", "54654821545612387", "05/21"}, 
        {-22.12, -1005.2, "21/08/2022"}, 
        IDLE, 
        0},
    {},
    {},
};

EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);

EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    //isValidAccount((*transData).cardHolderData)
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData){
     
    for(uint8_t i = 0; i < 255; i++){
        printf("%s %s %d\n", (*cardData).primaryAccountNumber, accountsArr[i].primaryAccountNumber, i);
        for(uint8_t j = 0; j < 20; j++){
            if((*cardData).primaryAccountNumber[j] != accountsArr[i].primaryAccountNumber[j]){
                printf("Not found at index: %d \n", i);
                break;;
            }
            else{
                if(j == 19){
                    return SERVER_OK;
                }     
            }
        }
        if (i == ((sizeof(accountsArr) / sizeof(accountsArr[0]) - 1))){
            printf("dec %ld\n", sizeof(accountsArr));
            return DECLINED_STOLEN_CARD;
        }
    }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    /*for(uint8_t i = 0; i < 255; i++){
        if((*cardData).primaryAccountNumber == accountsArr[i]){
            return SERVER_OK;
        }
        else{
            continue;
        }
        return DECLINED_STOLEN_CARD;
    }*/
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){

}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData){

}

#endif