#include "server.h"

uint32_t sequenceNumber = 0;

ST_accountsDB_t accountsArr[255] = {
    {1545,  RUNNING,    "01234567890123456"},
    {100000,  RUNNING,  "5807007076043875"},
    {6000,  RUNNING,    "14548445451165456"},
    {100,   RUNNING,    "84654821545612388"},
    {200,   BLOCKED,    "65432109876543210"}
};

//ST_transaction_t transactionArr[255] = {0};

ST_transaction_t transactionArr[255] = {
    {
        {"YOUSSEF MOHAMED MOSTAFA", "01234567890123456", "08/22"}, 
        {22.12, 1005.2, "01/03/2021"}, 
        IDLE, 
        1
    },
    {
        {"MOHAMED AHMED MOHAMED", "65432109876543210", "05/21"}, 
        {100, 1005.2, "21/08/2022"}, 
        IDLE, 
        2
    },
    {   
        {"ABO MOHAMED", "54654821545612387", "04/20"}, 
        {30, -1005.2, "21/08/2022"}, 
        IDLE, 
        3
    },
    {
        {"ABO MOHAMED", "84654821545612388", "05/26"}, 
        {200.12, -1005.2, "21/08/2022"}, 
        IDLE, 
        4
    },
    {
        {"MOHAMED ATEF", "7465482154561237", "10/22"}, 
        {1000, 2000.27, "21/01/2022"}, 
        IDLE, 
        5
    },
};


EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    ST_accountsDB_t accountReference;

    //printf("Sequence Number: %ld\n", sequenceNumber);

    if(isValidAccount(&(*transData).cardHolderData , &accountReference) == SERVER_OK){
        if(isAmountAvailable(&(*transData).terminalData, &accountReference) != LOW_BALANCE){
            if(isBlockedAccount(&accountReference) != BLOACKED_ACCOUNT){
                transData->transState = APPROVED;
                if(saveTransaction(transData) != INTERNAL_SERVER_ERROR){
                    //listSavedTransactions();
                    return APPROVED;
                }
                else{
                    transData->transState = INTERNAL_SERVER_ERROR;
                    return INTERNAL_SERVER_ERROR;
                }
            } 
            else{
                transData->transState = DECLINED_STOLEN_CARD;
                return DECLINED_STOLEN_CARD;
            }
        }
        else{
            transData->transState = DECLINED_INSUFFECIENT_FUND;
            return DECLINED_INSUFFECIENT_FUND;
        }
    }
    else{
        transData->transState = FRAUD_CARD;
        return FRAUD_CARD;
    }
  
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
    for(uint8_t i = 0; i < 255; i++){
        //printf("%s %s %d\n", (*cardData).primaryAccountNumber, accountsArr[i].primaryAccountNumber, i);
        for(uint8_t j = 0; j < 20; j++){
            if((*cardData).primaryAccountNumber[j] != accountsArr[i].primaryAccountNumber[j]){
                //printf("Not found at index: %d \n", i);
                break;;
            }
            else{
                if(j == 19){
                    *accountRefrence = accountsArr[i];
                    //printf("account state %d\n", accountRefrence->state);
                    return SERVER_OK;
                }     
            }
        }
        /*if (i == ((sizeof(accountsArr) / sizeof(accountsArr[0]) - 1))){
            printf("dec %ld\n", ((sizeof(accountsArr) / sizeof(accountsArr[0]) - 1)));
            return DECLINED_STOLEN_CARD;
        }*/
    }
    accountRefrence = NULL;
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
    if(accountRefrence->state == BLOCKED){
        return BLOACKED_ACCOUNT;
    }
    return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){
    if((*termData).transAmount <= (*accountRefrence).balance){
        printf("Balance before trans: %f\n", (*accountRefrence).balance);
        // update card balance
        (*accountRefrence).balance -= (*termData).transAmount;
        printf("Balance after trans: %f\n", (*accountRefrence).balance);
        return SERVER_OK;
    }
    return LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
    getTransaction();
    transactionArr[sequenceNumber].cardHolderData = transData->cardHolderData;
    transactionArr[sequenceNumber].terminalData = transData->terminalData;
    transactionArr[sequenceNumber].transactionSequenceNumber = sequenceNumber + 1;
    transactionArr[sequenceNumber].transState = transData->transState;

    return SERVER_OK;
}

void getTransaction(){
    for(uint8_t i = 0; i < 255; i++){
        if(transactionArr[i].transactionSequenceNumber != 0){
            sequenceNumber = transactionArr[i].transactionSequenceNumber;
        }
    }
}

void listSavedTransactions(){
    for (uint8_t i = 0; i < sequenceNumber; i++)
	{
		//ST_transaction_t* ptr = &transactionData[i];
		printf("------------- Trasnsaction %d ----------------\n", i + 1);
		printf("Transaction Sequence Number : %ld\n", transactionArr[i].transactionSequenceNumber); 
		printf("Transaction Date : %s\n", transactionArr[i].terminalData.transactionDate); 
		printf("Transaction Amount : %f\n", transactionArr[i].terminalData.transAmount);
		printf("Transaction State : %d\n" , transactionArr[i].transState); 
		printf("Terminal Max Amount : %f\n", transactionArr[i].terminalData.maxTransAmount); 
		printf("Cardholder Name : %s\n", transactionArr[i].cardHolderData.cardHolderName); 
		printf("PAN: %s\n", transactionArr[i].cardHolderData.primaryAccountNumber); 
		printf("Card Expiration Date : %s\n", transactionArr[i].cardHolderData.cardExpirationDate); 
		printf("---------------------------------------------\n");
	}
}

