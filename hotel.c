#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//structure for the hotel food management
struct node{
    char dish_name[200];
    int price;
    //float amount_left;
    struct node* prev;
    struct node* next;
}*header;

void display_menu(struct node* header)
{
    //function for viewing the added dishes
    struct node* ptr = header;
    if(ptr==NULL)
    {
        printf("Sorry the dishes are not ready now!\n");
    }
    else
    {
        while(ptr!=NULL)
        {
            printf("%s",ptr->dish_name);
            printf("%d\n",ptr->price);
            ptr=ptr->next;
        }
    }
}

struct node* add_new(struct node* header)
{
    //function for adding new dishes
    struct node* new = malloc(sizeof(struct node));
    new->next=NULL;
    struct node* ptr = header;
    printf("Enter the name of the dish:");
    fgetc(stdin);
    fgets(new->dish_name,200,stdin);
    printf("Enter the unit price of the dish:");
    scanf("%d",&new->price);
    fgetc(stdin);
    if(ptr==NULL)
    {
        new->prev=NULL;
        header=new;
    }
    else
    {
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        new->prev=ptr;
        ptr->next=new;
    }
    return header;
}

//function to delete the dishes
struct node* delete_dish(struct node* header)
{
    struct node* ptr=header;
    int k,i=1;
    if(ptr==NULL)
    {
        printf("There are no available dishes in the list to delete!\n");
    }
    else
    {
        display_menu(header);
        printf("Enter the Dish index to delete:");
        scanf("%d",&k);
        while(ptr!=NULL)
        {
            if(i==k)
            {
                break;
            }
            i=i+1;
            ptr=ptr->next;
        }
        if(ptr==NULL)
        {
            printf("Entered index out of bound!\n");
        }
        else if(ptr->next==NULL)
        {
            if(ptr->prev==NULL)
            {
                header = ptr->next;
                //free(ptr);
            }
            else
            {
                ptr->prev->next=NULL;
                //free(ptr);
            }
        }
        else if(ptr==header)
        {
            ptr->next->prev=NULL;
            header=ptr->next;
            //free(ptr);
        }
        else
        {
            ptr->prev->next=ptr->next;
            ptr->next->prev=ptr->prev;
            //free(ptr);
        }
    }
    return header;
}

struct node* Modify(struct node* header)
{
    struct node* ptr=header;
    char temp[50];
    int k,i=1,nprice;
    display_menu(header);
    if(ptr==NULL)
    {
        printf("Sorry the dishes are not ready now!\n");
    }
    else
    {
        printf("\nEnter Dish Index whose Price has to be Altered:");
        scanf("%d",&k);
        while(ptr!=NULL)
        {
            if(i==k)
            break;
            i=i+1;
            ptr=ptr->next;
        }
        if(ptr==NULL)
        {
            printf("The entered dish index is not accessible!\n");
        }
        else
        {
            printf("Enter New Price for the Dish:");
            scanf("%d",&nprice);
            ptr->price=nprice;
            printf("Dish Price Changed!\n");
        }
    }
    return header;
}

//--------------function detailing about the admin section...............
void admin(struct node* header)
{
    int option, flag=0;
    while(flag==0)
    {
        printf("Choose an option:\n1.Display menu\n2.Add new item\n3.Delete dish\n4.Modify price of dish\n");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            display_menu(header);
            break;
        case 2:
            header=add_new(header);
            break;
        case 3:
            header=delete_dish(header);
            break;
        case 4:
            header=Modify(header);
            break;
        case 5:
            flag=1;
            break;
        default:
            printf("invalid choice!\n");
            break;
        }
    }
}


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
    //struct node* header=NULL;
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
                admin(header);
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
