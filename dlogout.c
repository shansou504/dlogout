#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <stdio.h>
#include <stdlib.h>

static void check_escape(GtkWidget *widget,	GdkEventKey *event,	gpointer data) {
  if (event->keyval == GDK_KEY_Escape) {
		system("pkill -f dlogout &");
  }
}

static void action (GtkListBox *listbox) {
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

static void activate (GtkApplication *app, gpointer user_data) {
	g_signal_connect(app, "activate", G_CALLBACK(g_application_quit), app);

	GtkWidget *window;
	window = gtk_application_window_new(app);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window), TRUE);
	gtk_window_set_gravity(GTK_WINDOW (window), GDK_GRAVITY_NORTH_EAST);
	g_signal_connect(window, "key_press_event", G_CALLBACK(check_escape), NULL);

	GdkDisplay *display;
	display = gdk_display_get_default();
	GdkMonitor *monitor;
	monitor = gdk_display_get_primary_monitor(display);
	GdkRectangle geometry;
	gdk_monitor_get_geometry(monitor, &geometry); 
	gtk_window_move(GTK_WINDOW(window), geometry.width, 0);
	
	GtkWidget *listbox;
	listbox = gtk_list_box_new();
	gtk_container_add(GTK_CONTAINER(window), listbox);
	gtk_list_box_set_selection_mode(GTK_LIST_BOX(listbox), GTK_SELECTION_SINGLE);
	g_signal_connect(listbox, "row-activated", G_CALLBACK(action), listbox);
	
	GtkWidget *row1 = gtk_list_box_row_new();
	GtkWidget *label1 = gtk_label_new("Lock");
	gtk_container_add(GTK_CONTAINER(row1),label1);
	gtk_container_add(GTK_CONTAINER(listbox), row1);
	gtk_label_set_xalign(GTK_LABEL(label1), 0);
	
	GtkWidget *row2 = gtk_list_box_row_new();
	GtkWidget *label2 = gtk_label_new("Log Out");
	gtk_container_add(GTK_CONTAINER(row2), label2);
	gtk_container_add(GTK_CONTAINER(listbox), row2);
	gtk_label_set_xalign(GTK_LABEL(label2), 0);

	GtkWidget *row3 = gtk_list_box_row_new();
	GtkWidget *label3 = gtk_label_new("Suspend");
	gtk_container_add(GTK_CONTAINER (row3), label3);
	gtk_container_add(GTK_CONTAINER (listbox), row3);
	gtk_label_set_xalign(GTK_LABEL(label3), 0);
	
	GtkWidget *row4 = gtk_list_box_row_new();
	GtkWidget *label4 = gtk_label_new("Hibernate");
	gtk_container_add(GTK_CONTAINER (row4), label4);
	gtk_container_add(GTK_CONTAINER (listbox), row4);
	gtk_label_set_xalign(GTK_LABEL(label4), 0);
	
	GtkWidget *row5 = gtk_list_box_row_new();
	gtk_container_add(GTK_CONTAINER (listbox), row5);
	GtkWidget *label5 = gtk_label_new("Reboot");
	gtk_container_add(GTK_CONTAINER (row5), label5);
	gtk_label_set_xalign(GTK_LABEL(label5), 0);
	
	GtkWidget *row6 = gtk_list_box_row_new();
	GtkWidget *label6 = gtk_label_new("Shutdown");
	gtk_container_add(GTK_CONTAINER(row6), label6);
	gtk_container_add(GTK_CONTAINER(listbox), row6);
	gtk_label_set_xalign(GTK_LABEL(label6), 0);
	
	gtk_widget_show_all(window);
}

int main (int argc,	char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("dlogout.shansou504.github", 0);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
