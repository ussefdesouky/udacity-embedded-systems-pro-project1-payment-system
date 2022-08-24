/*
Implement the terminal module

    1- Fill in terminal.h file with functions' prototypes and typedefs
    2- Implement getTransactionDate function
    3- Implement isCardExpried function
    4- Implement gatTransactionAmount function
    5- Implement isBelowMaxAmount function
    6- Implement setMaxAmount function
*/
#ifndef TERMINAL_H
#define TERMINAL_H

#include "../Card/card.h"

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

char* trimDate(ST_terminalData_t *termData);
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

char* trimDate(ST_terminalData_t *termData){
    printf("%s \n", (*termData).transactionDate);
    printf("%ld \n", sizeof((*termData).transactionDate));
    uint8_t arr[5] = {3, 4, 5, 8, 9};
    uint8_t index = 0;
    uint8_t* date[5];
    uint8_t i = 0;
    for(int i = 0; i < sizeof(arr); i++){
        //date += (*termData).transactionDate[arr[i]];
        date[i] = (*termData).transactionDate[arr[i]];
        printf("%c \n",  (*termData).transactionDate[arr[i]]);
        printf("%s \n",  date);
    }
    /*for(int i = 0; i < sizeof(arr); i++){
        printf("for trim \n");
        date += (*termData).transactionDate[arr[i]];
        printf("%c \n",  (*termData).transactionDate[arr[i]]);
    }
    
    
    printf("%d \n", date);
    printf("trim \n");
    return date;*/
}

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    uint8_t arrSize = arrLenght((*termData).transactionDate, sizeof((*termData).transactionDate));
    if (arrSize != 10){
        return WRONG_DATE;
    }
    else{
        return TERMINAL_OK;
    }
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){

}
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){

}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){

}

#endif