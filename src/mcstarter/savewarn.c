#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void run_shutdown(GtkWidget *widget, gpointer data) {
    system("sudo shutdown -P -h now");
}
void cancel(GtkWidget *widget, gpointer data) {
    GtkWidget *window = data;
    gtk_window_destroy(GTK_WINDOW (window));
}
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *button;
    GtkWidget *text;
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *center_box_vert;
    GtkWidget *label;

    window = gtk_application_window_new(app);
    gtk_window_set_title (GTK_WINDOW (window), "warn");
    grid = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_homogeneous(GTK_BOX (grid), TRUE);
    center_box_vert = gtk_center_box_new ();
    gtk_orientable_set_orientation(GTK_CENTER_BOX (center_box_vert), GTK_ORIENTATION_VERTICAL);
    gtk_window_set_child (GTK_WINDOW (window), center_box_vert);
    gtk_center_box_set_end_widget(GTK_CENTER_BOX (center_box_vert), grid);
    /* Window Size */
    gtk_window_set_default_size (GTK_WINDOW (window), 100, 100);
    gtk_window_present (GTK_WINDOW (window));
   /* Okay Button */
   button = gtk_button_new_with_label ("Shutdown");
   g_signal_connect (button, "clicked", G_CALLBACK (run_shutdown), NULL);
   gtk_box_append (GTK_BOX (grid), button);
   /* Quit Button */
   button = gtk_button_new_with_label ("Cancel");
   g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window) ;
   gtk_box_append (GTK_BOX (grid), button);
   /* Label */
   label = gtk_label_new ("   Warning all UNSAVED data will be wiped on reboot (this includes .minecraft).\n If you want to save go back NOW and click the save button in the top right   ");
   gtk_center_box_set_start_widget (GTK_CENTER_BOX (center_box_vert), label);
   gtk_widget_set_margin_top(GTK_LABEL (label), 10);


}
int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.warning", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}