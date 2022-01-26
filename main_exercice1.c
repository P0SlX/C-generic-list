#include "exercice1.h"

struct test
{
    long long int a;
    long long int b;
    long long int c;
};

static void afficher_structure(void *val)
{
    // On récupère le pointeur de structure
    struct test *val_ptr = (struct test *) val;
    long long int total = val_ptr->a + val_ptr->b + val_ptr->c;
    printf("Structure : ");
    printf(" a = %lld, b = %lld, c = %lld  |  Total : %lld\n", val_ptr->a, val_ptr->b, val_ptr->c, total);
}

void aleatoire_structure(void *val)
{
    // On récupère le pointeur de structure
    struct test *val_ptr = (struct test *) val;
    // Et on assigne des valeurs aléatoires
    val_ptr->a = rand() % INT_MAX;
    val_ptr->b = rand() % INT_MAX;
    val_ptr->c = rand() % INT_MAX;
}

void detruire_struct(void *s)
{
    // On libère la zone mémoire de la struct
    struct test *s_ptr = (struct test *) s;
    free(&(*s_ptr));
    s = NULL;
}

static void afficher_int(void *val)
{
    // On récupère le pointeur de structure
    int *val_int = (int *) val;
    printf("%d ", *val_int);
}

void aleatoire_int(void *val)
{
    // On récupère le pointeur de structure
    int *val_int = (int *) val;
    // Et on assigne des valeurs aléatoires
    *val_int = rand() % INT_MAX;
}

void detruire_int(void *s)
{
    // On libère la zone mémoire de la struct
    int *s_ptr = (int *) s;
    free(&(*s_ptr));
    s = NULL;
}


int main()
{

    srand(time(NULL));
    T array = aleatoire(10, sizeof(int), &afficher_int, &aleatoire_int, &detruire_int);
    T array_1 = aleatoire(10, sizeof(struct test), &afficher_structure, &aleatoire_structure, &detruire_struct);

    printf("aleatoire() d'entiers : ");
    afficher(array); // affichage de array
    printf("aleatoire() de struct test : \n");
    afficher(array_1); // affichage de array_1

    trier(array);
    printf("trier() d'entiers : ");
    afficher(array); // affichage de array

    detruire_tout(&array); // destruction de array
    detruire_tout(&array_1); // destruction de array_1

    return EXIT_SUCCESS;
}
