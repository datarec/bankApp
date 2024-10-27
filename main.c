#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int unavailable = 1;
int userCount = 0;
int passwordCount = 0;
int userBalanceIter = 1;
int removeBalanceIter = 1;

void updateTransfereeFunds(int sendAmount, char *userSend) {
  FILE* readTransferee;
  readTransferee = fopen(userSend, "r");
  char retrieveTransferee[10];
  while (fgets(retrieveTransferee, 10, readTransferee)) {
    FILE* writeTransferee;
    int rtfInt = atoi(retrieveTransferee);
    int adding = rtfInt + sendAmount;
    char addingStr[10];
    sprintf(addingStr, "%d", adding);
    writeTransferee = fopen(userSend, "w");
    fprintf(writeTransferee, addingStr);
    printf("\nsending money...");
    printf("\nTRANSACTION SUCCESSFUL!");
    fclose(writeTransferee);
    fclose(readTransferee);
    exit(1);
  }
}


void removeFundsSender(char *userSend, int sendAmount, char *usernameInput) {
  char confirmTransaction;
  printf("\nAre you sure you want to send $%d to %s (y/n)? ", sendAmount, userSend);
  scanf(" %c", &confirmTransaction);
  if (confirmTransaction == 'y') {
    FILE* checkAdequate;
    checkAdequate = fopen(usernameInput, "r");
    char checkRetrieve[30];
    while (fgets(checkRetrieve, 30, checkAdequate)) {
      int crInt = atoi(checkRetrieve);
      if (crInt < sendAmount) {
        printf("You have insufficient funds.");
        exit(1);
      }
      else { 
        FILE* writeChanges;
        writeChanges = fopen(usernameInput, "w");
        int comparison = crInt - sendAmount;
        char comparisonStr[5];
        sprintf(comparisonStr, "%d", comparison);
        fprintf(writeChanges, comparisonStr);
        fclose(writeChanges);
        fclose(checkAdequate);
        updateTransfereeFunds(sendAmount, userSend);
      }
    }
  } 
  else if (confirmTransaction == 'n') {
    exit(1);
  }
}


void checkUser(char *userSend, char *usernameInput) {
  int sendAmount;
  char approveTrans;
  FILE* validateTransferee;
  validateTransferee = fopen("usernames.txt", "r");
  char valUsers[21];
  while (fgets(valUsers, 21, validateTransferee)) {
    valUsers[strcspn(valUsers, "\n")] = 0;
    int validateTransfereeUsername = strcmp(valUsers, userSend);
    if (validateTransfereeUsername == 0) {
      printf("\nAmount: ");
      scanf("%d", &sendAmount);
      fclose(validateTransferee);
      removeFundsSender(userSend, sendAmount, usernameInput);
    }
  } 
  printf("\nTRANSACTION FAILED. User does not exist. ");
}


void sendLogout(char *usernameInput) {
  int userOption;
  char userSend[30];  
  printf("\n\n1) Send");
  printf("\n2) Logout\n\n");
  scanf("%d", &userOption);
  if (userOption == 1) {
    printf("\nTransferee: ");
    scanf("%s", userSend);
    checkUser(userSend, usernameInput);
  }
  else if (userOption == 2) {
    printf("\nGoodbye. ");
  }
}


void loginPage(char *usernameInput) {
  FILE* userBalance;
  printf("\n\nWelcome %s!", usernameInput);
  int availableFunds = 0;
  char retrieveFunds[10];
  userBalance = fopen(usernameInput, "r");
  while (fgets(retrieveFunds, 10, userBalance)) {
    printf("\n\nBalance: %s", retrieveFunds);
    sendLogout(usernameInput);
  }
  fclose(userBalance);
}    


void checkLoginDetails(char *usernameInput, char *passwordInput) {
  FILE* checkUser;
  FILE* checkPass;
  checkUser = fopen("usernames.txt", "r");
  checkPass = fopen("passwords.txt", "r");
  char users[30];
  char passwords[30];
  while (fgets(users, 30, checkUser)) {
    userCount++;
    users[strcspn(users, "\n")] = 0;
    int compareUsers = strcmp(users, usernameInput);
    if (compareUsers == 0) {
      break;
    }
  }
  while (fgets(passwords, 30, checkPass)) {
    passwordCount++;
    passwords[strcspn(passwords, "\n")] = 0; 
    if (passwordCount == userCount) {
      int comparePassword = strcmp(passwordInput, passwords);
      if (comparePassword == 0) {
        printf("\nAccess granted!"); 
        printf("\nUser iter: %d, Password iter: %d", userCount, passwordCount);
        loginPage(usernameInput);
      }
      else {
        printf("\nIncorrect username or password. ");
      }
    }
  }

  fclose(checkPass);
  fclose(checkUser);
}


void checkAvailability(char *username) {
  FILE* usernames;
  int i;
  usernames = fopen("usernames.txt", "r");
  char iterUsers[10];
  while (fgets(iterUsers, 10, usernames)) {
    iterUsers[strcspn(iterUsers, "\n")] = 0;
    int compare = strcmp(iterUsers, username);
    if (compare == 0) {
      unavailable = false;
      break;
    }
  }
  fclose(usernames);  
}


void accountRegister() {
  FILE* writeU;
  FILE* writeP;
  FILE* writeB;  
  char username[15];
  char password[20];
  printf("https://coolbank.com/register\n\n");
  printf("Maximum username length is: 15 Characters. \n\n");
  printf("Create username: "); 
  scanf("%s", &username);
  printf("Create password: ");
  scanf("%s", &password);
  checkAvailability(username); 
  if (unavailable == 0) {
    printf("\nUsername is unavailable. Please try again, using something else. ");
    exit(1);
  }
  else if (strlen(username) < 3) {
    printf("\nUsername cannot be less than 3 letters long. Please try again.");
    exit(1);
  }
  else if (strlen(username) > 15) {
    printf("\nUsername cannot be greater than 15 letters. Please try again.");
    exit(1);
  }
  else if (strlen(password) < 8) {
    printf("\nPassword cannot be less than 8 digits. Please try again.");
    exit(1);
  }
  else if (strlen(password) > 20) {
    printf("\nPassword cannot be greater than 20 digits. Please try again.");
    exit(1);
  }
  writeU = fopen("usernames.txt", "a");
  writeP = fopen("passwords.txt", "a");  
  writeB = fopen(username, "a");                                    
  fprintf(writeU, "%s\n", username); 
  fprintf(writeP, "%s\n", password);
  fprintf(writeB, "%d\n", 100);
  fclose(writeU);
  fclose(writeP);
  fclose(writeB);
  printf("\nAccount successfully created!");
}


void accountLogin() {
  char usernameInput[20];
  char passwordInput[20]; 
  printf("https://coolbank.com/login\n\n");
  printf("\nAccount login page: \n\n");
  printf("Enter username: ");
  scanf("%s", &usernameInput);
  printf("Enter password: ");
  scanf("%s", &passwordInput);
  checkLoginDetails(usernameInput, passwordInput);
}

void loginRegister() {
  int option;
  printf("https://coolbank.com/home\n\n");
  printf("1) Login\n");
  printf("2) Register\n\n");
  scanf("%d", &option);
  if (option == 1) {
    accountLogin();
  }
  else if (option == 2) {
    accountRegister();
  }
}


int main() {
  loginRegister();
}


// To-do list. 

/*

nothing, all done (:

*/

