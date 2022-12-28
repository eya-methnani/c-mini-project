#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct product
{
    char name[50];
    float price;
    int quantity;
} product;
typedef struct stock
{
    product val;
    struct stock *suiv;
} stock;
typedef struct date
{
    int day;
    int month;
    int year;
} date;
typedef struct historique
{
    product produit;
    date date;
    char description[13];
    struct historique *suiv;
} historique;
void main()
{
    void addProduct(stock * *head, product product, date date, historique * *first);
    void deleteProduct(stock * *head, char name[20], historique **first, date date);
    void modifyProduct(stock * *head, char name[20], char newName[20], int newQuantity, float Newprice);
    void RechercheProduct(stock * *head, char name[20]);
    void printStock(stock * *head);
    void printProduct(stock * *head, char name[20]);
    void HistoriqueMois(historique * *head, int mois);
    void Historiqueyear(historique * *head, int year);
    char x[20];
    // initialiser des listes chainées vides
    stock *head = NULL;
    historique *first = NULL;
    printf("HI and welcome to our database.To add a product type add .To remove a product type remove. If you want to quit type quit: ");
    gets(x);
    while (strcmp(x, "quit") != 0)
    {
        if (strcmp(x, "add") == 0)
        {
            product p;
            date d;
            printf("please give us the name of the product:\n");
            gets(p.name);
            printf("please give us the price of the product:\n");
            scanf("%f", &p.price);
            printf("pleaes give us the quantity of the product: \n");
            scanf("%i", &p.quantity);
            printf("please give us the day : \n");
            scanf("%i", &d.day);
            printf("please give us the month: \n");
            scanf("%i", &d.month);
            printf("please give us the year: \n");
            scanf("%i", &d.year);
            addProduct(&head, p, d, &first);
        }
        else if (strcmp(x, "remove") == 0)
        {
            if (head == NULL)
            {
                printf("le stock est vide \n");
            }
            date d1;
            char y[20];
            printf("please give us the name of the product you are willing to delete: \n ");
            gets(y);
            printf("please give us the day : \n");
            scanf("%i", &d1.day);
            printf("please give us the month: \n");
            scanf("%i", &d1.month);
            printf("please give us the year: \n");
            scanf("%i", &d1.year);

            deleteProduct(&head, y, &first, d1);
        }
        else if (strcmp(x, "modify") == 0)
        {
            char nom[20];
            char newnom[20];
            int newquan;
            float newpri;
            printf("enter the name of the product you want to modify: \n ");
            gets(nom);
            printf("enter the new name: \n ");
            gets(newnom);
            printf("enter the new quantity: \n");
            scanf("%d", &newquan);
            printf("enter the new price: \n");
            scanf("%f", &newpri);
            modifyProduct(&head, nom, newnom, newquan, newpri);
        }
        else if (strcmp(x, "affiche") == 0)
        {
            char ch[20];
            printf("enter the name of the product you want to see: \n");
            gets(ch);
            printProduct(&head, ch);
        }
        else if (strcmp(x, "search") == 0)
        {
            char esmk[20];
            printf("enter the name of the product you want to search: \n");
            gets(esmk);
            RechercheProduct(&head, esmk);
        }
        else if (strcmp(x, "history") == 0)
        {
            char ss[10];
            printf("if you want to see the history of month type month,Of year type year: \n");
            gets(ss);
            if (strcmp(ss, "month") == 0)
            {
                int moiss;
                printf("give us the month: \n");
                scanf("%d", &moiss);
                HistoriqueMois(&first, moiss);
            }
            else if (strcmp(ss, "year") == 0)
            {
                int yearrr;
                printf("give us the year: \n");
                scanf("%d", &yearrr);
                Historiqueyear(&first, yearrr);
            }
        }
        else if (strcmp(x, "stock") == 0)
        {
            printStock(&head);
        }

        printf(" HI and welcome to our database.\n");
        printf("To add a product type add.\n");
        printf("To remove a product type remove.\n");
        printf("To modify a product type modify.\n");
        printf("to read a product description type affiche.\n");
        printf("To look for a product type search.\n");
        printf("To visualize the stock type stock.\n");
        printf("To read the history type history.\n");
        printf("If you want to quit type quit: ");
        gets(x);
    }
}

