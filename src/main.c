#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void
run_mc_cracked (GtkWidget *widget,
               gpointer  data)
  {
    system("screen -dmS mc2 portablemc start --username=mcos");
    printf("Running Minecraft Cracked Thank you PortableMC");
}
void 
server_config_ui (GtkWidget *widget, 
              gpointer data) 
        {
          system("screen -dmS gnom gnome-calculator");
        }
static void
run_mc (GtkWidget *widget,
             gpointer   data)
{
   system("screen -dmS mc minecraft-launcher");
   printf("Running Minecraft Launcher");

}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button1;
  GtkWidget *grid;
  GtkWidget *fixed;
  GtkWidget *box;
  GtkWidget *center_box;
  GtkWidget *center_box_vert;
  GtkWidget *label;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "mclaunch");

  /* Horizontal Box */
 center_box = gtk_center_box_new ();

  /* Vertical Box */
  center_box_vert = gtk_center_box_new ();
  gtk_orientable_set_orientation(GTK_CENTER_BOX (center_box_vert), GTK_ORIENTATION_VERTICAL);

 /* Initialize Grid */
  grid = gtk_grid_new ();
  /* Make the Vertical Grid the Owner of the Windo */
  gtk_window_set_child (GTK_WINDOW (window), center_box_vert);
  /* idk what this does but the documentation says it */
  fixed = gtk_fixed_new();
  /* Put the button into the center of the horizontal grid */
  gtk_center_box_set_center_widget(GTK_CENTER_BOX (center_box), grid);
  /* Attach Vert Grid to Horz Grid/ Put the Horizontal grid into the center of the vertical grid(which owns the window) */
  gtk_center_box_set_center_widget(GTK_CENTER_BOX (center_box_vert), center_box);


  /* Launch Button MCJAVA */
   button = gtk_button_new_with_label ("Launch MC Java");
   g_signal_connect (button, "clicked", G_CALLBACK (run_mc), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 3, 1);

  /* Window Size */
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 600);
  gtk_window_present (GTK_WINDOW (window));

  /* Quit Button */
  button1 = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button1, "clicked", G_CALLBACK (gtk_window_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button1, 0, 4, 3, 1);
  
 /* Cracked */  
 button = gtk_button_new_with_label ("Cracked Launcher plz don't tell mojang");
 g_signal_connect_swapped (button, "clicked", G_CALLBACK (run_mc_cracked), NULL);
 gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 3, 1);

/* Start Server */
 button = gtk_button_new_with_label ("Server Configurator");
 g_signal_connect_swapped (button, "clicked", G_CALLBACK (server_config_ui), NULL);
 gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 3, 1);

 /* Show This Window */
  gtk_widget_show (window);
  /* gtk_widget_show(box); */

  gtk_grid_set_row_spacing (GTK_GRID (grid), 12);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

