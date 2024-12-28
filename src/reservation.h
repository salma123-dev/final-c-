#ifndef RESERVATION_H_INCLUDED
#define RESERVATION_H_INCLUDED
#define FILE_RESERVATION "reservation.txt"
#include <stdio.h>
#include <gtk/gtk.h>
typedef struct {
    int id;
    char nom[100];
    int capacite;
    int places_disponibles;
} parking;
typedef struct {
    char nom[50];
    char prenom[50];
    char cin[20];
    char num_telephone[20];
} client_info_t;
typedef struct {
    int jour;
    int mois;
    int annee;
} date_reservation_t;
typedef struct {
    client_info_t client_info;
    char nom_parking[100];
    int id;
    date_reservation_t date_reservation;
} reservation;
// Déclaration des fonctions
int ajouter_reservation(char *file, reservation r);

reservation chercher_for_modif(char* file, int id_tester); 
int modifier_reservation(char*file ,int id1, reservation nouv) ; // Modifie une réservation
int supprimer_reservation(char *file, int id);
void afficher_reservation(GtkWidget *tree_view);
void afficher_parkings(GtkWidget *tree_view);
void trier(parking p[], int count);
#endif
