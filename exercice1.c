#include "exercice1.h"

T creer(int nb_elem, int taille_type, void (*afficher)(void *), void (*aleatoire)(void *),
        void (*detruire)(void *))
{
    // On réserve la place mémoire pour la struct
    T tab = (T) malloc(sizeof(struct tableau));
    // On réserve aussi la place pour l'array et on remet tout à 0
    tab->val = (void *) calloc(nb_elem, taille_type);

    // On assigne ensuite toutes les données passées en paramètre
    tab->nb_elem = nb_elem;
    tab->taille_type = taille_type;
    tab->afficher = (*afficher);
    tab->aleatoire = (*aleatoire);
    tab->detruire = (*detruire);
    return tab;
}

void afficher(T tableau)
{
    // On appelle la fonction affiché assigné au tableau
    // et on lui passe l'array et le nombre d'élément dedans en paramètre
    char *current_elem = tableau->val;
    void *end = current_elem + (tableau->nb_elem * tableau->taille_type);

    // On va parcourir l'array jusqu'à la fin et appeler la fonction affichage sur chaque éléments
    while (current_elem != end) {
        (tableau->afficher)(current_elem);
        current_elem += tableau->taille_type;
    }
    printf("\n");
}

T aleatoire(int nb_elem, int taille_type, void (*afficher)(void *), void (*aleatoire)(void *),
            void (*detruire)(void *))
{
    // On créer un tableau
    T tab = creer(nb_elem, taille_type, afficher, aleatoire, detruire);

    // Pour ensuite lui attribuer des valeurs aléatoires
    tab->nb_elem = nb_elem;
    char *current_elem = tab->val;
    void *end = current_elem + (nb_elem * taille_type);

    // On va parcourir l'array jusqu'à la fin et appeler la fonction affichage sur chaque éléments
    while (current_elem != end) {
        (tab->aleatoire)(current_elem);
        current_elem += taille_type;
    }
    return tab;
}

void detruire_tout(T *tableau)
{
    // On appelle la fonction détruire assigné à la struct avec l'adresse de l'array
    ((*tableau)->detruire)((*tableau)->val);
    // Et enfin on libère le tableau
    free(*tableau);
    tableau = NULL;
}

int compare(const void *a, const void *b)
{
    return (*(int *) a - *(int *) b);
}

void trier(T tableau)
{
    qsort(tableau->val, tableau->nb_elem, tableau->taille_type, compare);
}
