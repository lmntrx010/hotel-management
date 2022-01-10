#include<stdio.h>
#include<string.h>
//structure for the hotel food management
struct node{
    char dish_name[200];
    int price;
    float amount_left;
    struct node* prev;
    struct node* next;
}header;

//function to check the login credentials of the admin
int is_admin()
{
    char username[20], password[20];
    printf("Enter username:");
    scanf("%s",username);
    printf("Enter the password:");
    scanf("%s",password);
    if(strcmp(username,"admin")==0 && strcmp(password,"admin")==0)
    {
        return 1;
    }
    else{
        return 0;
    }
}

//function to check the login credential of the customer
int is_customer()
{
    char username[20], password[20];
    printf("Enter username:");
    scanf("%s",username);
    printf("Enter the password:");
    scanf("%s",password);
    if(strcmp(username,"cust")==0 && strcmp(password,"cust")==0)
    {
        return 1;
    }
    else{
        return 0;
    }
}
//main function
int main()
{
    int option, flag=0;
    while(flag==0)
    {
        printf("1 for admin.\n2 for customer.\n3 exit\n");
        printf("choose your option:");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            printf("admin\n");
            if(is_admin())
            {
                printf("Succesfully logined as admin!\n");
            }
            else
            {
                printf("Invalid username/password for admin!\n");
            }
            //dsiplay menu
            //add new dish
            //delete dish
            //modify the price of the dish
            break;
        case 2:
            printf("user\n");
            if(is_admin())
            {
                printf("Succesfully logined as customer!\n");
            }
            else
            {
                printf("Invalid username/password for customer!\n");
            }
            //view menu
            //place order
            //generate bill for order
            break;
        case 3:
            flag=1;
            break;
        default:
            printf("Unknown option.\n");
            break;
        }
    }
}
