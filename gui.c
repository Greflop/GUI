#include <stdlib.h>
#include <gtk/gtk.h>
 
void OnQuitter(GtkWidget* widget, gpointer data);
void OnAbout(GtkWidget* widget, gpointer data);
void quitter(GtkWidget *widget); void creer_file_selection();
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection);
 
int main(int argc, char **argv)
{
    GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pMenuBar;
    GtkWidget *pMenu;
    GtkWidget *pMenuItem;
    GtkWidget *bouton_ouvrir;
 
    gtk_init(&argc, &argv);
 
    /* Création de la fenêtre */
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "GtkMenu");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 
    /* Création de la GtkVBox */
    pVBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
 
    /**** Création du menu ****/
 
    /* ETAPE 1 */
    pMenuBar = gtk_menu_bar_new();
    /** Premier sous-menu **/
    /* ETAPE 2 */
    pMenu = gtk_menu_new();
    /* ETAPE 3 */
    pMenuItem = gtk_menu_item_new_with_label("Nouveau");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
 
    bouton_ouvrir = gtk_menu_item_new_with_label("Ouvrir");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), bouton_ouvrir);
    g_signal_connect(G_OBJECT(bouton_ouvrir), "activate", G_CALLBACK(creer_file_selection), NULL);

    pMenuItem = gtk_menu_item_new_with_label("Enregistrer");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
 
    pMenuItem = gtk_menu_item_new_with_label("Fermer");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
 
    pMenuItem = gtk_menu_item_new_with_label("Quitter");
    g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnQuitter),(GtkWidget*) pWindow);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
    /* ETAPE 4 */
    pMenuItem = gtk_menu_item_new_with_label("Fichier");
    /* ETAPE 5 */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
    /* ETAPE 6 */
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);
 
    /** Second sous-menu **/
    /* ETAPE 2 */
    pMenu = gtk_menu_new();
    /* ETAPE 3 */
    pMenuItem = gtk_menu_item_new_with_label("A propos de...");
    g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnAbout),(GtkWidget*) pWindow);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
    /* ETAPE 4 */
    pMenuItem = gtk_menu_item_new_with_label("?");
    /* ETAPE 5 */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
    /* ETAPE 6 */
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);
 
    /* Ajout du menu a la fenetre */
    gtk_box_pack_start(GTK_BOX(pVBox), pMenuBar, FALSE, FALSE, 0);
 
    gtk_widget_show_all(pWindow);
 
    gtk_main();
 
    return EXIT_SUCCESS;
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
    //GtkWidget *dialog;
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

    //gtk_dialog_run(GTK_DIALOG(dialog));
    //gtk_widget_destroy(dialog);
    gtk_widget_destroy(file_selection);
}
 
void OnQuitter(GtkWidget* widget, gpointer data)
{
    GtkWidget *pQuestion;
 
    pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez vous vraiment\n"
        "quitter le programme?");
 
    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_YES:
            gtk_main_quit();
            break;
        case GTK_RESPONSE_NONE:
        case GTK_RESPONSE_NO:
            gtk_widget_destroy(pQuestion);
            break;
    }
}
 
void OnAbout(GtkWidget* widget, gpointer data)
{
    GtkWidget *pAbout;
 
    pAbout = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Cours GTK+ 2.0\n"
        "http://gtk.developpez.com");
 
    gtk_dialog_run(GTK_DIALOG(pAbout));
 
    gtk_widget_destroy(pAbout);
}

