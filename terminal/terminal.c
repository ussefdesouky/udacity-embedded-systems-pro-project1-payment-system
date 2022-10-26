#include <stdio.h>
#include "terminal.h"

char* trimDate(ST_terminalData_t *termData){
    uint8_t index[5] = {3, 4, 5, 8, 9}; // 05/10/2022
    uint8_t i = 0;

    char* date = calloc(5, sizeof(uint8_t));

    for(uint8_t i = 0; i < sizeof(index); i++){
        date[i] = (*termData).transactionDate[index[i]];
    }
    //printf("DAAAAATE: %s\n", date);
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
    uint8_t index[4]= {3, 4, 0, 1};

    for(uint8_t i = 0; i < 4; i++){
        //printf("DATE: %d \t CARD: %d\n", date[index[i]], (*cardData).cardExpirationDate[index[i]]);
        if(date[index[i]] < (*cardData).cardExpirationDate[index[i]]){
            return CARD_OK;
        }
        else if(date[index[i]] == (*cardData).cardExpirationDate[index[i]]){
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

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData,  float maxAmount){
    (*termData).maxTransAmount = maxAmount;
    if ((*termData).maxTransAmount <= 0){
        return INVALID_MAX_AMOUNT;
    }
    else{
        return TERMINAL_OK;
    }
}

void getTransactionDateTest(){
    printf("Tester Name: Youssef Hassan\n");
    printf("Function Name: getTransactionDate\n");
    const uint8_t numberOfTestCases = 4;

    uint8_t transactionDateTestCase[4][28] = {"25/06/2022","10/10/2010", "10", ""};
    uint8_t expextedResult[4][11] = {"TERMINAL_OK", "TERMINAL_OK", "WRONG_DATE", "WRONG_DATE"};

    ST_terminalData_t termTest;

    for (uint8_t i = 0; i < numberOfTestCases; i++){
		printf("\nTest Case %d: \n", i + 1);
        strcpy(termTest.transactionDate, transactionDateTestCase[i]);
        printf("Input Data: %s\n", termTest.transactionDate);
		printf("Expected Result: %s\n", expextedResult[i]);
		if(getTransactionDate(&termTest) == TERMINAL_OK){
            printf("Actual Result: TERMINAL_OK\n");
        }
        else{
            printf("Actual Result: WRONG_DATE\n");
        }
	}

}

void isCardExpriedTest(){
    printf("Tester Name: Youssef Hassan\n");
    printf("Function Name: isCardExpired\n");
    const uint8_t numberOfTestCases = 4;

    uint8_t transactionDateTestCase[4][28] = {"25/06/2022","10/10/2010", "01/04/2048", "01/04/2026"};
    uint8_t expectedResult[4][12] = {"TERMINAL_OK", "TERMINAL_OK", "EXPIRED_CARD", "EXPIRED_CARD"};

    ST_cardData_t cardTest = {.cardExpirationDate = "05/24"};
    ST_terminalData_t termTest;

    for (uint8_t i = 0; i < numberOfTestCases; i++){
		printf("\nTest Case %d: \n", i + 1);
        strcpy(termTest.transactionDate, transactionDateTestCase[i]);
        printf("Input Data: %s\n", termTest.transactionDate);
		printf("Expected Result: %s\n", expectedResult[i]);
		if(isCardExpired(&cardTest, &termTest) == TERMINAL_OK){
            printf("Actual Result: TERMINAL_OK\n");
        }
        else{
            printf("Actual Result: EXPIRED_CARD\n");
        }
	}
}

void getTransactionAmountTest(){
    printf("Tester Name: Youssef Hassan\n");
    printf("Function Name: getTransactionAmount\n");
    const uint8_t numberOfTestCases = 4;

    float transactionAmountTestCase[4] = {2566.16, 21, 0, -200};
    uint8_t expectedResult[4][14] = {"TERMINAL_OK", "TERMINAL_OK", "INVALID_AMOUNT", "INVALID_AMOUNT"};

    ST_terminalData_t termTest;

    for (uint8_t i = 0; i < numberOfTestCases; i++){
		printf("\nTest Case %d: \n", i + 1);
        termTest.transAmount = transactionAmountTestCase[i];
        printf("Input Data: %f\n", termTest.transAmount);
		printf("Expected Result: %s\n", expectedResult[i]);
		if(getTransactionAmount(&termTest) == TERMINAL_OK){
            printf("Actual Result: TERMINAL_OK\n");
        }
        else{
            printf("Actual Result: INVALID_AMOUNT\n");
        }
	}
}

void isBelowMaxAmountTest(){
    printf("Tester Name: Youssef Hassan\n");
    printf("Function Name: isBelowMaxAmount\n");
    const uint8_t numberOfTestCases = 4;

    float transactionAmountTestCase[4] = {2000, 5000, 0, -200};
    float maxAmountTestCase[4] = {2566.16, 4000, 1000, 0};
    uint8_t expectedResult[4][17] = {"TERMINAL_OK", "EXCEED_MAX_AMOUNT", "TERMINAL_OK", "TERMINAL_OK"};

    ST_terminalData_t termTest;

    for (uint8_t i = 0; i < numberOfTestCases; i++){
		printf("\nTest Case %d: \n", i + 1);
        termTest.transAmount  = transactionAmountTestCase[i];
        termTest.maxTransAmount = maxAmountTestCase[i];
        printf("Input Data:\n \t transAmount: %f\n \t maxAmount: %f\n", termTest.transAmount, termTest.maxTransAmount); 
		printf("Expected Result: %s\n", expectedResult[i]);
		if(isBelowMaxAmount(&termTest) == TERMINAL_OK){
            printf("Actual Result: TERMINAL_OK\n");
        }
        else{
            printf("Actual Result: EXCEED_MAX_AMOUNT\n");
        }
	}
}

void setMaxAmountTest(){
    printf("Tester Name: Youssef Hassan\n");
    printf("Function Name: setMaxAmountTest\n");
    const uint8_t numberOfTestCases = 4;

    float maxAmountTestCase[4] = {2566.16, -1000, 4000, 0};
    uint8_t expectedResult[4][18] = {"TERMINAL_OK", "INVALID_MAX_AMOUNT", "TERMINAL_OK", "INVALID_MAX_AMOUNT"};

    ST_terminalData_t termTest;

    for (uint8_t i = 0; i < numberOfTestCases; i++){
		printf("\nTest Case %d: \n", i + 1);
        printf("Input Data:\n \t maxAmount: %f\n", maxAmountTestCase[i]); 
		printf("Expected Result: %s\n", expectedResult[i]);
		if(setMaxAmount(&termTest, maxAmountTestCase[i]) == TERMINAL_OK){
            printf("Actual Result: TERMINAL_OK\n");
        }
        else{
            printf("Actual Result: INVALID_MAX_AMOUNT\n");
        }
	}
}

void isValidCardPANTest(){
 
}
