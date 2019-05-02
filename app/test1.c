#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static GtkWidget *number1;
static GtkWidget *number2;
static GtkWidget *result;

/*calculate bmi from print_bmi*/
void do_calculate(GtkWidget *calculate, gpointer data) {
    float num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(number1)));
    float num2 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(number2)));
    float ans = num1/(num2/100*num2/100);
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "result: %.2f", ans);

    gtk_label_set_text(GTK_LABEL(result), buffer);
}


static void print_bmi(int argc, char **argv) {
    GtkWidget *window, *grid, *calculate;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title (GTK_WINDOW (window), "Fit Jung Loey");

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    result = gtk_label_new("weight:");
    gtk_grid_attach(GTK_GRID(grid), result, 0, 0, 1, 1);
    number1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), number1, 1, 0, 1, 1);
    result = gtk_label_new("kg.");
    gtk_grid_attach(GTK_GRID(grid), result, 2, 0, 1, 1);

    result = gtk_label_new("height:");
    gtk_grid_attach(GTK_GRID(grid), result, 0, 1, 1, 1);
    number2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), number2, 1, 1, 1, 1);
    result = gtk_label_new("cm.");
    gtk_grid_attach(GTK_GRID(grid), result, 2, 1, 1, 1);

    calculate = gtk_button_new_with_label("calculate");
    g_signal_connect(calculate, "clicked", G_CALLBACK(do_calculate), NULL);
    gtk_grid_attach(GTK_GRID(grid), calculate, 1, 3, 1, 1);

    result = gtk_label_new("result:");
    gtk_grid_attach(GTK_GRID(grid), result, 1, 5, 1, 1);
    gtk_widget_set_size_request(GTK_WIDGET(window),500,500);
    gtk_container_set_border_width (GTK_CONTAINER (window), 200);
    gtk_widget_show_all(window);
    gtk_main();

}

static void print_work(GtkWidget *widget,gpointer data){

  GtkWidget *window, *image, *button,*grid;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window), 5);
  gtk_window_set_title (GTK_WINDOW (window), "Fit Jung Loey");

  grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), grid);

  image = gtk_image_new_from_file("2.png");
  gtk_container_add (GTK_CONTAINER (window), image);
  gtk_grid_attach (GTK_GRID (grid), image, 2, 0, 1, 1);
  gtk_widget_show_all(window);
  gtk_main();
}


static void print_hello (GtkWidget *widget,gpointer data){
    GtkWidget *window;
    GtkWidget *child, *child2;
    GtkWidget *grid, *button;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Fit Jung Loey");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new ();
    gtk_container_add (GTK_CONTAINER (window), grid);
    child = gtk_image_new_from_file("1.jpg");
    gtk_container_add (GTK_CONTAINER (window), child);
    gtk_grid_attach (GTK_GRID (grid), child, 0, 1, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();
}


static void activate (GtkApplication *app,gpointer user_data){
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button,*image;
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, "theme.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Fit Jung Loey");
  gtk_container_set_border_width (GTK_CONTAINER (window), 200);

  grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), grid);

  image = gtk_image_new_from_file("images.jpeg");
  gtk_container_add (GTK_CONTAINER (window), image);
  gtk_grid_attach (GTK_GRID (grid), image, 2, 0, 2, 4);
  gtk_widget_set_size_request(image, 300, 300);


  button = gtk_button_new_with_label ("BMI      ");
  g_signal_connect (button, "clicked", G_CALLBACK (print_bmi), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("WORKOUT");
  g_signal_connect (button, "clicked", G_CALLBACK (print_work), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);


  button = gtk_button_new_with_label ("FOOD MENU");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 1, 1);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 1, 1);
  gtk_widget_set_size_request(GTK_WIDGET(window),500,500);
  gtk_widget_show_all (window);

}

int main (int argc,char **argv){
  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

