#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//structure for the hotel food management
struct node{
    char dish_name[200];
    int price;
    struct node* prev;
    struct node* next;
}*header;
//structure for the customer food management
struct order
{
    char dish_name[200];
    int price, qty;
    struct order *prev1;
    struct order *next1;
}*header1;


//sample function to display the dishes ordered
void display_order(struct order *header1)
{
    int i=1;
    struct order *ptr1 = header1;
    if (ptr1 == NULL)
    {
        printf("Oops , no dishes are ordered yet!1\n");
    }
    else
    {
        while (ptr1 != NULL)
        {
            printf("%d\n",i);
            printf("%s", ptr1->dish_name);
            printf("%d\n", ptr1->price);
            ptr1 = ptr1->next1;
            i++;
        }
    }
}

//function to display the menu
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
        int i=1;
        while(ptr!=NULL)
        {
            printf("%d\n",i);
            printf("%s",ptr->dish_name);
            printf("%d\n",ptr->price);
            ptr=ptr->next;
            i++;
        }
    }
}

/////////////////////////////////////////////ADMIN FUNCTIONS START//////////////////////////////////////////////////
struct node* add_new(struct node* header)
{
    //function for adding new dishes
    struct node* newnode = (struct node*) malloc(sizeof(struct node));
    newnode->next=NULL;
    struct node* ptr = header;
    printf("Enter the name of the dish:");
    fgetc(stdin);
    fgets(newnode->dish_name,200,stdin);
    printf("Enter the unit price of the dish:");
    scanf("%d",&newnode->price);
    fgetc(stdin);
    if(ptr==NULL)
    {
        newnode->prev=NULL;
        header=newnode;
    }
    else
    {
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        newnode->prev=ptr;
        ptr->next=newnode;
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
/////////////////////////////////////////////ADMIN FUNCTIONS END///////////////////////////////////////////////////

////////////////////////////////////////CUSTOMER FUNCTION STARTS///////////////////////////////////////////////////
struct order* searchNode(struct node *header, struct order *header1, int num, int qty)
{
    int i = 1, flag=0;
    struct node *ptr = header;
    struct order *ptr1 = header1;
    struct order* new1 = (struct order*)malloc(sizeof(struct order));
    new1->next1 = NULL;
    while (ptr != NULL)
    {
        if (i == num)
        {
            strcpy(new1->dish_name, ptr->dish_name);
            new1->price = (ptr->price)*qty;
            new1->qty=qty;
            flag=1;
            break;
        }
        ptr=ptr->next;
        i++;
    }
    if(flag==1)
    {
        if(ptr1==NULL)
        {
            header1 = new1;
        }
        else
        {
            while(ptr1->next1!=NULL)
            {
                ptr1=ptr1->next1;
            }
            new1->prev1=ptr1;
            ptr1->next1=new1;
        }
        printf("Order places successfully\n");
    }
    else
    {
        printf("Dish with the entered index number is not present!\n");
    }
    return header1;
}
struct order* placeOrder(struct node* header,struct order* header1)
{
   
    int i=1,index, qty;
    struct node *ptr=header;
    if (ptr== NULL)
    {
        printf("Dishes are not yet ready to be ordered!!\n");
        //return 0;
    }
    else
    {
    	display_order(header1);
        printf("Place the order from the given menu above(Enter '-1' to finish ordering):\n");
        while(1)
        {
            printf("Enter the the dish index: ");
            scanf("%d",&index);
            if(index==-1)
            {
            	if (i== 1)
                {
                    printf("Order is empty");
                }
                else
                {
                	printf("Order placed successfully..\n");
                	break;
                }
            }
            else
            {
            	printf("Enter the quantity of the selected dish:");
                scanf("%d", &qty);
                header1=searchNode(header, header1, index, qty);
                i++;
            }
        }
    }
    display_order(header1);
    return header1;   
}
void generate_bill(struct order* header1)
{
    struct order* temp=header1;
    int i=1;
    if (temp== NULL)
    {
        printf("No food is ordered");
    }
    else
    {
        printf("---------------------MENU---------------------\n");
        printf("sl no\tDish Name\tquantity\tPrice\n");
        while(temp!=NULL)
        {
            int j;
            printf("%d     \t",i);
            for(j=0;temp->dish_name[j]!='\n';j++)
            {
                printf("%c",temp->dish_name[j]);
            }
            printf("\t  \t%d         \t%d\n",temp->qty,temp->price);
            temp=temp->next1;
            i++;
        }
    }
}




/////////////////////////////CUSTOMER FUNCTION END//////////////////////////////////////////

//--------------function detailing about the admin section...............
struct node* admin(struct node* header)
{
    int option, flag=0;
    while(flag==0)
    {
        printf("Choose an option:\n1.Display menu\n2.Add new item\n3.Delete dish\n4.Modify price of dish\n5.logout\n");
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
    return header;
}

//................................function detailing about the customer section.........................
struct order* customer(struct node* header, struct order* header1)
{
    int option, flag=0;
    while(flag==0)
    {
        printf("Choose an option:\n1.Display menu\n2.Place order.\n3.Generate bill\n4.Logout\n");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            display_menu(header);
            break;
        case 2:
            header1=placeOrder(header, header1);
            break;
        case 3:
            generate_bill(header1);
            break;
        case 4:
            flag=1;
            break;
        default:
            printf("invalid choice!\n");
            break;
        }
    }
    return header1;
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
                header=admin(header);
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
            if(is_customer())
            {
                printf("Succesfully logined as customer!\n");
                header1=customer(header, header1);
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
