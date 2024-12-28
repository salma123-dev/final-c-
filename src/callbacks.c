#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "reservation.h"
void
on_button_ajouter_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *nom, *prenom, *cin, *telephone, *combobox1,  *label71 ,*label51 , *jour , *mois , *annee , *label72;
    char msg[50] = "";  
    int a ,t ;
    reservation r; 
nom = lookup_widget((GtkWidget *)button, "nom");
prenom = lookup_widget((GtkWidget *)button, "prenom");
cin = lookup_widget((GtkWidget *)button, "cin");
telephone = lookup_widget((GtkWidget *)button, "telephone");
combobox1 = lookup_widget((GtkWidget *)button, "combobox1");
mois = lookup_widget((GtkWidget *)button, "mois");
label71 = lookup_widget((GtkWidget *)button, "label71");
jour = lookup_widget((GtkWidget *)button, "jour");
annee = lookup_widget((GtkWidget *)button, "annee");

strcpy(r.client_info.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(r.client_info.prenom, gtk_entry_get_text(GTK_ENTRY(prenom)));
strcpy(r.client_info.cin, gtk_entry_get_text(GTK_ENTRY(cin)));
strcpy(r.client_info.num_telephone, gtk_entry_get_text(GTK_ENTRY(telephone)));
r.date_reservation.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
r.date_reservation.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
r.date_reservation.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
	char id_text[50];    
    	r.id = rand() % 10000 + 1;
   	 sprintf(id_text, "%d", r.id);
   	 label51 = lookup_widget((GtkWidget *)button, "label51");
   	 gtk_label_set_text(GTK_LABEL(label51),id_text);
	
const gchar *selected_text_combobox1 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1));
if (selected_text_combobox1 != NULL) {
    strcpy(r.nom_parking, selected_text_combobox1);
} else {
    strcpy(r.nom_parking, "Inconnu"); 
}

    		t=ajouter_reservation("reservation.txt",r);
    		if (t)
    			gtk_label_set_text(GTK_LABEL(label71), "votre réservation a été ajouté avec succés \nmerci pour votre confiance 🌟😊 ");
    		else     
			gtk_label_set_text(GTK_LABEL(label71), "echec !");

}






void
on_button_supprimer_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *id1, *label72;
    int result;
    reservation r;  
    
    id1 = lookup_widget(GTK_WIDGET(button), "id1");  
    label72 = lookup_widget(GTK_WIDGET(button), "label72");  
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(id1));  
    r.id = atoi(id_text); 
    if (r.id <= 0) {
        gtk_label_set_text(GTK_LABEL(label72), "ID invalide. Veuillez entrer un ID valide.");
        return;  
    }
    result = supprimer_reservation("reservation.txt", r.id);
    if (result) {
        gtk_label_set_text(GTK_LABEL(label72), "Réservation supprimée avec succès.");
   }else {
        gtk_label_set_text(GTK_LABEL(label72), "Erreur : Réservation introuvée avec cet ID.");
    }
}