void recieveTransactionDataTest(){
    printf("\nTester Name: Youssef Hassan\n");
    printf("Function Name: receiveTransactionData\n");

    // transaction DB as our test cases
    uint8_t numberOfTestCases = 5;

    uint8_t expectedResult[5][27] = {"APPROVED", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "DECLINED_INSUFFECIENT_FUND", "FRAUD_CARD"};

    for (uint8_t i = 0; i < 5; i++){
		printf("\nTest Case %d: \n", i + 1);
        printf("Input Data: transactionArr[%d]\n", i); 
		printf("Expected Result: %s\n", expectedResult[i]);
		if(recieveTransactionData(&transactionArr[i]) == APPROVED){
            printf("Actual Result: APPROVED\n");
        }
        else if (recieveTransactionData(&transactionArr[i]) == DECLINED_STOLEN_CARD){
            printf("Actual Result: DECLINED_STOLEN_CARD\n");
        }
        else if (recieveTransactionData(&transactionArr[i]) == INTERNAL_SERVER_ERROR){
            printf("Actual Result: INTERNAL_SERVER_ERROR\n");
        }
        else if (recieveTransactionData(&transactionArr[i]) == DECLINED_INSUFFECIENT_FUND){
            printf("Actual Result: DECLINED_INSUFFECIENT_FUND\n");
        }
        else if (recieveTransactionData(&transactionArr[i]) == FRAUD_CARD){
            printf("Actual Result: FRAUD_CARD\n");
        }
        else{
            printf("Actual Result: IDLE\n");
        }
	}
}

void isValidAccountTest(){
    printf("\nTester Name: Youssef Hassan\n");
    printf("Function Name: isValidAccount\n");

    ST_accountsDB_t accountReference;
    // transaction DB as our test cases
    uint8_t numberOfTestCases = 5;

    uint8_t expectedResult[5][27] = {"SERVER_OK", "SERVER_OK", "FRAUD_CARD", "SERVER_OK", "FRAUD_CARD"};

    for (uint8_t i = 0; i < 5; i++){
		printf("\nTest Case %d: \n", i + 1);
        printf("Input Data: transactionArr[%d]\n", i); 
		printf("Expected Result: %s\n", expectedResult[i]);
		if(isValidAccount(&transactionArr[i].cardHolderData, &accountReference) == SERVER_OK){
            printf("Actual Result: SERVER_OK\n");
        }
        else{
            printf("Actual Result: FRAUD_CARD\n");
        }
	}
}

void isBlockedAccountTest(){
    printf("\nTester Name: Youssef Hassan\n");
    printf("Function Name: isBlockedAccount\n");

    ST_accountsDB_t accountReference;
    // transaction DB as our test cases
    uint8_t numberOfTestCases = 5;

    uint8_t expectedResult[5][27] = {"SERVER_OK", "SERVER_OK", "SERVER_OK", "SERVER_OK", "BLOCKED_ACCOUNT"};

    for (uint8_t i = 0; i < 5; i++){
        accountReference = accountsArr[i];
		printf("\nTest Case %d: \n", i + 1);
        printf("Input Data: transactionArr[%d]\n", i); 
		printf("Expected Result: %s\n", expectedResult[i]);
		if(isBlockedAccount(&accountReference) == SERVER_OK){
            printf("Actual Result: SERVER_OK\n");
        }
        else{
            printf("Actual Result: BLOCKED_ACCOUNT\n");
        }
	} 
}

void isAmountAvailableTest(){
    printf("\nTester Name: Youssef Hassan\n");
    printf("Function Name: isAmountAvailable\n");

    ST_accountsDB_t accountReference;
    // transaction DB as our test cases
    uint8_t numberOfTestCases = 5;

    uint8_t expectedResult[5][27] = {"SERVER_OK", "SERVER_OK", "SERVER_OK", "SERVER_OK", "LOW_BALANCE"};

    for (uint8_t i = 0; i < 5; i++){
        accountReference = accountsArr[i];
		printf("\nTest Case %d: \n", i + 1);
        printf("Input Data: transactionArr[%d]\n", i); 
		printf("Expected Result: %s\n", expectedResult[i]);
		if(isAmountAvailable(&transactionArr[i].terminalData, &accountReference) == SERVER_OK){
            printf("Actual Result: SERVER_OK\n");
        }
        else{
            printf("Actual Result: LOW_BALANCE\n");
        }
	}
}

void saveTransactionTest(){
    printf("\nTester Name: Youssef Hassan\n");
    printf("Function Name: saveTransaction\n");

    // transaction DB as our test cases
    uint8_t numberOfTestCases = 5;

    uint8_t expectedResult[5][27] = {"SERVER_OK", "SERVER_OK", "SERVER_OK", "SERVER_OK", "SERVER_OK"};

    for (uint8_t i = 0; i < 5; i++){
		printf("\nTest Case %d: \n", i + 1);
        printf("Input Data: transactionArr[%d]\n", i); 
		printf("Expected Result: %s\n", expectedResult[i]);
		if(saveTransaction(&transactionArr[i]) == SERVER_OK){
            printf("Actual Result: SERVER_OK\n");
        }
        else{
            printf("Actual Result: SERVER_OK\n");
        }
	}
}

void listSavedTransactionsTest(){
    printf("Tester Name: Youssef Hassan\n");
    printf("Function Name: listSavedTransaction\n");
    printf("Input Data: transactionArr[255]\n"); 
	printf("Expected Result must be same as Actual Result as it is a printing function\n");

    listSavedTransactions();
}