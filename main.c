#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int unavailable = true;
int userCount = false;
int passwordCount = false;
int userBalanceIter = 1;

void removeFundsSender(char *userSend) {
  char confirmTransaction;
  printf("Are you sure you want to send $100 to %s? ", userSend);
  scanf("%c", &confirmTransaction);

  //printf("\nWE need to iterate to this number in balance.txt: %d", userCount); 
  //printf("\n\nRemoving funds...");
  //exit(1);
}


void checkUser(char *userSend) {
  int sendAmount;
  char approveTrans;
  FILE* validateTransferee;
  validateTransferee = fopen("users.txt", "r");
  char valUsers[21];
  while (fgets(valUsers, 21, validateTransferee)) {
    valUsers[strcspn(valUsers, "\n")] = 0;
    int validateTransfereeUsername = strcmp(valUsers, userSend);
    if (validateTransfereeUsername == 0) {
      printf("\nAmount: ");
      scanf("%d", &sendAmount);
      removeFundsSender(userSend);
    }
  } 
  printf("\nTRANSACTION FAILED. User does not exist. ");
}


void sendLogout() {
  int userOption;
  char userSend[30];  
  printf("\n\n1) Send");
  printf("\n2) Logout\n\n");
  scanf("%d", &userOption);
  if (userOption == 1) {
    printf("\nTransferee: ");
    scanf("%s", userSend);
    checkUser(userSend);
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
  userBalance = fopen("balance.txt", "r");
  while (fgets(retrieveFunds, 10, userBalance)) {
    retrieveFunds[strcspn(retrieveFunds, "\n")] = 0;
    if (userBalanceIter != userCount) {
      userBalanceIter++;
    }
    else if (userBalanceIter == userCount) {
      int fundsInt = atoi(retrieveFunds);
      printf("\n\nBalance: %d ", fundsInt);
      sendLogout();
      break;
    }
  }
}    


void checkLoginDetails(char *usernameInput, char *passwordInput) {
  FILE* checkUser;
  FILE* checkPass;
  checkUser = fopen("users.txt", "r");
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
  usernames = fopen("users.txt", "r");
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
  writeU = fopen("users.txt", "a");
  writeP = fopen("passwords.txt", "a");  
  writeB = fopen("balance.txt", "a");                                    
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



*/

