#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {

    FILE *fp;
    if((fp=fopen("contact.csv","w"))==NULL)
    {
        fprintf(stderr,"File not found\n");
        return ;
    }
        fprintf(fp,"%d\n",addressBook->contactCount);

    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
  
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp;
    if((fp=fopen("contact.csv","r"))==NULL)
    {
        fprintf(stderr,"File not found\n");
        return ;
    }
    
    fscanf(fp,"%d\n",&addressBook->contactCount);

    while((fscanf(fp,"%[^,],%[^,],%[^\n] ",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email))==3)
        addressBook->contactCount++;
    fclose(fp);
    
}
