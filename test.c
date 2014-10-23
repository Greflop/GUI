#include <stdlib.h>
#include <gtk/gtk.h>
 
void quitter(GtkWidget *widget); void creer_file_selection();
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection);
 
int main(int argc,char* argv[])
{
    GtkWidget *win;
    GtkWidget *bouton_explorer;
     
    gtk_init(&argc,&argv);
     
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win),"GtkFileSelection");
    gtk_window_set_default_size(GTK_WINDOW(win),320,200);
     
    // On crée un bouton explorer
    bouton_explorer=gtk_button_new_with_mnemonic("_Explorer...");
    // on met bouton_explorer dans win
    gtk_container_add(GTK_CONTAINER(win),bouton_explorer);
     
    g_signal_connect(G_OBJECT(win),"destroy",G_CALLBACK(quitter), NULL);
    g_signal_connect(G_OBJECT(bouton_explorer), "clicked", G_CALLBACK(creer_file_selection), NULL);
     
    // affichage de win et de ce qu'il contient
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
 
void quitter(GtkWidget* widget)
{
    // destruction de win et de tout ce qu'il contient
    gtk_widget_destroy(widget);
    gtk_main_quit();
}
 
void creer_file_selection()
{
    GtkWidget *selection;
     
    selection = gtk_file_selection_new( g_locale_to_utf8( "Sélectionnez un fichier", -1, NULL, NULL, NULL) );
    gtk_widget_show(selection);
     
    //On interdit l'utilisation des autres fenêtres.
    gtk_window_set_modal(GTK_WINDOW(selection), TRUE);
     
    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(recuperer_chemin), selection );
     
    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}
 
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection)
{
    const gchar* chemin;
    GtkWidget *dialog;
    chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );
     
    /*dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection),
    GTK_DIALOG_MODAL,
    GTK_MESSAGE_INFO,
    GTK_BUTTONS_OK,
    "Vous avez choisi :\n%s", chemin);*/
    GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pImage;
    GtkWidget *pQuitImage;
    GtkWidget *pQuitBtn;
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
    gtk_window_set_title(GTK_WINDOW(pWindow), "GtkImage");
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 
    pVBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
 
    /* Chargement d'une image a partir d'un fichier */
    pImage = gtk_image_new_from_file(chemin);
    gtk_box_pack_start(GTK_BOX(pVBox), pImage, FALSE, FALSE, 5);
 
    pQuitBtn = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(pVBox), pQuitBtn, TRUE, FALSE, 5);
    g_signal_connect(G_OBJECT(pQuitBtn), "clicked", G_CALLBACK(gtk_main_quit), NULL);
 
    /* Chargement d'une image a partir d'un GtkStockItem */
    pQuitImage = gtk_image_new_from_stock(GTK_STOCK_QUIT, GTK_ICON_SIZE_LARGE_TOOLBAR);
    gtk_container_add(GTK_CONTAINER(pQuitBtn), pQuitImage);
 
    gtk_widget_show_all(pWindow);
     
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_widget_destroy(file_selection);
}

