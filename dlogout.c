#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <stdlib.h>

static void
reboot (void) {
	system("systemctl reboot");
}

static void
shutdown (void) {
	system("systemctl poweroff");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  window = gtk_application_window_new (app);
	gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
	gtk_window_set_default_size (GTK_WINDOW (window), 80, 60);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window), TRUE);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);

  GtkWidget *button_box;
  button_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  GtkWidget *rebootbtn = gtk_button_new_with_label ("Reboot");
  g_signal_connect (rebootbtn, "clicked", G_CALLBACK (reboot), NULL);
  gtk_container_add (GTK_CONTAINER (button_box), rebootbtn);

  GtkWidget *shutdownbtn = gtk_button_new_with_label ("Shutdown");
  g_signal_connect (shutdownbtn, "clicked", G_CALLBACK (shutdown), NULL);
  gtk_container_add (GTK_CONTAINER (button_box), shutdownbtn);

  gtk_widget_show_all (window);

	g_signal_connect (app, "activate", G_CALLBACK (g_application_quit), app);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("dlogout.shansou504.github", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
