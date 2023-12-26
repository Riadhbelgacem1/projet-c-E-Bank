#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

#define ll 30
int i, j;
int main_exit;
void close();
void menu();

enum
{
    TND, EUR, USDT
} tdevise;

enum
{
    COURANT, EPARGNE
} typec;

struct date
{
    int mounth, day, year;
};

typedef struct adresse
{
    char ville[ll];
    char rue[ll];
    int codepos;
} adresse;

struct
{
    double idlcli;
    char nomcli[ll];
    char prenomcli[ll];
    struct date date_naissance;
    struct date date_crea;
    char mailcli[ll];
    struct adresse adresse;
    int phone;
    float flouc;
    char typec[ll];
} client, upd, check, rem, transaction;

struct
{
    int idcompte;
    int idclient;
    char typec[ll];
    struct date date_com;
} vcompte;

void fordelay(int j)
{
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

void comptjdid()
{
    FILE *txt;
    txt = fopen("record", "a+");
    system("cls");
    printf("\t\t\t\t\******Add account******");
    printf("\n\n\n donner votre nom:");
    scanf("%s", client.nomcli);
    printf("\n donner votre prenom:");
    scanf("%s", client.prenomcli);
    printf("\n donner votre date de naissance:(mm/dd/yyyy)");
    scanf("%d/%d/%d", &client.date_naissance.mounth, &client.date_naissance.day, &client.date_naissance.year);
    printf("\n donner la date d'aujourd-hui:");
    scanf("%d/%d/%d", &client.date_crea.mounth, &client.date_crea.day, &client.date_crea.year);
    printf("\n donner votre num de compte :");
    scanf("%lf", &client.idlcli);
    printf("\n donner le num de telphone:");
    scanf("%d", &client.phone);
    printf("\n donner le mail client:");
    scanf("%s", client.mailcli);
    printf("\n donner votre adresse:(ville/rue/codepostale");
    scanf("%s %s %d", client.adresse.ville, client.adresse.rue, &client.adresse.codepos);
    printf("\nType du compte:\n\t#EPARGNE\n\t#COURANT\n\n\tEnter your choice:");
    scanf("%s", client.typec);
    fprintf(txt,"%lf %s %d/%d/%d %d %s %s %d %s \n", client.idlcli, client.nomcli, client.date_naissance.mounth, client.date_naissance.day, client.date_naissance.year, client.phone, client.mailcli, client.adresse.ville, client.adresse.codepos, client.typec);
    fclose(txt);
    printf("\nAccount created successfully!");
    printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        exit(0);
}

void badel(void)
{
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");
    printf("\nEnter the account no. of the customer whose info you want to change:");
    scanf("%lf", &upd.idlcli);
    while (fscanf(old, "%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", &client.idlcli, client.nomcli, &client.date_naissance.mounth, &client.date_naissance.day, &client.date_naissance.year, &client.phone, client.mailcli, client.adresse.ville, &client.adresse.codepos, client.typec, &client.flouc) != EOF)
    {
        if (client.idlcli == upd.idlcli)
        {
            test = 1;
            printf("\nWhich information do you want to change?\n1.Address mail\n2.Num de telephone\n\nentrer votre choix(1 pour address mail and 2 pour telephone):");
            scanf("%d", &choice);
            system("cls");
            if (choice == 1)
            {
                printf("Entrer la nouvelle adresse mail:");
                scanf("%s", upd.mailcli);
                fprintf(newrec, "%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", client.idlcli, client.nomcli, client.date_naissance.mounth, client.date_naissance.day, client.date_naissance.year, client.phone, upd.mailcli, client.adresse.ville, client.adresse.codepos, client.typec, client.flouc);
                system("cls");
                printf("Changes saved!");
            }
            else if (choice == 2)
            {
                printf("Entrer la nouvelle numero de telephone :");
                scanf("%d", &upd.phone);
                fprintf(newrec, "%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", client.idlcli, client.nomcli, client.date_naissance.mounth, client.date_naissance.day, client.date_naissance.year, upd.phone, client.mailcli, client.adresse.ville, client.adresse.codepos, client.typec, client.flouc);
                system("cls");
                printf("Changes saved!");
            }
        }
        else
            fprintf(newrec, "%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", &client.idlcli, client.nomcli, &client.date_naissance.mounth, &client.date_naissance.day, &client.date_naissance.year, &client.phone, client.mailcli, client.adresse.ville, &client.adresse.codepos, client.typec, &client.flouc);
    }
    fclose(old);
    fclose(newrec);
    remove("record.txt");
    rename("new.txt", "record.txt");

    if (test != 1)
    {
        system("cls");
        printf("\n Record not found!!\a\a\a");
    edit_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            exit(0);
        else if (main_exit == 0)
            badel();
        else
        {
            printf("\nInvalid!\a");
            goto edit_invalid;
        }
    }
    else
    {
        printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            exit(0);
    }
}

void hawel(void)
{
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.txt", "r");
    newrec = fopen("new.txt", "w");

    printf("Enter the account no. of the customer:");
    scanf("%lf", &transaction.idlcli);
    while (fscanf(old,"%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", &client.idlcli, client.nomcli, &client.date_naissance.mounth, &client.date_naissance.day, &client.date_naissance.year, &client.phone, client.mailcli, client.adresse.ville, &client.adresse.codepos, client.typec, &client.flouc) != EOF)
    {

        if (client.idlcli == transaction.idlcli)
        {
            test = 1;
            printf("\n\n Do you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("Enter the amount you want to deposit:$ ");
                scanf("%f", &transaction.flouc);
                client.flouc += transaction.flouc;
                fprintf(newrec, "%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", client.idlcli, client.nomcli, &client.date_naissance.mounth, client.date_naissance.day, client.date_naissance.year, client.phone, client.mailcli, client.adresse.ville, client.adresse.codepos, client.typec, client.flouc);
                printf("\n\nDeposited successfully!");
            }
            else
            {
                printf("Enter the amount you want to withdraw:$ ");
                scanf("%f", &transaction.flouc);
                client.flouc -= transaction.flouc;
                fprintf(newrec,"%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", client.idlcli, client.nomcli, &client.date_naissance.mounth, client.date_naissance.day, client.date_naissance.year, client.phone, client.mailcli, client.adresse.ville, client.adresse.codepos, client.typec, client.flouc);
                printf("\n\nWithdrawn successfully!");
            }
        }
        else
        {
            fprintf(newrec, "%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", client.idlcli, client.nomcli, client.date_naissance.mounth, client.date_naissance.day, client.date_naissance.year, client.phone, client.mailcli, client.adresse.ville, client.adresse.codepos, client.typec, client.flouc);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.txt");
    rename("new.txt", "record.txt");
    if (test != 1)
    {
        printf("\n\nRecord not found!!");
    transact_invalid:
        printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 0)
            hawel();
        else if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            exit(0);
        else
        {
            printf("\nInvalid!");
            goto transact_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else
            exit(0);
    }
}

void chouf(void)
{
    FILE *txt;
    int test = 0;
    txt = fopen("record.txt","r");
    printf("donner votre numero de client:");
    scanf("%lf", &check.idlcli);
    while (fscanf(txt,"%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", &client.idlcli, client.nomcli, &client.date_naissance.mounth, &client.date_naissance.day, &client.date_naissance.year, &client.phone, client.mailcli, client.adresse.ville, &client.adresse.codepos, client.typec, &client.flouc) != EOF)
    {
        if (client.idlcli == check.idlcli)
        {
            system("cls");
            test = 1;
            printf("n\ Numero du compte:%.0lf \n Nom de client:%s \nPrenom client %s \n Date de naissance:%d/%d/%d \nMail: %s \n Numero de telephone: %d \n Adresse %s/%s/%d \n Solde:DT %f\n", client.idlcli, client.nomcli, client.prenomcli, client.date_naissance.mounth, client.date_naissance.day, client.date_naissance.year, client.mailcli, client.phone, client.adresse.ville, client.adresse.rue, client.adresse.codepos, client.flouc);
            if (strcmpi(client.typec, "current") == 0)
            {

                printf("\n\nT'a pas le droit \a\a");
            }
            else
            {
                float interest = (client.flouc * 8) / 1200;
                printf("\n\n You will get DT.%.2f as interest on %.0lf of every month", interest, client.flouc);
            }
        }
    }

    fclose(txt);
    if (test != 1)
    {
        system("cls");
        printf("\nRecord not found!!\a\a\a");
    see_invalid:
        printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            exit(0);
        else if (main_exit == 0)
            chouf();
        else
        {
            system("cls");
            printf("\nInvalid!\a");
            goto see_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &main_exit);
    }
    if (main_exit == 1)
    {
        system("cls");
        menu();
    }

    else
    {

        system("cls");
        exit(0);
    }
}

void fasakh(void)
{
    FILE *old, *newr;
    int test=0;
    old=fopen("record.txt","r");
    newr=fopen("new.txt","w");
    printf("donner le numero de compte a supprimer:");
    scanf("%d",&rem.idlcli);
    while(fscanf(old,"%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", &client.idlcli, client.nomcli, &client.date_naissance.mounth, &client.date_naissance.day, &client.date_naissance.year, &client.phone, client.mailcli, client.adresse.ville, &client.adresse.codepos, client.typec, &client.flouc)!=EOF)
    {
        if(client.idlcli!=rem.idlcli)
        {
            fprintf(newr,"%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", &client.idlcli, client.nomcli, &client.date_naissance.mounth, &client.date_naissance.day, &client.date_naissance.year, &client.phone, client.mailcli, client.adresse.ville, &client.adresse.codepos, client.typec, &client.flouc);
        }
        else
            {test++;
            printf("\nRecord deleted successfully!\n");
            }
   }
   fclose(old);
   fclose(newr);
   remove("record.txt");
   rename("new.txt","record.txt");
   if(test==0)
        {
            printf("\nRecord not found!!\a\a\a");
            erase_invalid:
              printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
              scanf("%d",&main_exit);

                 if (main_exit==1)
                    menu();
                else if (main_exit==2)
                    close();
                else if(main_exit==0)
                    fasakh();
                else
                    {printf("\nInvalid!\a");
                    goto erase_invalid;}
        }
    else
        {printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else
            close();
        }
}
void view_list()
{
    FILE *view;
    view=fopen("record.txt","r");
    int test=0;
    system("cls");
    printf("\nCOMTE. NO.\tNOM\t\t\tADDRESSMAIL\t\t\tPHONE\n");

    while(fscanf(view,"%lf %s %d/%d/%d %lf %s %s %lf %s %f\n", &client.idlcli, client.nomcli, &client.date_naissance.mounth, &client.date_naissance.day, &client.date_naissance.year, &client.phone, client.mailcli, client.adresse.ville, &client.adresse.codepos, client.typec, &client.flouc) != EOF)
{
    printf("\n%f\t\t\t %s\t\t\t %s\t\t\t %.0lf", client.idlcli, client.nomcli, client.mailcli, client.phone);
    test++;
}

    fclose(view);
    if (test==0)
        {   system("cls");
            printf("\nNO RECORDS!!\n");}

    view_list_invalid:
     printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        system("cls");
        if (main_exit==1)
            menu();
        else if(main_exit==0)
            close();
        else
        {
            printf("\nInvalid!\a");
            goto view_list_invalid;
        }
}
void close(void)
{
    printf("\n\n\n\ Thanks you");
    }

void menu(void)
{   int choice;
    system("cls");
    system("color 3");
    printf("\n\n\t\t\t               E-Bank");
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BIENVENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t[1] Creer un nouveau compte\n\t\t[2] Mise à jour des informations dun compte existant.\n\t\t[3] Transactions\n\t\t[4] Afficher les details d un compte existant\n\t\t[5]Supprimer un compte existant\n\t\t[6] Afficher la liste des clients\n\t\t[7] Exit\n\n\n\t\t Enter your choice:");
    scanf("%d",&choice);

    system("cls");
    switch(choice)
    {
        case 1:comptjdid();
        break;
        case 2:badel();
        break;
        case 3:hawel();
        break;
        case 4:chouf();
        break;
        case 5:fasakh();
        break;
        case 6:view_list();
        break;
        case 7:close();
        break;
    }

}

int main()
{
    char pass[10],password[10]="riad";
    int i=0;
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login ");
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s",pass);
    if (strcmp(pass,password)==0)
        {printf("\n\nPassword Match!\nLOADING");
        for(i=0;i<=6;i++)
        {
            fordelay(100000000);
            printf(". ");
        }
        printf("\n");
                system("pause");
				system("cls");
            menu();
        }
    else
        {   printf("\n\nWrong password!!\a\a\a");
            login_try:
            printf("\nEnter 1 to try again and 0 to exit:");
            scanf("%d",&main_exit);
            if (main_exit==1)
                    {

                        system("cls");
                        main();
                    }

            else if (main_exit==0)
                    {
                    system("cls");
                    close();}
            else
                    {printf("\nInvalid!");
                    fordelay(1000000000);
                    system("cls");
                    goto login_try;}

        }
        return 0;
}
