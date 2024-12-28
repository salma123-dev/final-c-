// reservation.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"
#include <gtk/gtk.h>
#define FILE_RESERVATION "reservation.txt"
#define FILE_ID "id.txt"

int ajouter_reservation(char *file, reservation r) {
    FILE *f = fopen(file, "a");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    fprintf(f, "%s %s %s %s %s %d %d %d %d\n",
            r.client_info.nom, r.client_info.prenom, r.client_info.cin, r.nom_parking,
            r.client_info.num_telephone, r.id, r.date_reservation.jour,
            r.date_reservation.mois, r.date_reservation.annee);
    fclose(f);
    return 1;
}

int supprimer_reservation(char *file, int id) {
    FILE *f = fopen(file, "r");
    FILE *f2 = fopen("temp.txt", "w");  // Créer un fichier temporaire pour sauvegarder les autres réservations
    int result = 0;  // Variable pour vérifier si une réservation a été supprimée

    if (f != NULL && f2 != NULL) {
        reservation r;
        // Utilisation du format approprié pour lire les champs
        while (fscanf(f, "%s %s %s %s %s %d %d %d %d\n",
                       r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                       r.nom_parking, r.client_info.num_telephone, &r.id,
                       &r.date_reservation.jour, &r.date_reservation.mois,
                       &r.date_reservation.annee) != EOF) {
            if (r.id != id) {
                // Si l'ID ne correspond pas, on garde la réservation dans le fichier temporaire
                fprintf(f2, "%s %s %s %s %s %d %d %d %d\n",
                        r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                        r.nom_parking, r.client_info.num_telephone, r.id,
                        r.date_reservation.jour, r.date_reservation.mois,
                        r.date_reservation.annee);
            } else {
                result = 1;  // Réservation trouvée et supprimée
            }
        }
        fclose(f);
        fclose(f2);

        if (result) {
            remove(FILE_RESERVATION);  
            rename("temp.txt", FILE_RESERVATION); 
        } else {
            remove("temp.txt"); // Supprime le fichier temporaire si aucune réservation n'a été supprimée
        }

        return result;
    } else {
        if (f != NULL) fclose(f);
        if (f2 != NULL) fclose(f2);
        return 0; 
    }
}
reservation chercher_for_modif(char*file ,int id) {
    reservation r;
    FILE *f = fopen(file, "r");

    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %s %d %d %d %d\n",
                       r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                       r.nom_parking, r.client_info.num_telephone, &r.id,
                       &r.date_reservation.jour, &r.date_reservation.mois,
                       &r.date_reservation.annee) != EOF) {
            if (r.id == id) {
                fclose(f);
                return r;
            }
        }
        fclose(f);
    }

    r.id = -1;  // Retourne une réservation avec un ID invalide si non trouvé
    return r;
}

int modifier_reservation(char*file ,int id1, reservation nouv) {
    int tr = 0;
    reservation r;
    FILE *f = fopen(file, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s %s %d %d %d %d\n",
                       r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                       r.nom_parking, r.client_info.num_telephone, &r.id,
                       &r.date_reservation.jour, &r.date_reservation.mois,
                       &r.date_reservation.annee) != EOF) {
            if (r.id == id1) {
                fprintf(f2, "%s %s %s %s %s %d %d %d %d\n",
                        nouv.client_info.nom, nouv.client_info.prenom, nouv.client_info.cin,
                        nouv.nom_parking, nouv.client_info.num_telephone, nouv.id,
                        nouv.date_reservation.jour, nouv.date_reservation.mois,
                        nouv.date_reservation.annee);
                tr = 1;
            } else {
                fprintf(f2, "%s %s %s %s %s %d %d %d %d\n",
                        r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                        r.nom_parking, r.client_info.num_telephone, r.id,
                        r.date_reservation.jour, r.date_reservation.mois,
                        r.date_reservation.annee);
            }
        }
        fclose(f);
        fclose(f2);
        remove(FILE_RESERVATION);
        rename("nouv.txt", FILE_RESERVATION);
    }
    return tr;
}





