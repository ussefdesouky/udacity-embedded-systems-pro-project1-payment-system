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

#include <stdlib.h>
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
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

char* trimDate(ST_terminalData_t *termData){
    uint8_t index[5] = {3, 4, 5, 8, 9};
    uint8_t i = 0;

    char* date = calloc(5, sizeof(uint8_t));

    for(uint8_t i = 0; i < sizeof(index); i++){
        date[i] = (*termData).transactionDate[index[i]];
    }
    return date;
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

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
    uint8_t* date = trimDate(termData);
    uint8_t index[4]= {3, 4, 1, 0};

    for(uint8_t i = 0; i < 4; i++){
        if(date[index[i]] <= (*cardData).cardExpirationDate[index[i]]){
            continue;
        }
        else{
            return EXPIRED_CARD;
        }
    }
    return CARD_OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    if ((*termData).transAmount <= 0){
        return INVALID_AMOUNT;
    }
    else{
        return TERMINAL_OK;
    }
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if ((*termData).transAmount > (*termData).maxTransAmount){
        return EXCEED_MAX_AMOUNT;
    }
    else{
        return TERMINAL_OK;
    }
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    if ((*termData).maxTransAmount <= 0){
        return INVALID_MAX_AMOUNT;
    }
    else{
        return TERMINAL_OK;
    }
}

#endif