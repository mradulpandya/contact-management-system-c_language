#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>

struct contact
{
    long ph;
    char name[20],add[20],email[30],note[50];
}list;

char query[20],name[20],email[30],note[50],add[20],ph;

FILE *fp,*ft;

int i,n,ch,l,found;

int main()
{
main:
    system("cls");    /* ************Main menu ***********************  */
    printf("\n\t **** Welcome to Contact Management System **** ");
    printf("\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t Press [1] For Add a new Contact\n\t\t Press [2] For List all Contacts\n\t\t Press [3] For Search for contact\n\t\t Press [4] For Edit a Contact\n\t\t Press [5] For Delete a Contact\n\t\t Press [0] For Exit\n\t\t=================\n\t\t");
    printf("Enter the choice:");
    scanf("%d",&ch);

    switch(ch)
    {
    case 0:
        printf("\n\n\t\tAre you sure you want to exit?");
        break;

        /* *********************Add new contacts************  */
    case 1:
        system("cls");
        fp=fopen("contact.txt","a");
        for (;;)
        {
            fflush(stdin);
            printf("\nName : ");
            scanf("%[^\n]",&list.name);

            if(stricmp(list.name,"")==0 || stricmp(list.name," ")==0)
                break;

            fflush(stdin);
            printf("Phone : ");
            scanf("%ld",&list.ph);

            fflush(stdin);
            printf("Address : ");
            scanf("%[^\n]",&list.add);
            fflush(stdin);

            printf("Email address : ");
            gets(list.email);

            printf("Notes : ");
            gets(list.note);
            printf("\n");

            fwrite(&list,sizeof(list),1,fp);
        }
        fclose(fp);
        break;
        /* *********************list of contacts*************************  */

    case 2:
        system("cls");
        printf("\n\t\t================================\n\t\t\tLIST OF CONTACTS\n\t\t================================\n\nName\t\tPhone No\tAddress\t\tE-mail ad.\n=================================================================\n\n");
        for(i=97;i<=122;i=i+1)
        {
            fp=fopen("contact.txt","r");
            fflush(stdin);
            found=0;
            while(fread(&list,sizeof(list),1,fp)==1)
            {
                if(list.name[0]==i || list.name[0]==i-32)
                {
                    printf("\nName\t: %s\nPhone\t: %ld\nAddress\t: %s\nEmail\t: %s\nNote\t: %s\n",list.name,list.ph,list.add,list.email,list.note);
                    found++;
                }
            }
           /* if(found!=0)
            {
                printf("===========================================================\n\n",i-32,found);
                getch();
            }*/
            fclose(fp);
        }
        break;
        /* *******************search contacts**********************  */
    case 3:
        system("cls");
        do
        {
            found=0;
            printf("\n\n\t CONTACT SEARCH\n\t===========================\n\tEmail of contact to search: ");
            fflush(stdin);
            scanf("%s",&query);
            l=strlen(query);
            fp=fopen("contact.txt","r");
            system("cls");
            printf("\n\n Search result for '%s' \n===================================================\n",query);
            while(fread(&list,sizeof(list),1,fp)==1)
            {
                for(i=0; i<=l; i++)
                    email[i]=list.email[i];
                    email[l]='\0';

                if(stricmp(email,query)==0)
                {
                    printf("\n Name\t: %s\n Phone\t:%ld\n Address: %s\n Email\t: %s\n Note\t: %s\n",list.name,list.ph,list.add,list.email,list.note);
                    found++;

                    if (found%4==0)
                    {
                        printf("Press any key to continue...");
                        getch();
                    }
                }
            }

            if(found==0)
            {
                printf("\n No match found!");
            }
            else
            {
                printf("\n %d match(s) found!",found);
            }
            fclose(fp);
            printf("\n Try again?\n\n\t[1] Yes\t\t[0] No\n\t");
            scanf("%d",&ch);
        }
        while(ch==1);
        break;

        /* *********************edit contacts************************/

    case 4:
        system("cls");
        fp=fopen("contact.txt","r");
        ft=fopen("temp.dat","w");
        fflush(stdin);

        printf("Edit contact\n===============================\n\n\t Enter the name of contact to edit:");
        scanf("%[^\n]",name);

        while(fread(&list,sizeof(list),1,fp)==1)
        {
            if(stricmp(name,list.name)!=0)
                fwrite(&list,sizeof(list),1,ft);
        }
        fflush(stdin);
        printf("\n\n Editing '%s'\n\n",name);
        printf(" Name :");
        scanf("%[^\n]",&list.name);
        fflush(stdin);

        printf(" Phone :");
        scanf("%ld",&list.ph);
        fflush(stdin);

        printf(" Address :");
        scanf("%[^\n]",&list.add);
        fflush(stdin);
        printf(" Email address :");
        gets(list.email);
        fflush(stdin);


        printf(" Note :");
        gets(list.note);
        printf("\n");
        fwrite(&list,sizeof(list),1,ft);
        fclose(fp);
        fclose(ft);

        remove("contact.txt");
        rename("temp.dat","contact.txt");
        break;

        /* ********************delete contacts**********************/

    case 5:
        system("cls");
        fflush(stdin);
        printf("\n\n\t DELETE A CONTACT\n\t==========================\n\t Enter the name of contact to delete:");
        scanf("%[^\n]",&name);
        fp=fopen("contact.txt","r");
        ft=fopen("temp.dat","w");

        while(fread(&list,sizeof(list),1,fp)!=0)
            if (stricmp(name,list.name)!=0)
                fwrite(&list,sizeof(list),1,ft);
        fclose(fp);
        fclose(ft);

        remove("contact.txt");
        rename("temp.dat","contact.txt");
        break;

    default:
        printf("Invalid choice");
        break;

    }

    printf("\n\n\n Enter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n");
    scanf("%d",&ch);
    switch (ch)
    {
        case 1:
        goto main;
    case 0:
        break;
    default:
        printf("Invalid choice");
        break;
    }

    return 0;
}
