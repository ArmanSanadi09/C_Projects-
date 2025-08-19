#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Account {
    long int aadhar;
    double amount, debit, credit;
    char name[50], userId[50], phone[15];
};

void Create() {
    struct Account acc;
    FILE *fp = fopen("bank.dat", "ab");
    printf("\n--- New Account ---\n");
    if (!fp) {
        printf("\nError opening file!");
        return;
    }

    char Mobile[15];
    while (1) {
        printf("\nEnter Mobile Number: ");
        scanf("%s", Mobile);
        if (strlen(Mobile) == 10 && (Mobile[0] >= '6' && Mobile[0] <= '9')) {
            strcpy(acc.phone, Mobile);
            break;
        } else {
            printf("\nIncorrect phone number. Please enter a valid number.\n");
        }
    }

    while (1) {
        char adh[20];
        printf("Enter Aadhar Number: ");
        scanf("%s", adh);
        if (strlen(adh) == 12) {
            acc.aadhar = atol(adh);
            break;
        } else {
            printf("\nPlease enter a valid Aadhar number (12 digits).\n");
        }
    }

    printf("\nEnter Full Name: ");
    scanf(" %[^\n]", acc.name);

    printf("\nEnter initial amount: ");
    scanf("%lf", &acc.amount);

    // Generate user ID based on aadhar number (simple logic)
    sprintf(acc.userId, "UID%ld", acc.aadhar % 10000);
    printf("\nYour User ID is: %s\n", acc.userId);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully...\n");
}

void View() {
    struct Account acc;
    FILE *fp = fopen("bank.dat", "rb");
    char searchId[50];
    int found = 0;
    printf("\n--- Account Details ---\n");
    if (!fp) {
        printf("No accounts found!\n");
        return;
    }

    printf("\nEnter User ID to search: ");
    scanf("%s", searchId);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (strcmp(acc.userId, searchId) == 0) {
            printf("User ID: %s\n", acc.userId);
            printf("Name: %s\n", acc.name);
            printf("Phone: %s\n", acc.phone);
            printf("Aadhar: %ld\n", acc.aadhar);
            printf("Balance: %.2f\n", acc.amount);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(fp);
}

void Credit() {
    struct Account acc;
    FILE *fp = fopen("bank.dat", "rb+");
    char UserID[50];
    int found = 0;
    double depositamount = 0;
	printf("\n--- Credit Amount ---\n");
    if (!fp) {
        printf("Account Not found..! ");
        return;
    }
    
    printf("\nEnter UserID : ");
    scanf("%s", UserID);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (strcmp(acc.userId, UserID) == 0) {
            printf("\n\tWelcome %s",acc.name);			
            printf("\n Balance: %lf",acc.amount);
            printf("\n\nAdd amount: ");
            scanf("%lf", &depositamount);
            
            printf("\n\tCredited Amount: %lf",depositamount);
            acc.amount += depositamount;
            acc.credit = depositamount;
            printf("\n\n\tAmount:%lf ",acc.amount);
           
            printf("\nDeposit Successfully...");
            fseek(fp,-sizeof(acc),SEEK_CUR);
            fwrite(&acc,sizeof(acc),1,fp);
            found = 1;
            break;
        }
    }
    if (!found) printf("Account Not found..!");
    fclose(fp);
}

void Debit(){
  struct Account acc;
  FILE *fp=fopen("bank.dat","rb+");
  char userID[50];
  int found=0;
  double  debit,amount;
  printf("\n--- Debit Amount ---\n");
  if(!fp){
    printf("\nAccount Not Found..!\n");
    return;
  }
  printf("Enter UserID : ");
  scanf("%s",userID);
  while(fread(&acc,sizeof(acc),1,fp)){
    if(strcmp(acc.userId,userID)==0){
      printf("\nWelcome %s ",acc.name);
      printf("\nAvailable Amount : %lf",acc.amount);
      printf("\nEnter Amount for Debit : ");
      scanf("%lf",&debit);
      
      if((acc.amount)<=debit){
        printf("\n\tInsuficiant Balance..!");
        
      }
      acc.debit=debit;
      acc.amount-=debit;
      
       fseek(fp, -sizeof(acc), SEEK_CUR);
       fwrite(&acc, sizeof(acc), 1, fp);
      printf("\n\t₹ %lf \tdebited",acc.debit);
      printf("\n\tTotal Amount : %lf",acc.amount);
      found=1;
      break;
    }
    
  }
  if(!found)printf("Account Not found..!");
  fclose(fp);
}

void Last(){
  struct Account acc;
  FILE *fp=fopen("bank.dat","rb");
  char userID[50];
  int found=0;
  printf("\n--- Last Transaction ---\n");
  if(!fp){
    printf("Account Not found..!");
    return ;
  }
  printf("\nEnter UserID : ");
  scanf("%s", userID);
  while(fread(&acc,sizeof(acc),1,fp)){
    if(strcmp(acc.userId,userID)==0){
      printf("\n\nName : %s",acc.name);
      printf("\n\n\tAmount : %lf",acc.amount);
      printf("\n\tCredit : %lf",acc.credit);
      printf("\n\tDebit : %lf",acc.debit);
      found=1;
      break;
    }
  }
  if(!found)printf("\nAccount Not found..!\n");
  fclose(fp);
  
}

void Changes(){
  struct Account acc;
  FILE *fp=fopen("bank.dat","rb+");
  char userID[50],name[50],phone[50];
  int choice,found=0;
  
  
  printf("\n--- Changes ---\n");
  if(!fp){
    printf("\nAccount Not found..!");
    return;
  }
  printf("\nEnter UID for Changes : ");
  scanf("%s",userID);
  while(fread(&acc,sizeof(acc),1,fp)){
    if(strcmp(acc.userId,userID)==0){
      while(1){
        printf("\nwhat You have to Change ?\n");
        printf("\t1. Name \n\t2. Mobile Number \n");
        scanf("%d",&choice);
        switch(choice){
          case 1: printf("\nName : %s",acc.name);
          printf("\n\nNew Name : ");
          scanf(" %[^\n]",name);
          strcpy(acc.name,name);
          printf("\n\n\tName changed Successfully");
          break;
          case 2: printf("\nPhone Number : %s",acc.phone);
          printf("\n\nNew phone Number : ");
          scanf("%s",phone);
          if(strlen(phone)==10 &&(phone[0]>='6' && phone[0]<='9')){
            strcpy(acc.phone,phone);
            printf("\nphone Number changed Successfully..");
          }
          else{
            printf("\n\n\tPlease Enter valid phone Number [Number have must 10 digits] ");
          }
          break;
          
          default: printf("Please Enter Currect..!");
        }
        fseek(fp,-sizeof(acc),SEEK_CUR);
        fwrite(&acc,sizeof(acc),1,fp);
        found=1;
        break;
        
      }
    }
  }
  if(!found)printf("\nAccount Not found..!\n");
  fclose(fp);
}

int main() {
    int select;
    while (1) {
        printf("\n1. New Account \n2. View Account \n3. Credit \n4. Debit \n5. Last Transaction \n6. Changes \n7. Exit \n");
        printf("Select an option: ");
        scanf("%d", &select);
        switch (select) {
            case 1: Create(); break;
            case 2: View(); break;
            case 3: Credit(); break;
            case 4:  Debit();  break;
            case 5:  Last();  break;
            case 6:  Changes(); break;
            case 7: exit(0); break;
            default: printf("Please enter a correct number!\n");
        }
    }
    return 0;
}