void afficher_reservation(GtkWidget *tree_view){
gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), NULL);
    GtkListStore *store = gtk_list_store_new(9,
					        
                                             G_TYPE_STRING, 
                                             G_TYPE_STRING, 
                                             G_TYPE_STRING, 
                                             G_TYPE_STRING, 
                                             G_TYPE_STRING, 
                                             G_TYPE_INT,
					     G_TYPE_INT,
                                             G_TYPE_INT,
					     G_TYPE_INT);  
FILE *file = fopen("reservation.txt", "r"); 
if (!file) {
        g_printerr("Erreur : Impossible d'ouvrir le fichier\n");
        return;
    }
    reservation r ;
    char line[1024];
    int count = 0;
while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        int n = sscanf(line, "%s %s %s %s %s %d %d %d %d", 
            r.client_info.nom, r.client_info.prenom, r.client_info.cin,r.nom_parking,r.client_info.num_telephone,    &r.id ,&r.date_reservation.jour,&r.date_reservation.mois,&r.date_reservation.annee );
if (n == 9) {
            GtkTreeIter iter;
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, r.client_info.nom,
                               1, r.client_info.prenom,
                               2, r.client_info.cin,
                               3, r.nom_parking,
                               4, r.client_info.num_telephone,
                               5, r.id ,
                               6, r.date_reservation.jour,
                               7, r.date_reservation.mois,
                               8, r.date_reservation.annee,
                               -1);
count++;
        } else {
            g_printerr("Erreur de format dans une ligne du fichier : %s\n", line);
        }
    }
    fclose(file);
if (count == 0) {
        g_print("Aucune reservation trouvé dans le fichier.\n");
    } else {
        g_print("%d reservation(s) chargé(s) depuis le fichier.\n", count);
    }
if (g_list_length(gtk_tree_view_get_columns(GTK_TREE_VIEW(tree_view))) == 0) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("NOM", renderer, "text", 0, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("PRENOM", renderer, "text", 1, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 2, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("NOM_PARKING", renderer, "text", 3, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("TELEPHONE", renderer, "text", 4, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("ID RESERVATION", renderer, "text", 5, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("JOUR", renderer, "text", 6, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("MOIS", renderer, "text", 7, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("ANNEE", renderer, "text", 8, NULL));
       
    }
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(store));

    // Libérer le modèle
    g_object_unref(store);
}


/*
void trier(parking p[], int count) {
    parking temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            
            if (p[j].places_disponibles < p[j + 1].places_disponibles) {
              
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}*/
void afficher_parkings(GtkWidget *tree_view){
gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), NULL);
    GtkListStore *store = gtk_list_store_new(4,
					     G_TYPE_INT,   
                                             G_TYPE_STRING, 
                                             G_TYPE_INT,
                                             G_TYPE_INT
					     );  
FILE *file = fopen("parkingss.txt", "r"); 
if (!file) {
        g_printerr("Erreur : Impossible d'ouvrir le fichier\n");
        return;
    }
    parking p ;
    char line[1024];
    int count = 0;
while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        int n = sscanf(line, "%d %s %d %d ", 
            &p.id, p.nom,&p.capacite,&p.places_disponibles );
         
if (n == 4) {
            GtkTreeIter iter;
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, p.id,
                               1, p.nom,
                               2, p.capacite,
                               3, p.places_disponibles,
                              -1);
count++;
        } else {
            g_printerr("Erreur de format dans une ligne du fichier : %s\n", line);
        }
    }
    fclose(file);
if (count == 0) {
        g_print("Aucun parking trouvé dans le fichier.\n");
    } else {
        g_print("%d parking(s) chargé(s) depuis le fichier.\n", count);
    }
if (g_list_length(gtk_tree_view_get_columns(GTK_TREE_VIEW(tree_view))) == 0) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("NOM", renderer, "text", 1, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("CAPACITE", renderer, "text", 2, NULL));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),
                                    gtk_tree_view_column_new_with_attributes("PLACES_DISPONIBLE", renderer, "text", 3, NULL));
        
    }
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(store));

    // Libérer le modèle
    g_object_unref(store);
}

