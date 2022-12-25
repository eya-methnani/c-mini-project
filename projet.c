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
    strcpy(newHis->description, "suppression \n");
    newHis->suiv = NULL;
    historique *curr = *first;
    while (curr->suiv != NULL)
    {
        curr = curr->suiv;
    }
    curr->suiv = newHis;
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
            printf("%d / %d / %d", aux->date.day, aux->date.month, aux->date.year);
        }
        aux = aux->suiv;
    }
}