void
on_buttonverif_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
char ch1[50], ch2[50];
    int id_tester;
    reservation r;
    
    // Recherche des widgets GTK
    GtkWidget *label190 = lookup_widget(GTK_WIDGET(button), "label190");
    GtkWidget *label200 = lookup_widget(GTK_WIDGET(button), "label200");
    GtkWidget *label210 = lookup_widget(GTK_WIDGET(button), "label210");
    GtkWidget *label220 = lookup_widget(GTK_WIDGET(button), "label220");
    GtkWidget *label230 = lookup_widget(GTK_WIDGET(button), "label230");
    GtkWidget *label240 = lookup_widget(GTK_WIDGET(button), "label240");
   /* GtkWidget *jour = lookup_widget(GTK_WIDGET(button), "jour");
    GtkWidget *mois = lookup_widget(GTK_WIDGET(button), "mois");
    GtkWidget *annee = lookup_widget(GTK_WIDGET(button), "annee");*/

    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button),"entry_id");
    GtkWidget *cin1 = lookup_widget(GTK_WIDGET(button),"cin1");
    GtkWidget *nom2 = lookup_widget(GTK_WIDGET(button),"nom2");
    GtkWidget *prenom1 = lookup_widget(GTK_WIDGET(button),"prenom1");
    GtkWidget *telephone1 = lookup_widget(GTK_WIDGET(button),"telephone1");
    GtkWidget *sannee1 = lookup_widget(GTK_WIDGET(button),"sannee1");
    GtkWidget *sjour1 = lookup_widget(GTK_WIDGET(button),"sjour1");
    GtkWidget *smois1 = lookup_widget(GTK_WIDGET(button),"smois1");
    GtkWidget *parking1 = lookup_widget(GTK_WIDGET(button),"parking1");
    GtkWidget *label270 = lookup_widget(GTK_WIDGET(button),"label270");

    // Récupération de l'ID du client
    id_tester = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
    // Recherche de la réservation avec l'ID donné
    reservation r_modif =chercher_for_modif("reservation.txt",id_tester)
