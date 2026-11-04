#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int arr[100];
int search_byname(AddressBook *,char*,int *);
int search_bynumber(AddressBook *,char*,int *);
int search_bymail(AddressBook *,char*,int *);
void edit_contact(AddressBook *,int *,int );
void dlt_contact(AddressBook *,int *,int);
int validate_name(AddressBook *,char *str);
int validate_phone(AddressBook *addressBook,char *str);
int validate_email(AddressBook *addressBook,char *str);


void listContacts(AddressBook *addressBook, int sortChoice) 
{
    // Sort contacts based on the chosen criteria

    int i,res;
    if(addressBook->contactCount == 0)
    {
        printf("No contact found");
        return ;

    }
    printf("1.list by name:\n");
    printf("2.list by phone:\n");
    printf("3.list by email:\n");
    do
    {
        printf("Enter the sortChoic:");
        scanf("%d",&sortChoice);
        switch(sortChoice)
        {
         
         case 1: // Sorting logic for Name
            {

          for(int i=0;i<addressBook->contactCount;i++)
           {
             for(int j=0;j<addressBook->contactCount-i-1;j++)
               {
                res=strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
            
               if(res>0)
                 {
                  Contact temp = addressBook->contacts[j];
                   addressBook->contacts[j] = addressBook->contacts[j+1];
                   addressBook->contacts[j+1] =temp;
                  }
               }
            }
          break;
       } 
         case 2: // Sorting logic for Phone Number
          {
           for(int i=0;i<addressBook->contactCount;i++)
           {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
              {
              res=strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
            
              if(res>0)
                {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] =temp;
                }
              }
             }
          break;
         }

        case 3: // Sorting logic for E-mail
         {
           for(int i=0;i<addressBook->contactCount;i++)
            {
             for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
             res=strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
            
             if(res>0)
             {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] =temp;
             }
             }
           }
          break;
         }
          default:
           {
            printf("Invalid list");
              }
        }
    }while(sortChoice==4);
    for(i=0;i<addressBook->contactCount;i++)
    {
         printf("| %d  | %s\t| %s\t| %s\t|\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    }


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char str[100];
    int res=0,var=addressBook->contactCount;
    // get a valid name from the user
    while(res!=1)
    {
        printf("Enter the name: ");
        scanf(" %[^\n]",str);
        res=validate_name(addressBook,str);
        if(res)
            strcpy(addressBook->contacts[var].name,str);
        else
            printf("Invalid name.\n");
    }
    res=0;
    // get a valid phone number
    while(res!=1)
    {
        printf("Enter the number: ");
        scanf("%s",str);
        res=validate_phone(addressBook,str);
        if(res==1)
            strcpy(addressBook->contacts[var].phone,str);
        else if(res==0)
            printf("Invalid number.\n");
    }
    res=0;
    // get a valid email address
    while(res!=1)
    {
        printf("Enter the E-mail: ");
        scanf("%s",str);
        res=validate_email(addressBook,str);
        
        if(res==1)
            strcpy(addressBook->contacts[var].email,str);
        else if (res==0)
            printf("Invalid E-mail\n");
    }
    printf("Contact is saved successfully..");
    addressBook->contactCount+=1;//increment total contact count66
 
    
    
}

    

int searchContact(AddressBook *addressBook,int *arr) 
{
    
int choice,res=0;
    char str[100];
    // Display the search menu options to the user
    printf("1.Name\n2.Phone NUmber\n3.E-mail\n4.Exit\nEnter the choice: ");
    scanf("%d",&choice);


    if(choice==1)
        printf("Enter the name: ");
    else if(choice == 2)
        printf("Enter the phone number: ");
    else if(choice==3)
        printf("Enter the E-mail: ");
    
    
    scanf(" %[^\n]",str);
    switch (choice)
    {
    case 1:
        
    
        printf("| No.| Name\t\t| Phone number  |\tE-mail\t\t|\n");
        res= search_byname(addressBook,str,arr);

        if(res==0)
        {
            printf("Contact is not found\n");
        }
        break;
    case 2:
        
        printf("| No.| Name\t\t| Phone number  |\tE-mail\t\t|\n");
        res=search_bynumber(addressBook,str,arr);

        if(res==0)
        {
            printf("Contact is not found\n");
        }
        break;
    case 3:
        
        printf("| No.| Name\t\t| Phone number  |\tE-mail\t\t|\n");
        res =search_bymail(addressBook,str,arr);
        
        if(res==0)
        { 
            printf("Contact is not found\n");
        }
        break;
    case 4:
        printf("Exiting...");
        break;
    default:
    printf("Enter a valid choice");
        break;
    }
    return res;
   
}

void editContact(AddressBook *addressBook)
{
    int arr[100]; 
    int res;

    res = searchContact(addressBook, arr);
    if(res>0)
    {

    edit_contact(addressBook, arr,res);
    }
}

void deleteContact(AddressBook *addressBook)
{
    {
    int arr[100];
    int res;

    // Use the same searchContact function to find the contact to delete
    res = searchContact(addressBook, arr);

    if (res > 0)
    {
        //  delete if matches were found
        dlt_contact(addressBook, arr, res);
    }
}
}

int search_byname(AddressBook *addressBook,char*str,int *ptr)
{
    char *add;
    int flag=0;
    
    for (int  i = 0; i < addressBook->contactCount; i++)
        {
            
            add=strstr(addressBook->contacts[i].name,str); 
            if(add!=NULL)
            {
                printf("| %d  | %s\t| %s\t| %s\t|\n",flag+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                ptr[flag]=i;
                flag++;
            }
        }
        return flag;
}


int search_bynumber(AddressBook *addressBook,char*str,int *ptr)
{
    int add;
    int flag=0;
    
    for (int  i = 0; i < addressBook->contactCount; i++)
        {
            add=strcmp(addressBook->contacts[i].phone,str);
            
            if(add==0)
            {
                printf("| %d  | %s\t| %s\t| %s\t|\n",flag+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                
                
                ptr[flag]=i;
                flag++;
            }
        }
        return flag;
}


int search_bymail(AddressBook *addressBook, char*str, int *ptr)
{
    int add;
    int flag=0;
    
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        add = strcmp(addressBook->contacts[i].email, str);
        
        if(add==0)
        {
            printf("| %d  | %s\t| %s\t| %s\t|\n", flag+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            
            
            ptr[flag]=i;
            flag++;
        }
    }
    return flag;
}





void edit_contact(AddressBook *addressBook,int *ptr,int res)
{
	int choice,num,num1,arr[10];
    char str[100];
    
    printf("Enter the contact to edit: ");
    scanf("%d",&choice);
    
    if(choice>=1 && choice <= res) //check if the selection is valid
    {
        num=ptr[choice-1];
        
        printf("1.Name\n2.Number\n3.E-mail\nEnter the choice: ");
        scanf("%d",&choice);
        
        if(choice==1) // Logic for editing the Name 
        {
            printf("Enter the new name: ");
            scanf(" %[^\n]",str);
            strcpy(addressBook->contacts[num].name,str);
            printf("Contact is edited.");
        }
        else if (choice==2) // Logic for editing the Phone Number
        {
            printf("Enter the new number: ");
            scanf("%s",str);
            
            if(search_bynumber(addressBook,str,arr)==0)
            {
                    strcpy(addressBook->contacts[num].phone,str);
                    printf("Contact is edited.");
            }
            else    
                printf("The number is already present\n");
        }
        else if (choice==3) // Logic for editing the Email
        {
            printf("Enter the new mail: ");
            scanf("%s",str);
            // Search if the new email already exists to prevent duplicates
            if(search_bymail(addressBook,str,arr)==0)
            {
                // Validate the format of the new email address
                if(validate_email(addressBook,str)==1)
                {
                    strcpy(addressBook->contacts[num].email,str);// Update if valid and unique
                    printf("Contact is edited.");
                }
                else    printf("The mail is not valid\n");
            }
            else
                printf("The Mail is already present\n");
        }
        else
            printf("Error Invalid choice\n");
    }
    else
        printf("Enter the correct contact\n");
    
}

void dlt_contact(AddressBook *addressBook,int *ptr,int res)
{
	 int choice;
    char ch;
    printf("enter the contact to be deleted :");
    scanf("%d",&choice);

    if(choice>= 1 && choice<= res)
    {
    // Maps the user's list selection to the actual contact index
    int num=ptr[choice-1];

    printf("Do you want to delete y/n?: ");
    scanf(" %c",&ch);
    
    if(ch=='y'|| ch == 'Y')
    {
        //shift all contacts after the deleted one to the left
        for (int i = num; i < addressBook->contactCount - 1; i++)
            {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }
            addressBook->contactCount --;//reduce count
            printf("Contact successfully deleted.\n");
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

int validate_name(AddressBook *addressBook,char *str)
{
    int length=strlen(str);

    for(int i=0;i<length;i++)
    {
        // Check if character is Uppercase (A-Z), Lowercase (a-z), a Space, or a Dot (.)
        if(str[i]>='A' && str[i]<='Z'||str[i]>='a' && str[i]<='z' || str[i]==' ' || str[i]=='.')
            continue;
        else
            return 0;
    }
    return 1;
    
}


int validate_phone(AddressBook *addressBook ,char*str)
{
    int length=strlen(str),count=0,arr[10];
    
    // phone number is at least 10 digits long
    if(length<10)
        return 0;
        
    for(int i=0;i<length;i++)
    {
        // Check if character is between ASCII '0' and '9'
        if(str[i]>='0' && str[i]<='9')
            continue;
        else    
            return 0;
    }
    // Loop through existing contacts to prevent duplicate phone numbers
    for(int i = 0; i< addressBook->contactCount;i++)
    {
        //comparing
        if(strcmp(addressBook->contacts[i].phone,str)==0)
        {   

            return 0;
        }
    }
    return 1;
}


int validate_email(AddressBook *addressBook,char *str)
{
    int count=0,i;
    int flag;
    char *add,*res;
    
    // Check if the email starts with a lowercase letter
    if(str[0]<'a' || str[0]>'z')
        return 0;
        
    add=strchr(str,'@');
    res=strstr(str,".com");
    
    //Ensure '@' exists, ".com" exists, and nothing comes after ".com"
    if( add==NULL || res==NULL||res[4]!='\0')
        return 0;
        
    for(i=0;str[i]!='@';i++)
    {
         // Allow only lowercase letters and numbers in the username
        if(str[i]>='a' && str[i]<='z' || str[i]>='0' && str[i]<='9')
            continue;
        else
            return 0;
    }
    
    // Loop through the domain part (between '@' and '.com')
    for(i=1;add[i]!=res[0];i++)
    {
        //check the domain name contains only lowercase letters
        if(add[i]<'a' || add[i]>'z')
            return 0;  
    }
    // Check if the email already exists in the address book
     for(int i = 0; i< addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,str)==0)
        {   
            
            return 0;
        }
    }
    // Ensure the domain part (eg. "gmail") is at least 3 characters long
    if(i<3)
        return 0;
        
    return 1;
}
