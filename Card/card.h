/*
Implement the card module

    1- Fill in card.h file with functions' prototypes and typedefs
    2- Implement getCardHolderName function
    3- Implement getCardExpiryDate function
    4- Implement getCardPAN function
*/

#ifndef CARD_H
#define CARD_H

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

uint8_t arrLenght(const char *arr, uint8_t maxLenght){
    uint8_t arrSize = 0;
    for(int i = 0; i < maxLenght; i++){
        if(arr[i] != 0){
            arrSize++;
        }
    }
    printf("%d \n", arrSize);
    printf("%s \n", arr);
    printf("------------------------------- \n");
    return arrSize;
}

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    uint8_t arrSize = arrLenght((*cardData).cardHolderName, sizeof((*cardData).cardHolderName));
    if (arrSize < 20 | arrSize > 24 | arrSize == 0){
        return WRONG_NAME;
    }
    else{
        return CARD_OK;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    uint8_t arrSize = arrLenght((*cardData).cardExpirationDate, sizeof((*cardData).cardExpirationDate));
    if (arrSize != 5){
        return WRONG_EXP_DATE;
    }
    else{
        return CARD_OK;
    }
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    uint8_t arrSize = arrLenght((*cardData).primaryAccountNumber, sizeof((*cardData).primaryAccountNumber));
    if (arrSize < 16 | arrSize > 19 | arrSize == 0){
        return WRONG_PAN;
    }
    else{
        return CARD_OK;
    }
}

ST_cardData_t cardData;

#endif