void addProduct(stock **head, product product, date date, historique **first)
{
    // Créez un nouvel élément de la liste
    stock *newstock = (stock *)malloc(sizeof(stock));
    newstock->val = product;
    newstock->suiv = NULL;
    // Si la liste est vide, mettez le nouvel élément en tête de liste
    if (*head == NULL)
    {
        *head = newstock;
    }
    else
    {
        // Sinon, trouvez la fin de la liste et ajoutez le nouvel élément
        stock *current = *head;
        while (current->suiv != NULL)
        {
            current = current->suiv;
        }
        current->suiv = newstock;
    }
    // ajout dans l'historique
    historique *newHis = (historique *)malloc(sizeof(historique));
    newHis->produit = product;
    newHis->date = date;
    strcpy(newHis->description, "added \n");
    newHis->suiv = NULL;
    // Si la liste est vide, mettez le nouvel élément en tête de liste
    if (*first == NULL)
    {
        *first = newHis;
    }
    else
    {
        // Sinon, trouvez la fin de la liste et ajoutez le nouvel élément
        historique *curr = *first;
        while (curr->suiv != NULL)
        {
            curr = curr->suiv;
        }
        curr->suiv = newHis;
    }
}
// Affiche les informations sur un produit donné
void printProduct(stock **head, char name[20])
{
    stock *aux = *head;
    stock *auxx = *head;

    int test;
    test = 0;

    while (auxx->suiv != NULL)
    {
        auxx = auxx->suiv;
    }
    if (strcmp(auxx->val.name, name) == 0)
    {
        printf("name: ");
        puts(auxx->val.name);
        printf("Quantity : %d\n", auxx->val.quantity);
        printf("Price : %.2f\n", auxx->val.price);
        test = 1;
    }
    if (aux->suiv == NULL)
    {
        if (strcmp(aux->val.name, name) == 0)
        {
            test = 1;
            printf("name: ");
            puts(aux->val.name);
            printf("Quantity : %d\n", aux->val.quantity);
            printf("Price : %.2f\n", aux->val.price);
        }
    }
    else
    {
        while ((aux->suiv != NULL) && (test == 0))
        {
            if (strcmp(aux->val.name, name) == 0)
            {
                test = 1;
                printf("name: ");
                puts(aux->val.name);
                printf("Quantity : %d\n", aux->val.quantity);
                printf("Price : %.2f\n", aux->val.price);
            }
            else
            {
                aux = aux->suiv;
            }
        }
    };

    if (test == 0)
    {
        printf("The product you want to see is unavailable \n ");
    }
}
// Supprime un produit de la liste chainée
void deleteProduct(stock **head, char name[20], historique **first, date date)
{
    // Si la liste est vide, il n'y a rien à faire
    /*if (*head == NULL)
    {
        printf("le stock est vide \n ");
        return;
    }*/
    // Si le produit à supprimer est en tête de liste, supprimez-le
    stock *current = *head;
    stock *aux = *head;
    stock *au = *head;
    product p1;
    aux = au->suiv;
    while (aux->suiv != NULL)
    {
        aux = aux->suiv;
        au = au->suiv;
    }
    if (strcmp(aux->val.name, name) == 0)
    {
        au->suiv = NULL;
        free(aux);
        printf("the product has been deleted \n");
    }
    if (strcmp(current->val.name, name) == 0)
    {
        p1 = current->val;
        *head = current->suiv;
        free(current);
        printf("the product has been deleted \n");
    }
    else
    {
        int test;
        test = 0;

        // Sinon, parcourez la liste et supprimez le produit s'il est trouvé
        while ((current->suiv != NULL) && (test == 0))
        {
            if (strcmp(current->suiv->val.name, name) == 0)
            {
                stock *temp = current->suiv;
                p1 = temp->val;
                current->suiv = temp->suiv;
                free(temp);
                test = 1;
                printf("the product has been deleted \n");
            }
            current = current->suiv;
        }
        if (test == 0)
        {
            printf("the product is not available in stock \n");
            return;
        }
    }

    // ajout dans l'historique
    historique *newHis = (historique *)malloc(sizeof(historique));
    newHis->produit = p1;
    newHis->date = date;
    strcpy(newHis->description, " deleted \n");
    newHis->suiv = NULL;
    historique *curr = *first;
    while (curr->suiv != NULL)
    {
        curr = curr->suiv;
    }
    curr->suiv = newHis;
}
// modifier le produit
void modifyProduct(stock **head, char name[20], char newName[20], int newQuantity, float Newprice)
{
    stock *current = *head;
    stock *aux = *head;
    int test;
    test = 0;
    while (aux->suiv != NULL)
    {
        aux = aux->suiv;
    }
    if (strcmp(aux->val.name, name) == 0)
    {
        strcpy(current->val.name, newName);
        current->val.quantity = newQuantity;
        current->val.price = Newprice;
        test = 1;
    }
    while ((head != NULL) && (test == 0))
    {
        if (strcmp(current->val.name, name) == 0)
        {
            strcpy(current->val.name, newName);
            current->val.quantity = newQuantity;
            current->val.price = Newprice;
            test = 1;
        }
        current = current->suiv;
    }
    if (test == 0)
    {
        printf("the willing product is not in the stock");
    }
}
void RechercheProduct(stock **head, char name[20])
{
    stock *aux = *head;
    stock *current = *head;
    int test;
    test = 0;
    while (current->suiv != NULL)
    {
        current = current->suiv;
    }
    if (strcmp(current->val.name, name) == 0)
    {
        test = 1;
        printf(" the product does exist in stock \n");
    }
    while ((aux->suiv != NULL) && (test == 0))
    {
        if (strcmp(aux->val.name, name) == 0)
        {
            test = 1;
            printf(" the product does exist in stock \n");
        }
        else
        {
            aux = aux->suiv;
        }
    }

    if (test == 0)
    {
        printf("the product is not available in stock \n");
        return;
    }
}
// Fonction pour afficher le stock actuel
void printStock(stock **head)
{
    stock *aux = *head;
    printf("Stock actuel :\n");
    while (aux != NULL)
    {
        printf("- %s : quantity: %d, price: %f ", aux->val.name, aux->val.quantity, aux->val.price);
        printf("\n");
        aux = aux->suiv;
    }
}
// afficher l'historique jour par jour
void HistoriqueMois(historique **head, int mois)
{
    historique *aux = *head;
    while (aux != NULL)
    {
        if (aux->date.month == mois)
        {
            printf("%s :\n ", aux->produit.name);
            printf("%s : \n", aux->description);
            printf("%d / %d / %d\n", aux->date.day, aux->date.month, aux->date.year);
        }
        aux = aux->suiv;
    }
}
// afficher l'historique mois par mois
void Historiqueyear(historique **head, int year)
{
    historique *aux = *head;
    while (aux != NULL)
    {
        if (aux->date.year == year)
        {
            printf("%s :\n", aux->produit.name);
            printf("%s :\n", aux->description);
            printf("%d / %d / %d\n", aux->date.day, aux->date.month, aux->date.year);
        }
        aux = aux->suiv;
    }
}