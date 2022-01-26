# compilateur
CC := gcc
# options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb -Wno-unused-variable -Wno-unused-parameter
TAB := exercice1
LIST := exercice2

# all est la cible choisie par défaut par la commande make
# elle dépend de la règle $(LIST), qui va être réalisée
# NOTE --- les cibles ne doivent pas avoir le même nom qu'un fichier
all : $(LIST) $(TAB)

$(TAB) : exercice1.o main_exercice1.o
# instructions de compilation
# $@ fait référence à la cible, $^ aux dépendances
	$(CC) $(CFLAGS) -o $@ $^

# déclaration des fichiers objets nécessaires à la création de $(LIST)
# exécutée avec la commande make $(LIST)
$(LIST) : exercice2.o main_exercice2.o
# instructions de compilation
# $@ fait référence à la cible, $^ aux dépendances
	$(CC) $(CFLAGS) -o $@ $^

# règle générale pour la génération des .o
# $(LIST) dépend de fonctions.o et main.o, qui seront donc exécutés 
# via cette règle en premier lieu
%.o : %.c
# la génération des fichiers .o dépend de fichiers .c 
# (aucune cible ne correspondant à ces derniers, l'instruction est exécutée)
# $< correspond à chaque dépendance prise les unes à la suite des autres 
	$(CC) $(CFLAGS) -o $@ -c $<

run_exercice1 : $(TAB)
	./$(TAB)

run_exercice2 : $(LIST)
	./$(LIST)

memoire_exercice1 : $(TAB)
	valgrind ./$(TAB)

memoire_exercice2 : $(LIST)
	valgrind ./$(LIST)

# règle de nettoyage (supprimant les fichiers .o), ne dépendant d'aucune autre règle
clean : 
	rm *.o  $(LIST) $(TAB)

