#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

// Função para buscar e preencher a Razão Social com base no CNPJ
void buscar_razao_social(const char *cnpj, GtkWidget *razao_social_entry) {
    FILE *file = fopen("clientes.txt", "r");
    if (file == NULL) {
        g_print("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    char linha[256], cnpj_tmp[50] = "", razao_social[100] = "";
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), file)) {
        if (strncmp(linha, "CNPJ: ", 6) == 0) {
            sscanf(linha, "CNPJ: %[^\n]", cnpj_tmp);
            if (strcmp(cnpj_tmp, cnpj) == 0) {
                encontrado = 1;
            }
        } else if (encontrado && strncmp(linha, "Razão Social: ", 13) == 0) {
            sscanf(linha, "Razão Social: %[^\n]", razao_social);
            break;
        }
    }

    if (encontrado) {
        gtk_entry_set_text(GTK_ENTRY(razao_social_entry), razao_social);
    } else {
        g_print("CNPJ não encontrado.\n");
    }

    fclose(file);
}

// Função para salvar dados do funcionário (atualizada)
void salvar_dados_funcionario(const char *nome, const char *cpf, const char *cargo, const char *telefone, const char *email, const char *cnpj, const char *razao_social, const char *usuario, const char *senha) {
    FILE *file = fopen("funcionarios.txt", "a");
    if (file == NULL) {
        g_print("Erro ao abrir o arquivo de funcionários.\n");
        return;
    }

    fprintf(file, "Nome: %s\nCPF: %s\nCargo: %s\nTelefone: %s\nE-mail: %s\nCNPJ: %s\nRazão Social: %s\nUsuário: %s\nSenha: %s\n\n",
            nome, cpf, cargo, telefone, email, cnpj, razao_social, usuario, senha);
    fclose(file);
    g_print("Dados do funcionário salvos com sucesso.\n");
}

// Callback para o botão Salvar (atualizado)
void on_salvar_funcionario_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)g_object_get_data(G_OBJECT(data), "entries");
    GtkWidget *message_label = GTK_WIDGET(g_object_get_data(G_OBJECT(data), "message_label"));

    const char *nome = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *cpf = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const char *cargo = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const char *telefone = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const char *email = gtk_entry_get_text(GTK_ENTRY(entries[4]));
    const char *cnpj = gtk_entry_get_text(GTK_ENTRY(entries[5]));
    const char *razao_social = gtk_entry_get_text(GTK_ENTRY(entries[6]));
    const char *usuario = gtk_entry_get_text(GTK_ENTRY(entries[7]));
    const char *senha = gtk_entry_get_text(GTK_ENTRY(entries[8]));

    if (*nome == '\0' || *cpf == '\0' || *cargo == '\0' || *telefone == '\0' || *email == '\0' || *cnpj == '\0' || *usuario == '\0' || *senha == '\0') {
        gtk_label_set_text(GTK_LABEL(message_label), "Erro: Um ou mais campos de entrada estão vazios.");
        return;
    }

    salvar_dados_funcionario(nome, cpf, cargo, telefone, email, cnpj, razao_social, usuario, senha);
    gtk_label_set_text(GTK_LABEL(message_label), "Dados do funcionário salvos com sucesso!");
}

// Callback para o botão Buscar
void on_buscar_clicado(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const char *cnpj = gtk_entry_get_text(GTK_ENTRY(entries[5]));

    if (*cnpj == '\0') {
        g_print("Erro: CNPJ não foi inserido.\n");
        return;
    }

    buscar_razao_social(cnpj, entries[6]);
}

// Função para abrir a janela de cadastro de funcionário (atualizada)
void open_funcionario_window() {
    GtkWidget *window, *vbox, *grid, *save_button, *buscar_button, *message_label;
    GtkWidget *labels[9];
    static GtkWidget *entries[9];
    const char *label_texts[] = {
        "Nome", "CPF", "Cargo", "Telefone", "E-mail", "CNPJ", "Razão Social", "Usuário", "Senha"
    };

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Cadastro de Funcionários");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 300);
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

    for (int i = 0; i < 9; i++) {
        labels[i] = gtk_label_new(label_texts[i]);
        entries[i] = gtk_entry_new();

        if (i == 6) {  // Campo Razão Social somente leitura
            gtk_widget_set_sensitive(entries[i], FALSE);
            gtk_widget_set_name(entries[i], "readonly_entry");
        }

        if (i == 1 || i == 3 || i == 5) {  // Restringe dígitos de CPF, Telefone e CNPJ
            int max_length = (i == 1 || i == 3) ? 11 : 14;
            gtk_entry_set_max_length(GTK_ENTRY(entries[i]), max_length);
        }

        if (i == 8) {  // Campo de senha
            gtk_entry_set_visibility(GTK_ENTRY(entries[i]), FALSE);
            gtk_entry_set_invisible_char(GTK_ENTRY(entries[i]), '*');
        }

        int row = i / 3; // Três colunas por linha
        int col = (i % 3) * 2; // Duas colunas (label e entry) por campo
        gtk_grid_attach(GTK_GRID(grid), labels[i], col, row, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), entries[i], col + 1, row, 1, 1);
    }

    g_object_set_data(G_OBJECT(window), "entries", entries);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, "#readonly_entry { background-color: #D3D3D3; }", -1, NULL);
    gtk_style_context_add_provider(gtk_widget_get_style_context(entries[6]), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    buscar_button = gtk_button_new_with_label("Buscar");
    g_signal_connect(buscar_button, "clicked", G_CALLBACK(on_buscar_clicado), entries);
    gtk_box_pack_start(GTK_BOX(vbox), buscar_button, FALSE, FALSE, 0);

    save_button = gtk_button_new_with_label("Salvar");
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_salvar_funcionario_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), save_button, FALSE, FALSE, 0);

    message_label = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(vbox), message_label, FALSE, FALSE, 0);
    g_object_set_data(G_OBJECT(window), "message_label", message_label);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), window);

    gtk_widget_show_all(window);
}
