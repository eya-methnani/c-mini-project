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