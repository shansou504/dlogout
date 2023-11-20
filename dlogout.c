#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>
#include <stdlib.h>

static void
check_escape(GtkWidget *widget,
	GdkEventKey *event,
	gpointer data)
{
  if (event->keyval == GDK_KEY_Escape) {
		system("pkill -f dlogout &");
  }
}

static void
action (GtkListBox *listbox)
{
	GtkListBoxRow *listboxrow = gtk_list_box_get_selected_row(listbox);
	switch (gtk_list_box_row_get_index(listboxrow)) {
		case 0:
			system("slock &");
			system("xset dpms force off &");
			system("pkill -f dlogout &");
			break;
		case 1:
			system("pkill -f dwm &");
			system("pkill -f dlogout &");
			break;
		case 2:
			system("slock &");
			system("systemctl suspend &");
			system("pkill -f dlogout &");
			break;
		case 3:
			system("slock &");
			system("systemctl hibernate &");
			system("pkill -f dlogout &");
			break;
		case 4:
			system("systemctl reboot");
			break;
		case 5:
			system("systemctl poweroff");
			break;
		default:
			system("pkill -f dlogout &");
	} 
}

static void
activate (GtkApplication *app,
	gpointer        user_data)
{
	gint w = 80;
	gint h = 80;
	GtkWidget *window;
	window = gtk_application_window_new (app);
	gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
	gtk_window_set_default_size (GTK_WINDOW (window), w, h);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window), TRUE);
	gtk_window_set_gravity (GTK_WINDOW (window), GDK_GRAVITY_NORTH_EAST);
	g_signal_connect(window, "key_press_event", G_CALLBACK(check_escape), NULL);

	GdkDisplay *display;
	display = gdk_display_get_default();
	GdkMonitor *monitor;
	monitor = gdk_display_get_primary_monitor(display);
	GdkRectangle geometry;
	gdk_monitor_get_geometry (monitor, &geometry); 
	gint a,b,x,y;
	gtk_window_get_position (GTK_WINDOW (window), &x, &y);
	gtk_window_move (GTK_WINDOW (window), geometry.width - w, 0);
	
	GtkWidget *listbox;
	listbox = gtk_list_box_new ();
	gtk_container_add (GTK_CONTAINER (window), listbox);
	gtk_list_box_set_selection_mode (GTK_LIST_BOX(listbox), GTK_SELECTION_SINGLE);
	
	GtkWidget *rowlock = gtk_list_box_row_new();
	GtkWidget *labellock = gtk_label_new("Lock");
	gtk_container_add (GTK_CONTAINER (rowlock), labellock);
	gtk_container_add (GTK_CONTAINER (listbox), rowlock);
	gtk_label_set_xalign (GTK_LABEL(labellock), 0);
	
	GtkWidget *rowlogout = gtk_list_box_row_new();
	GtkWidget *labellogout = gtk_label_new("Logout");
	gtk_container_add (GTK_CONTAINER (rowlogout), labellogout);
	gtk_container_add (GTK_CONTAINER (listbox), rowlogout);
	gtk_label_set_xalign (GTK_LABEL(labellogout), 0);

	GtkWidget *rowsleep = gtk_list_box_row_new();
	GtkWidget *labelsleep = gtk_label_new("Sleep");
	gtk_container_add (GTK_CONTAINER (rowsleep), labelsleep);
	gtk_container_add (GTK_CONTAINER (listbox), rowsleep);
	gtk_label_set_xalign (GTK_LABEL(labelsleep), 0);
	
	GtkWidget *rowhibernate = gtk_list_box_row_new();
	GtkWidget *labelhibernate = gtk_label_new("Hibernate");
	gtk_container_add (GTK_CONTAINER (rowhibernate), labelhibernate);
	gtk_container_add (GTK_CONTAINER (listbox), rowhibernate);
	gtk_label_set_xalign (GTK_LABEL(labelhibernate), 0);
	
	GtkWidget *rowreboot = gtk_list_box_row_new();
	gtk_container_add (GTK_CONTAINER (listbox), rowreboot);
	GtkWidget *labelreboot = gtk_label_new("Reboot");
	gtk_container_add (GTK_CONTAINER (rowreboot), labelreboot);
	gtk_label_set_xalign (GTK_LABEL(labelreboot), 0);
	
	GtkWidget *rowshutdown = gtk_list_box_row_new();
	GtkWidget *labelshutdown = gtk_label_new("Shutdown");
	gtk_container_add (GTK_CONTAINER (rowshutdown), labelshutdown);
	gtk_container_add (GTK_CONTAINER (listbox), rowshutdown);
	gtk_label_set_xalign (GTK_LABEL(labelshutdown), 0);
	
	g_signal_connect (listbox, "row-activated", G_CALLBACK (action), listbox);
	
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
