#include <gtk/gtk.h>

#include "xas_spc.h"


void show_halt_question(GtkWidget *widget, gpointer window);
void show_reboot_question(GtkWidget *widget, gpointer window);
void show_help(GtkWidget *widget, gpointer window);

int main( int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *vbox;

  GtkWidget *halt;
  GtkWidget *reboot;
  GtkWidget *close;
  GtkWidget *help;
  GtkWidget *cancel;

  result = 0;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
  gtk_window_set_title(GTK_WINDOW(window), "XAS_EXIT: Shutdown or reboot host");
  gtk_container_set_border_width(GTK_CONTAINER(window), 5);

  vbox = gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  halt = gtk_button_new_with_label("Halt (apagar)");
  reboot = gtk_button_new_with_label("Reboot (reiniciar)");
  close = gtk_button_new_with_label("Close Window (pechar ventana)");
  help = gtk_button_new_with_label("Help (axuda)");
  cancel = gtk_button_new_with_label("Cancel");

  gtk_box_pack_start(GTK_BOX(vbox), halt, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), reboot, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), close, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), help, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), cancel, TRUE, TRUE, 0);

  g_signal_connect(G_OBJECT(halt), "clicked",
        G_CALLBACK(show_halt_question), (gpointer) window);

  g_signal_connect(G_OBJECT(reboot), "clicked",
        G_CALLBACK(show_reboot_question), (gpointer) window);

  g_signal_connect(G_OBJECT(close), "clicked",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  g_signal_connect(G_OBJECT(help), "clicked",
        G_CALLBACK(show_help), (gpointer) window);

  g_signal_connect(G_OBJECT(cancel), "clicked",
        G_CALLBACK(gtk_main_quit), (gpointer) window);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  gtk_widget_show_all(window);

  gtk_main();

  return result;
}

void show_halt_question(GtkWidget *widget, gpointer window)
{
  GtkWidget *dialog;

  dialog = gtk_message_dialog_new(window,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_YES_NO,
            "Are you sure to halt?");
  gtk_window_set_title(GTK_WINDOW(dialog), "Question");
  switch( gtk_dialog_run(GTK_DIALOG(dialog)) )
  {
      case GTK_RESPONSE_YES:
        result = execHalt();
        break;
      case GTK_RESPONSE_NO:
        break;
      default:
        break;
  }
  gtk_widget_destroy(dialog);
}


void show_reboot_question(GtkWidget *widget, gpointer window)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(window,
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_YES_NO,
            "Are you sure to reboot?");
  gtk_window_set_title(GTK_WINDOW(dialog), "Question");
  switch( gtk_dialog_run(GTK_DIALOG(dialog)) )
  {
      case GTK_RESPONSE_YES:
        result = execReboot();
        break;
      case GTK_RESPONSE_NO:

        break;
      default:
        break;
  }
  gtk_widget_destroy(dialog);
}

void show_help(GtkWidget *widget, gpointer data)
{
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("/usr/share/icons/XAS/xas_exit_logo.png", NULL);

  GtkWidget *dialog = gtk_about_dialog_new();
  gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "XAS_EXIT");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "1.0");
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),
      "© J. Breogán L. Costa: Software Engineering and development\n jlcosta@correo.ei.uvigo.es\nJavier Rodeiro Iglesias, Ph.D: Direction and support");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),
     "xas_exit is part of XAS (XAS ADR \nat sourceforge), designed to and at ESEI: \nhttp://esei.uvigo.es");
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),
      "Help and more info at http://sourceforge.net");
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
  g_object_unref(pixbuf), pixbuf = NULL;
  gtk_dialog_run(GTK_DIALOG (dialog));
  gtk_widget_destroy(dialog);

}
