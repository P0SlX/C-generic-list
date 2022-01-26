#include "exercice2.h"

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
    T_var tableau = aleatoire_var(10, sizeof(int), &afficher_int, &aleatoire_int, &detruire_int);
    T_var tableau_1 = aleatoire_var(10, sizeof(struct test), &afficher_structure, &aleatoire_structure,
                                    &detruire_struct);

    printf("aleatoire_var() d'entier : ");
    afficher_var(tableau); // affichage de tableau
    printf("aleatoire_var() de struct test :\n");
    afficher_var(tableau_1); // affichage de tableau_1

    int a = 8473843;
    struct test t;
    t.a = 1;
    t.b = 2;
    t.c = 3;

    push(tableau, &a);
    push(tableau_1, &t);

    printf("push() d'entier : ");
    afficher_var(tableau); // affichage de tableau
    printf("push() de struct test :\n");
    afficher_var(tableau_1); // affichage de tableau1


    printf("pop() de 2 entier : ");
    void *popped = pop(tableau); // suppression du dernier élément de tableau
    free(popped);
    popped = pop(tableau); // suppression du dernier élément de tableau
    free(popped);

    afficher_var(tableau); // affichage de tableau

    printf("pop() de 2 de struct test :\n");
    popped = pop(tableau_1); // suppression du dernier élément de tableau_1
    free(popped);
    popped = pop(tableau_1); // suppression du dernier élément de tableau_1
    free(popped);
    afficher_var(tableau_1); // affichage de tableau

    push_indice(tableau, &a, 1); // ajout de l'élément à l'indice 1

    printf("push_indice() d'entier à l'indice 1 : ");
    afficher_var(tableau); // affichage de tableau

    popped = pop_indice(tableau_1, 0); // suppression de l'élément à l'indice 0
    free(popped);

    printf("pop_indice() de struct test à l'indice 0 :\n");
    afficher_var(tableau_1); // affichage de tableau

    // Exercice 3

    // 3.1
    void *max_tableau = maximum(tableau);
    printf("maximum() : Adresse %p  |  Valeur : ", max_tableau);
    afficher_int(max_tableau);

    // 3.2
    T_var s = slice(tableau_1, 2, 4);
    printf("\nslice() de struct test entre l'indice 2 et 4 :\n");
    afficher_var(s);

    // 3.3
    T_var f1 = filtrer(tableau, &isEven);
    T_var f2 = filtrer(tableau, &isOdd);

    printf("filtrer() d'entier : isEven() : ");
    afficher_var(f1);
    printf("filtrer() d'entier : isOdd() : ");
    afficher_var(f2);

    detruire_tout(&s); // destruction de s
    detruire_tout(&f1);
    detruire_tout(&f2);
    detruire_tout(&tableau); // destruction de tableau
    detruire_tout(&tableau_1); // destruction de tableau_1

    return EXIT_SUCCESS;
}
