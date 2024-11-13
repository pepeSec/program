#include <gtk/gtk.h>
#include <stdio.h>

// Função para salvar dados do cliente em um arquivo
void salvar_dados_cliente(const char *nome, const char *cnpj, const char *razao, const char *telefone, const char *endereco, const char *email, const char *data_abertura, GtkWidget *message_label) {
    FILE *file = fopen("clientes.txt", "a");
    if (file == NULL) {
        g_print("Erro ao abrir o arquivo de clientes.\n");
        gtk_label_set_text(GTK_LABEL(message_label), "Erro ao salvar dados.");
        return;
    }

    fprintf(file, "Nome: %s\nCNPJ: %s\nRazão Social: %s\nTelefone: %s\nEndereço: %s\nE-mail: %s\nData de Abertura: %s\n\n", nome, cnpj, razao, telefone, endereco, email, data_abertura);
    fclose(file);
    gtk_label_set_text(GTK_LABEL(message_label), "Dados do cliente salvos com sucesso!");
    gtk_widget_set_name(message_label, "success_message");
}

// Callback para salvar os dados quando o botão "Salvar" for clicado
void on_salvar_cliente_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)g_object_get_data(G_OBJECT(data), "entries");
    GtkWidget *message_label = g_object_get_data(G_OBJECT(data), "message_label");

    const char *nome = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *cnpj = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const char *razao = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const char *telefone = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const char *endereco = gtk_entry_get_text(GTK_ENTRY(entries[4]));
    const char *email = gtk_entry_get_text(GTK_ENTRY(entries[5]));
    const char *data_abertura = gtk_entry_get_text(GTK_ENTRY(entries[6]));

    if (*nome == '\0' || *cnpj == '\0' || *razao == '\0' || *telefone == '\0' ||
        *endereco == '\0' || *email == '\0' || *data_abertura == '\0') {
        gtk_label_set_text(GTK_LABEL(message_label), "Erro: Todos os campos são obrigatórios.");
        gtk_widget_set_name(message_label, "error_message");
        return;
    }

    salvar_dados_cliente(nome, cnpj, razao, telefone, endereco, email, data_abertura, message_label);
}

// Função para abrir a janela de cadastro de cliente
void open_cliente_window() {
    GtkWidget *window, *vbox, *grid;
    GtkWidget *labels[7];
    static GtkWidget *entries[7];
    GtkWidget *message_label;
    const char *label_texts[] = {
        "Nome", "CNPJ", "Razão Social", "Telefone", "Endereço", "E-mail", "Data de Abertura"
    };

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Cadastro de Clientes");
    gtk_window_set_default_size(GTK_WINDOW(window), 550, 200);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *alignment = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), alignment, TRUE, TRUE, 0);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(alignment), grid);

    for (int i = 0; i < 7; i++) {
        labels[i] = gtk_label_new(label_texts[i]);
        entries[i] = gtk_entry_new();

        if (entries[i] == NULL) {
            g_print("Erro: Não foi possível criar a entrada para o campo %d (%s)\n", i, label_texts[i]);
            return;
        }

        int row = i / 2;
        int col = i % 2;
        gtk_grid_attach(GTK_GRID(grid), labels[i], col * 2, row, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), entries[i], col * 2 + 1, row, 1, 1);
    }

    // Limitar CNPJ a 14 dígitos e Telefone a 11 dígitos
    gtk_entry_set_max_length(GTK_ENTRY(entries[1]), 14);
    gtk_entry_set_max_length(GTK_ENTRY(entries[3]), 11);

    g_object_set_data(G_OBJECT(window), "entries", entries);

    // Mensagem de feedback para o usuário
    message_label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), message_label, FALSE, FALSE, 0);
    g_object_set_data(G_OBJECT(window), "message_label", message_label);

    // Botão de salvar
    GtkWidget *save_button = gtk_button_new_with_label("Salvar");
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_salvar_cliente_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), save_button, FALSE, FALSE, 0);

    // CSS para mensagens de sucesso e erro
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider,
        "#success_message { color: green; font-weight: bold; }\n"
        "#error_message { color: red; font-weight: bold; }\n",
        -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), window);

    gtk_widget_show_all(window);
}
