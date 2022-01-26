#include "exercice2.h"

void check_ptr(void *ptr)
{
    if (ptr == NULL) {
        perror("Une erreur est survenue (pointeur à NULL) ");
        exit(EXIT_FAILURE);
    }
}

T_var creer_var(int taille_max, int taille_type, void (*afficher)(void *), void (*aleatoire)(void *),
                void (*detruire)(void *))
{
    // On réserve la place mémoire pour la struct
    T_var tab = (T_var) malloc(sizeof(struct tableau_variable));
    check_ptr(tab);

    // On par défaut une taille de 128x la taille du type pour éviter de realloc a chaque ajout
    // Car ca prend du temps
    tab->val = (void *) calloc(1, taille_max);
    check_ptr(tab->val);
    tab->nb_elem = 0;

    // On assigne ensuite toutes les données passées en paramètre
    tab->taille_max = taille_max;
    tab->taille_type = taille_type;
    tab->afficher = (*afficher);
    tab->aleatoire = (*aleatoire);
    tab->detruire = (*detruire);
    return tab;
}

void afficher_var(T_var tableau)
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


T_var aleatoire_var(int nb_elem, int taille_type, void (*afficher)(void *), void (*aleatoire)(void *),
                    void (*detruire)(void *))
{
    // On déduit la taille max par chunck de 1024 octets pour éviter la realloc a chaque push
    int taille_max = (((nb_elem * taille_type) / 1024) + 1) * 1024;

    // On créer un tableau
    T_var tab = creer_var(taille_max, taille_type, afficher, aleatoire, detruire);

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

void push(T_var tableau, void *val)
{
    char *val_ptr = tableau->val;
    int used_size = tableau->nb_elem * tableau->taille_type;

    // Si ya plus assez de place pour un autre elem, on agrandi l'allocation
    if ((used_size + tableau->taille_type) > tableau->taille_max) {
        tableau->val = (void *) realloc(tableau->val, tableau->taille_max + 1024);
        check_ptr(tableau->val);
        val_ptr = tableau->val;
        tableau->taille_max += 1024;
    }

    // On copie la valeur à la suite
    memcpy(val_ptr + used_size, val, tableau->taille_type);
    tableau->nb_elem++;
}

void push_indice(T_var tableau, void *val, int indice)
{
    // Si l'indice est trop grand, alors on le met à la fin
    if (indice > tableau->nb_elem)
        indice = tableau->nb_elem;

    char *val_ptr = tableau->val;
    int used_size = tableau->nb_elem * tableau->taille_type;

    // Si ya plus assez de place pour un autre elem, on agrandi l'allocation
    if ((used_size + tableau->taille_type) > tableau->taille_max) {
        tableau->val = (void *) realloc(tableau->val, tableau->taille_max + 1024);
        check_ptr(tableau->val);
        val_ptr = tableau->val;
        tableau->taille_max += 1024;
    }

    // On copie les valeurs après l'indice dans un endroit temporaire
    void *tmp = malloc((tableau->nb_elem * tableau->taille_type) - (indice * tableau->taille_type));
    check_ptr(tmp);
    char *start = val_ptr + (indice * tableau->taille_type);
    int size_to_copy = (tableau->nb_elem * tableau->taille_type) - (indice * tableau->taille_type);
    memcpy(tmp, start, size_to_copy);

    // On ajoute l'élément à l'indice
    memcpy(start, val, tableau->taille_type);
    tableau->nb_elem++;

    // On recopie l'array temporaire à la suite
    memcpy(start + tableau->taille_type, tmp, size_to_copy);

    free(tmp);
}

void *pop(T_var tableau)
{
    if (tableau->nb_elem == 0)
        return NULL;

    char *val_ptr = tableau->val;

    // On va chercher l'adresse de la dernière valeur
    void *last_elem = val_ptr + ((tableau->nb_elem * tableau->taille_type) - tableau->taille_type);

    // On alloue de la place et on copie la dernière valeur pour la retourner à la fin
    void *return_ptr = malloc(tableau->taille_type);
    memcpy(return_ptr, last_elem, tableau->taille_type);

    // Et on remet à 0 le dernier élément
    memset(last_elem, 0, tableau->taille_type);
    tableau->nb_elem--;

    // On regarde si on a trop pop et donc on peut realloc pour libérer de l'espace mémoire
    // Ici need_resize sera a 1 quand il y aura 512 octets ou plus de libre dans l'array
    bool need_resize = (((tableau->nb_elem * tableau->taille_type) <= (tableau->taille_max - 1536)) ? 1 : 0) &&
                      (tableau->taille_max > 1024);

    if (need_resize) {
        tableau->val = (void *) realloc(tableau->val, tableau->taille_max - 1024);
        check_ptr(tableau->val);
        tableau->taille_max -= 1024;
    }
    return return_ptr;
}

void *pop_indice(T_var tableau, int indice)
{
    if (tableau->nb_elem == 0)
        return NULL;

    if (tableau->nb_elem == 1)
        pop(tableau);

    char *val_ptr = tableau->val;

    // On récupère l'adresse de l'adresse à copier, la taille et la destination
    void *from = val_ptr + (indice * tableau->taille_type) + tableau->taille_type;
    char *to = val_ptr + (indice * tableau->taille_type);
    int size_to_copy = (tableau->nb_elem * tableau->taille_type) - (indice * tableau->taille_type);

    // On alloue de la place et on copie la dernière valeur pour la retourner à la fin
    void *return_ptr = malloc(tableau->taille_type);
    memcpy(return_ptr, to, tableau->taille_type);

    // On shift d'un élément vers la gauche et réécrire par dessus l'élément à pop
    memcpy(to, from, size_to_copy);

    // On nettoie ce qui reste après le memcpy
    memset(to + size_to_copy, 0, tableau->taille_type);

    tableau->nb_elem--;

    // On regarde si on a trop pop et donc on peut realloc pour libérer de l'espace mémoire
    // Ici need_resize sera a 1 quand il y aura 512 octets ou plus de libre dans l'array
    bool need_resize = (((tableau->nb_elem * tableau->taille_type) <= (tableau->taille_max - 1536)) ? 1 : 0) &&
                      (tableau->taille_max > 1024);

    if (need_resize) {
        tableau->val = (void *) realloc(tableau->val, tableau->taille_max - 1024);
        check_ptr(tableau->val);
        tableau->taille_max -= 1024;
    }
    return return_ptr;
}

void detruire_tout(T_var *tableau)
{
    // On appelle la fonction détruire assigné à la struct avec l'adresse de l'array
    ((*tableau)->detruire)((*tableau)->val);
    // Et enfin on libère le tableau
    free(*tableau);
    tableau = NULL;
}

void *maximum(T_var tableau)
{
    char *ptr = tableau->val;
    void *end = ptr + tableau->nb_elem * tableau->taille_type;
    void *max = ptr;

    // On va parcourir l'array jusqu'à la fin
    while (ptr != end) {
        // Si max est plus grand que ptr
        if (memcmp(max, ptr, tableau->taille_type) < 0) {
            max = ptr;
        }
        ptr += tableau->taille_type;
    }

    return max;
}

T_var slice(T_var tableau, int n, int m)
{
    // Si n ou m n'est pas entre 0 et n items
    if (!(n > 0 && n < tableau->nb_elem) && (m > 0 && m < tableau->nb_elem))
        return NULL;

    char *val_ptr = tableau->val;

    // Taille a prendre
    int taille = (m * tableau->taille_type) - (n * tableau->taille_type);

    // Calcul de l'adresse de n
    void *n_ptr = val_ptr + (n * tableau->taille_type);

    T_var res = creer_var(taille, tableau->taille_type, tableau->afficher, tableau->aleatoire, tableau->detruire);
    memcpy(res->val, n_ptr, taille);
    res->nb_elem = m - n;
    return res;
}

bool isEven(void *val)
{
    int *val_int = (int *) val;
    return *val_int % 2 == 0;
}

bool isOdd(void *val)
{
    int *val_int = (int *) val;
    return *val_int % 2 != 0;
}

T_var filtrer(T_var tableau, bool (*predicat)(void *))
{
    T_var res = creer_var(tableau->taille_max, tableau->taille_type, tableau->afficher, tableau->aleatoire,
                          tableau->detruire);
    char *val_ptr = tableau->val;
    char *res_ptr = res->val;
    int res_nb_elem = 0;

    for (int i = 0; i < tableau->nb_elem; ++i) {
        void *offset = val_ptr + (tableau->taille_type * i);
        if ((*predicat)(offset)) {
            memcpy(res_ptr, offset, tableau->taille_type);
            res_ptr += tableau->taille_type;
            res_nb_elem++;
        }
    }
    res->taille_max = res_nb_elem;
    res->nb_elem = res_nb_elem;
    return res;
}