#ifndef PROJETNEW_EXERCICE2_H
#define PROJETNEW_EXERCICE2_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

typedef struct tableau_variable *T_var;

struct tableau_variable
{
    int nb_elem;
    int taille_type;
    int taille_max;
    void *val;

    void (*afficher)(void *);

    void (*aleatoire)(void *);

    void (*detruire)(void *);
};

void check_ptr(void *ptr);

T_var creer_var(int taille_max,
                int taille_type,
                void (*afficher)(void *),
                void (*aleatoire)(void *),
                void (*detruire)(void *)
);

void afficher_var(T_var tableau);

T_var aleatoire_var(int nb_elem,
                    int taille_type,
                    void (*afficher)(void *),
                    void (*aleatoire)(void *),
                    void (*detruire)(void *)
);

void push(T_var tableau, void *val);

void push_indice(T_var tableau, void *val, int indice);

void *pop(T_var tableau);

void *pop_indice(T_var tableau, int indice);

void detruire_tout(T_var *tableau);

void *maximum(T_var tableau);

T_var slice(T_var tableau, int n, int m);

bool isEven(void *val);

bool isOdd(void *val);

T_var filtrer(T_var tableau, bool (*predicat)(void *));


#endif //PROJETNEW_EXERCICE2_H
