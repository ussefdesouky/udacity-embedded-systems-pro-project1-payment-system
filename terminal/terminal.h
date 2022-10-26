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
#include "../card/card.h"

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
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // optional
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);

void getTransactionDateTest();
void isCardExpriedTest();
void getTransactionAmountTest();
void isBelowMaxAmountTest();
void setMaxAmountTest();
void isValidCardPANTest();

#endif