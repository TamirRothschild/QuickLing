#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    GtkWidget *input_entry;
    GtkWidget *output_entry;
    GtkWidget *lang_entry;
    GtkWidget *result_label;
} AppWidgets;

void on_input_file_clicked(GtkButton *button, AppWidgets *widgets) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Choose Input File",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "_Open",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        gtk_entry_set_text(GTK_ENTRY(widgets->input_entry), filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void on_output_file_clicked(GtkButton *button, AppWidgets *widgets) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Choose Output File",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "_Save",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        gtk_entry_set_text(GTK_ENTRY(widgets->output_entry), filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void on_translate_clicked(GtkButton *button, AppWidgets *widgets) {
    const char *input_file = gtk_entry_get_text(GTK_ENTRY(widgets->input_entry));
    const char *output_file = gtk_entry_get_text(GTK_ENTRY(widgets->output_entry));
    const char *lang_pair = gtk_entry_get_text(GTK_ENTRY(widgets->lang_entry));

    if (strlen(input_file) > 0 && strlen(output_file) > 0 && strlen(lang_pair) > 0) {
        char command[512];
        snprintf(command, sizeof(command), "trans -b -i %s -o %s :%s", input_file, output_file, lang_pair);
        int result = system(command);

        if (result == 0) {
            gtk_label_set_text(GTK_LABEL(widgets->result_label), "Translation Completed!");
        } else {
            gtk_label_set_text(GTK_LABEL(widgets->result_label), "Translation Failed!");
        }
    } else {
        gtk_label_set_text(GTK_LABEL(widgets->result_label), "Please fill in all fields.");
    }
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *input_label, *output_label, *lang_label;
    GtkWidget *input_button, *output_button, *translate_button;

    AppWidgets widgets;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Text File Translator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    input_label = gtk_label_new("Input File:");
    gtk_grid_attach(GTK_GRID(grid), input_label, 0, 0, 1, 1);

    widgets.input_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets.input_entry, 1, 0, 1, 1);

    input_button = gtk_button_new_with_label("Browse");
    g_signal_connect(input_button, "clicked", G_CALLBACK(on_input_file_clicked), &widgets);
    gtk_grid_attach(GTK_GRID(grid), input_button, 2, 0, 1, 1);

    output_label = gtk_label_new("Output File:");
    gtk_grid_attach(GTK_GRID(grid), output_label, 0, 1, 1, 1);

    widgets.output_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets.output_entry, 1, 1, 1, 1);

    output_button = gtk_button_new_with_label("Browse");
    g_signal_connect(output_button, "clicked", G_CALLBACK(on_output_file_clicked), &widgets);
    gtk_grid_attach(GTK_GRID(grid), output_button, 2, 1, 1, 1);

    lang_label = gtk_label_new("Language Code (e.g., 'en:de'):");
    gtk_grid_attach(GTK_GRID(grid), lang_label, 0, 2, 1, 1);

    widgets.lang_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets.lang_entry, 1, 2, 1, 1);

    translate_button = gtk_button_new_with_label("Translate");
    g_signal_connect(translate_button, "clicked", G_CALLBACK(on_translate_clicked), &widgets);
    gtk_grid_attach(GTK_GRID(grid), translate_button, 1, 3, 1, 1);

    widgets.result_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), widgets.result_label, 1, 4, 1, 1);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
