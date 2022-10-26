/*
Implement the card module

    1- Fill in card.h file with functions' prototypes and typedefs
    2- Implement getCardHolderName function
    3- Implement getCardExpiryDate function
    4- Implement getCardPAN function
*/

#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <string.h>

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

typedef unsigned char uint8_t;
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

uint8_t arrLenght(const char *arr, uint8_t maxLenght);
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

void getCardHolderNameTest(); 
void getCardExpiryDateTest();
void getCardPANTest();

#endif
