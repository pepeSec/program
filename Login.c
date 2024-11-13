#include <gtk/gtk.h>
#include <string.h>

// Declarando a função de menu
void open_menu_window();

// Definindo as credenciais
const char* username_stored = "admin";
const char* password_stored = "1234";

// Função para abrir o menu com atraso de 1 segundo
gboolean delayed_open_menu(gpointer data) {
    GtkWidget **widgets = (GtkWidget **)data;
    gtk_widget_hide(widgets[3]); // Fechar a janela de login
    open_menu_window(); // Abrir o menu
    return FALSE; // Remover o callback após execução
}

// Função de autenticação
void on_login_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **widgets = (GtkWidget **)data;
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(widgets[0]));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(widgets[1]));
    GtkWidget *message_label = widgets[2];

    if (strcmp(username, username_stored) == 0 && strcmp(password, password_stored) == 0) {
        gtk_label_set_text(GTK_LABEL(message_label), "Logado com sucesso!");
        gtk_widget_set_name(message_label, "success_message");

        // Atrasar a abertura do menu em 1 segundo (1000 milissegundos)
        g_timeout_add(1500, delayed_open_menu, widgets);
    } else {
        gtk_label_set_text(GTK_LABEL(message_label), "Login e/ou senha incorretos.");
        gtk_widget_set_name(message_label, "error_message");
    }
}

// Função para criar a janela de login
void create_login_window() {
    GtkWidget *window, *vbox, *hbox_username, *hbox_password;
    GtkWidget *username_entry, *password_entry;
    GtkWidget *username_label, *password_label, *login_button, *message_label;

    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Login");
    gtk_window_maximize(GTK_WINDOW(window));

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Caixa horizontal para "Usuário" e entrada de usuário
    hbox_username = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    username_label = gtk_label_new("Usuário:");
    username_entry = gtk_entry_new();
    gtk_widget_set_size_request(username_entry, 300, -1);
    gtk_box_pack_start(GTK_BOX(hbox_username), username_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_username), username_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_username, FALSE, FALSE, 0);

    // Caixa horizontal para "Senha" e entrada de senha
    hbox_password = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    password_label = gtk_label_new("Senha:");
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_widget_set_size_request(password_entry, 300, -1);
    gtk_box_pack_start(GTK_BOX(hbox_password), password_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_password), password_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_password, FALSE, FALSE, 0);

    // Botão de login e mensagem de feedback
    login_button = gtk_button_new_with_label("Entrar");
    gtk_box_pack_start(GTK_BOX(vbox), login_button, FALSE, FALSE, 0);

    message_label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), message_label, FALSE, FALSE, 0);

    // CSS para mensagens de sucesso e erro
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider,
        "#success_message { color: green; font-weight: bold; }\n"
        "#error_message { color: red; font-weight: bold; }\n",
        -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Widgets para a função de callback
    GtkWidget *widgets[4] = { username_entry, password_entry, message_label, window };

    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_button_clicked), widgets);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}

int main(int argc, char *argv[]) {
    create_login_window();
    return 0;
}
