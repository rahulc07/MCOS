#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void
run_mc_cracked (GtkWidget *widget,
               gpointer  data)
  {
    system("xterm -e /bin/sh -c 'portablemc start --username=mcos'");
    printf("Running Minecraft Cracked Thank you PortableMC");
}
void
run_mc (GtkWidget *widget,
             gpointer   data)
{
   system("screen -dmS mc minecraft-launcher");
   printf("Running Minecraft Launcher \n");

}
void 
run_htop (GtkWidget *widget,
           gpointer data)
{
  system("xterm -e /bin/sh -c 'htop' ");
  printf("Running HTOP \n");
}  
void 
run_tui (GtkWidget *widget,
           gpointer data)
{
  system("xterm -e /bin/sh -c 'nmtui' ");
  printf("Running NMTUI \n");
}
void halt_system (GtkWidget *widget, gpointer data)
  {
    system("savewarn");
  } 
void save (GtkWidget *widget, gpointer data) {
  system("xterm -e /bin/sh -c 'syssave' ");
}
void run_performance_inject (GtkWidget *widget, gpointer data)
  {
    system("xterm -e /bin/sh -c 'performance-inject' ");
  } 
        

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *grid;
  GtkWidget *gridtr;
  GtkWidget *gridtl;
  GtkWidget *center_box;
  GtkWidget *center_box_vert;
  GtkWidget *center_box_tr;
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "mclaunch");

  /* Horizontal Box */
 center_box = gtk_center_box_new ();
 /* Top Right Horizontal Box */
 center_box_tr = gtk_center_box_new ();
 /* Top Left */

  /* Vertical Box */
  center_box_vert = gtk_center_box_new ();
  gtk_orientable_set_orientation(GTK_CENTER_BOX (center_box_vert), GTK_ORIENTATION_VERTICAL);

 /* Initialize Grid(Mid-Center) */
  grid = gtk_grid_new ();
 /* Initialize Grid (Top Right) */
  gridtr = gtk_grid_new();
  /* Initialze Grid (Top Left)  */
  gridtl = gtk_grid_new();
  
  gtk_widget_set_margin_top(GTK_GRID (gridtl), 5);
  gtk_widget_set_margin_start(GTK_GRID (gridtl), 10);

  gtk_widget_set_margin_top(GTK_GRID (gridtr), 5);
  gtk_widget_set_margin_end(GTK_GRID (gridtr), 10);
  /* Make the Vertical Grid the Owner of the Window */
  gtk_window_set_child (GTK_WINDOW (window), center_box_vert);
  /* Put the main buttons into the center of the horizontal grid */
  gtk_center_box_set_center_widget(GTK_CENTER_BOX (center_box), grid);
  /* Put the TR buttons into the right of the horizontal grid (center_box_tr)*/
  gtk_center_box_set_end_widget(GTK_CENTER_BOX (center_box_tr), gridtr);
  /* Weird but the Top Right Center box is the center box for the entire top, so attaching the top left buttons on the top left of the center box */
  gtk_center_box_set_start_widget(GTK_CENTER_BOX (center_box_tr), gridtl);
  /* Put the Horizontal grid into the center of the vertical grid(which owns the window) */
  gtk_center_box_set_center_widget(GTK_CENTER_BOX (center_box_vert), center_box);
  /* Put the 'Top Right Grid' on the 'Top' of the Vertical Grid */
  gtk_center_box_set_start_widget(GTK_CENTER_BOX (center_box_vert), center_box_tr);

  /* Launch Button MCJAVA */
   button = gtk_button_new_with_label ("Launch MC Java");
   g_signal_connect (button, "clicked", G_CALLBACK (run_mc), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 3, 1);

  /* Window Size */
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 600);
  gtk_window_present (GTK_WINDOW (window));

  /* Quit Button */
  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (halt_system), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 3, 1);
  
 /* Cracked */  
 button = gtk_button_new_with_label ("Cracked Launcher (via PortableMC)");
 g_signal_connect_swapped (button, "clicked", G_CALLBACK (run_mc_cracked), NULL);
 gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 3, 1);

 /* Performance Injectors */
 button = gtk_button_new_with_label ("Performance Injectors");
 g_signal_connect_swapped (button, "clicked", G_CALLBACK (run_performance_inject), NULL);
 gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 3, 1); 

/* Starting TR Widgets */
/* Wifi */
button = gtk_button_new_with_label ("");
g_signal_connect_swapped (button, "clicked", G_CALLBACK (run_tui), NULL);
gtk_grid_attach (GTK_GRID (gridtr), button, 0, 1, 1, 1);
/* System Monitor */
button = gtk_button_new_with_label ("");
g_signal_connect_swapped (button, "clicked", G_CALLBACK (run_htop), NULL);
gtk_grid_attach (GTK_GRID (gridtr), button, 1, 1, 1, 1);

/* Starting top left widgets */
button = gtk_button_new_with_label ("");
g_signal_connect_swapped (button, "clicked", G_CALLBACK (save), NULL);
gtk_grid_attach (GTK_GRID (gridtl), button, 0, 0, 1, 1);

 /* Show This Window */
  gtk_widget_show (window);
  /* gtk_widget_show(box); */

  gtk_grid_set_row_spacing (GTK_GRID (grid), 12);
  gtk_grid_set_row_spacing (GTK_GRID (gridtr), 12);
  gtk_grid_set_column_spacing (GTK_GRID (gridtr), 6);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.mcos.mcstarter", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