;
    g_print("%d", r_modif.id);
    
    if (r_modif.id != id_tester) {
        
        gtk_label_set_text(GTK_LABEL(label270), "Erreur !! : id introuvable ");
        
        // Réinitialisation des champs d'information
        gtk_label_set_text(GTK_LABEL(label190), "");
        gtk_label_set_text(GTK_LABEL(label200), " ");
        gtk_label_set_text(GTK_LABEL(label210), "");
        gtk_label_set_text(GTK_LABEL(label220), "");
        gtk_label_set_text(GTK_LABEL(label230), " ");
        gtk_label_set_text(GTK_LABEL(label240), " ");
        
        // Masquer les champs pour la modification
        gtk_widget_set_visible(nom2, FALSE);
        gtk_widget_set_visible(prenom1, FALSE);
        gtk_widget_set_visible(cin1, FALSE);
        gtk_widget_set_visible(telephone1, FALSE);
        gtk_widget_set_visible(parking1, FALSE);
        gtk_widget_set_visible(sannee1, FALSE);
        gtk_widget_set_visible(sjour1, FALSE);
        gtk_widget_set_visible(smois1, FALSE);
    } else {
        // Si l'ID est trouvé, permettre la modification des informations
        gtk_label_set_text(GTK_LABEL(label270), "Veuillez modifier vos informations");
        
        // Affichage des champs de saisie pour la modification
        gtk_widget_set_visible(nom2, TRUE);
        gtk_widget_set_visible(prenom1, TRUE);
        gtk_widget_set_visible(cin1, TRUE);
        gtk_widget_set_visible(telephone1, TRUE);
        gtk_widget_set_visible(parking1, TRUE);
        gtk_widget_set_visible(sannee1, TRUE);
        gtk_widget_set_visible(sjour1, TRUE);
        gtk_widget_set_visible(smois1, TRUE);
	gtk_widget_set_visible(nom2, TRUE);

        // Mise à jour des labels
        gtk_label_set_text(GTK_LABEL(label190), "Nom");
        gtk_label_set_text(GTK_LABEL(label200), "Prénom");
        gtk_label_set_text(GTK_LABEL(label210), "CIN");
        gtk_label_set_text(GTK_LABEL(label220), "Nom Parking");
        gtk_label_set_text(GTK_LABEL(label230), "Téléphone");
        gtk_label_set_text(GTK_LABEL(label240), "Date de Réservation");
        /*gtk_label_set_text(GTK_LABEL(jour), "Jour");
        gtk_label_set_text(GTK_LABEL(mois), "Mois");
        gtk_label_set_text(GTK_LABEL(annee), "Année");*/

        // Pré-remplir les champs avec les informations existantes
        gtk_entry_set_text(GTK_ENTRY(nom2), r_modif.client_info.nom);
        gtk_entry_set_text(GTK_ENTRY(prenom1), r_modif.client_info.prenom);
        gtk_entry_set_text(GTK_ENTRY(cin1), r_modif.client_info.cin);
        gtk_entry_set_text(GTK_ENTRY(telephone1), r_modif.client_info.num_telephone);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(sannee1), r_modif.date_reservation.annee);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(sjour1), r_modif.date_reservation.jour);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(smois1), r_modif.date_reservation.mois);

        const gchar *selected_text_parking1 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(parking1));
        if (selected_text_parking1 != NULL) {
            strcpy(r.nom_parking, selected_text_parking1);
        } else {
            strcpy(r.nom_parking, "Inconnu");
        }
    }
}
void
on_button_modifier_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *label270 = lookup_widget(GTK_WIDGET(button), "label270");
    GtkWidget *label260 = lookup_widget(GTK_WIDGET(button), "label260");
    reservation r;
    int id_test;
    // Récupération des champs du formulaire
    GtkWidget *entry_id =lookup_widget(GTK_WIDGET(button), "entry_id");
    GtkWidget *nom2=lookup_widget(GTK_WIDGET(button), "nom2");
    GtkWidget *prenom1 =lookup_widget(GTK_WIDGET(button), "prenom1");
    GtkWidget *cin1 = lookup_widget(GTK_WIDGET(button), "cin1");
    GtkWidget *telephone1 = lookup_widget(GTK_WIDGET(button), "telephone1");
    GtkWidget *sannee1 = lookup_widget(GTK_WIDGET(button), "sannee1");
    GtkWidget *sjour1 = lookup_widget(GTK_WIDGET(button), "sjour1");
    GtkWidget *smois1 = lookup_widget(GTK_WIDGET(button), "smois1");
    GtkWidget *parking1 = lookup_widget(GTK_WIDGET(button), "parking1");

    // Récupération de l'ID de la réservation
    id_test = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));

    // Mise à jour des informations de la réservation
    strcpy(r.client_info.nom, gtk_entry_get_text(GTK_ENTRY(nom2)));
    strcpy(r.client_info.prenom, gtk_entry_get_text(GTK_ENTRY(prenom1)));
    strcpy(r.client_info.cin, gtk_entry_get_text(GTK_ENTRY(cin1)));
    strcpy(r.client_info.num_telephone, gtk_entry_get_text(GTK_ENTRY(telephone1)));
    r.date_reservation.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sjour1));
    r.date_reservation.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(sannee1));
    r.date_reservation.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(smois1));
    r.id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));

    // Récupérer le parking sélectionné
    const gchar *selected_text_parking1 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(parking1));
    if (selected_text_parking1 != NULL) {
        strcpy(r.nom_parking, selected_text_parking1);
    } else {
        strcpy(r.nom_parking, "Inconnu");
    }

    
    int a = modifier_reservation("reservation.txt",r.id,r);
    if (a) {
        gtk_label_set_text(GTK_LABEL(label260), "votre réservation a été ajouté avec succés \nmerci pour votre confiance 🌟😊");
    } else {
        gtk_label_set_text(GTK_LABEL(label260), "Échec de la modification !");
    }
}





void
on_AFFICHER_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
g_print("Le bouton AFFICHER a été cliqué.\n");
    GtkWidget *AFFICHER = GTK_WIDGET(button);
    GtkWidget *parent_window = gtk_widget_get_parent(AFFICHER);
    GtkWidget *tree_view = lookup_widget(parent_window, "treeview22");

    if (!tree_view) {
        g_print("Erreur : TreeView non trouvé.\n");
        return;
    }
    parking p ;
    afficher_parkings(tree_view);
}


void
on_actualisersalma_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
g_print("Le bouton Actualisersalma a été cliqué.\n");
    GtkWidget *actualisersalma = GTK_WIDGET(button);
    GtkWidget *parent_window = gtk_widget_get_parent(actualisersalma);
    GtkWidget *tree_view = lookup_widget(parent_window, "treeview11");

    if (!tree_view) {
        g_print("Erreur : TreeView non trouvé.\n");
        return;
    }
    afficher_reservation(tree_view);
}


void
on_retoursalma_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}

