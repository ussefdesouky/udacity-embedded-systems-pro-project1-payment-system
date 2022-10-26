#include "card.h"

uint8_t arrLenght(const char *arr, uint8_t maxLenght){
    uint8_t arrLen = 0;
    for(int i = 0; i < maxLenght; i++){
        if(arr[i] != 0){
            arrLen++;
            // printf("%c\n", arr[i]);    
        }
    }
    // printf("%d \n", maxLenght);
    printf("%d \n", arrLen);
    printf("%s \n", arr);
    printf("------------------------------- \n");
    return arrLen;
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

void getCardHolderNameTest(){
    printf("Tester Name: Youssef Hassan\n");
    printf("Function Name: getCardHolderName\n");
    const uint8_t numberOfTestCases = 3;

    uint8_t cardHolderNameTestCase[3][28] = {"YOUSSEF MOHAMED MOSTAFA","YOUSSEF MOHAMED MOSTAFA KA", "YOUSSEF MOHAMED"};
    uint8_t expextedResult[3][11] = {"CARD_OK", "WRONG_NAME", "CARD_OK"};

    ST_cardData_t cardTest;

    for (uint8_t i = 0; i < numberOfTestCases; i++){
		printf("\nTest Case %d: \n", i + 1);
        strcpy(cardTest.cardHolderName, cardHolderNameTestCase[i]);
        printf("Input Data: %s\n", cardTest.cardHolderName);
		printf("Expected Result: %s\n", expextedResult[i]);
		if(getCardHolderName(&cardTest) == CARD_OK){
            printf("Actual Result: CARD_OK\n");
        }
        else{
            printf("Actual Result: WRONG_NAME\n");
        }
	}

}

void getCardExpiryDateTest(){
    printf("Tester Name: Youssef Hassan\n");
    printf("Function Name: getCardExpiryDate\n");
    const uint8_t numberOfTestCases = 3;

    uint8_t cardExpiryDateTestCase[3][11] = {"05/25","05/25/2022", "0525"};
    uint8_t expextedResult[3][15] = {"CARD_OK", "WRONG_EXP_DATE", "WRONG_EXP_DATE"};

    ST_cardData_t cardTest;

    for (uint8_t i = 0; i < numberOfTestCases; i++){
		printf("\nTest Case %d: \n", i + 1);
        strcpy(cardTest.cardExpirationDate, cardExpiryDateTestCase[i]);
        printf("Input Data: %s\n", cardTest.cardExpirationDate);
		printf("Expected Result: %s\n", expextedResult[i]);
		if(getCardExpiryDate(&cardTest) == CARD_OK){
            printf("Actual Result: CARD_OK\n");
        }
        else{
            printf("Actual Result: WRONG_EXP_DATE\n");
        }
	}
}

void getCardPANTest(){
    printf("Tester Name: Youssef Hassan\n");
    printf("Function Name: getCardPAN\n");
    const uint8_t numberOfTestCases = 3;

    uint8_t cardPANTestCase[3][21] = {"01234567890123456", "9876543210987654", "98760123456789012345"};
    uint8_t expectedResult[3][10] = {"CARD_OK", "CARD_OK", "WRONG_PAN"};

    ST_cardData_t cardTest;

    for (uint8_t i = 0; i < numberOfTestCases; i++){
		printf("\nTest Case %d: \n", i + 1);
        strcpy(cardTest.primaryAccountNumber, cardPANTestCase[i]);
        printf("Input Data: %s\n", cardTest.primaryAccountNumber);
		printf("Expected Result: %s\n", expectedResult[i]);
		if(getCardPAN(&cardTest) == CARD_OK){
            printf("Actual Result: CARD_OK\n");
        }
        else{
            printf("Actual Result: WRONG_PAN\n");
        }
	}
}