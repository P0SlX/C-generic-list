#ifndef PROJETNEW_EXERCICE1_H
#define PROJETNEW_EXERCICE1_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct tableau *T;

struct tableau
{
    int nb_elem;
    int taille_type;
    void *val;

    void (*afficher)(void *);

    void (*aleatoire)(void *);

    void (*detruire)(void *);
};

T creer(int nb_elem,
        int taille_type,
        void (*afficher)(void *),
        void (*aleatoire)(void *),
        void (*detruire)(void *)
);

void afficher(T tableau);

T aleatoire(int nb_elem,
            int taille_type,
            void (*afficher)(void *),
            void (*aleatoire)(void *),
            void (*detruire)(void *)
);

void detruire_tout(T *tableau);

void trier(T tableau);

#endif //PROJETNEW_EXERCICE1_H
