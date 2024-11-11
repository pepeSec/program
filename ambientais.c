#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

// Função para buscar dados do cliente no arquivo "clientes.txt"
void buscar_dados_cliente(const char *cnpj, GtkWidget **entries) {
    FILE *file = fopen("clientes.txt", "r");
    if (file == NULL) {
        g_print("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    char linha[256];
    int encontrado = 0;

    // Limpar os campos antes de realizar a busca
    for (int i = 0; i < 9; i++) {
        gtk_entry_set_text(GTK_ENTRY(entries[i]), "");
    }

    while (fgets(linha, sizeof(linha), file)) {
        // Remover a quebra de linha no final
        linha[strcspn(linha, "\n")] = 0;

        // Procurar o CNPJ na linha lida
        if (strstr(linha, cnpj)) {
            encontrado = 1;

            // Variáveis temporárias para armazenar os dados
            char nome[100], razao_social[100], telefone[50], endereco[100], email[100], data_abertura[50];

            // Usando strtok para separar os dados pelos delimitadores "|"
            char *token = strtok(linha, "|");
            int i = 0;

            // Iterando sobre os tokens para ler os dados
            while (token != NULL) {
                switch (i) {
                    case 0:
                        sscanf(token, "Nome: %[^\n]", nome);
                        break;
                    case 1:
                        sscanf(token, "CNPJ: %[^\n]", cnpj);
                        break;
                    case 2:
                        sscanf(token, "Razão Social: %[^\n]", razao_social);
                        break;
                    case 3:
                        sscanf(token, "Telefone: %[^\n]", telefone);
                        break;
                    case 4:
                        sscanf(token, "Endereço: %[^\n]", endereco);
                        break;
                    case 5:
                        sscanf(token, "E-mail: %[^\n]", email);
                        break;
                    case 6:
                        sscanf(token, "Data de Abertura: %[^\n]", data_abertura);
                        break;
                    default:
                        break;
                }
                token = strtok(NULL, "|");
                i++;
            }

            // Preencher os campos com os dados lidos
            gtk_entry_set_text(GTK_ENTRY(entries[0]), nome);            // Nome
            gtk_entry_set_text(GTK_ENTRY(entries[1]), cnpj);            // CNPJ
            gtk_entry_set_text(GTK_ENTRY(entries[2]), razao_social);   // Razão Social
            gtk_entry_set_text(GTK_ENTRY(entries[3]), telefone);       // Telefone
            gtk_entry_set_text(GTK_ENTRY(entries[4]), endereco);       // Endereço
            gtk_entry_set_text(GTK_ENTRY(entries[5]), email);          // E-mail
            gtk_entry_set_text(GTK_ENTRY(entries[6]), data_abertura);  // Data de Abertura

            break;  // Encontrou o cliente, sai do loop
        }
    }

    if (!encontrado) {
        g_print("CNPJ não encontrado.\n");
    }

    fclose(file);
}

// Função para salvar os dados ambientais em "dadosAmbientais.txt"
void salvar_dados_ambientais(GtkWidget **entries) {
    FILE *file = fopen("dadosAmbientais.txt", "a");
    if (file == NULL) {
        g_print("Erro ao abrir o arquivo de dados ambientais.\n");
        return;
    }

    fprintf(file, "Nome: %s\nCNPJ: %s\nRazão Social: %s\nTelefone: %s\nEndereço: %s\nE-mail: %s\nData de Abertura: %s\nQuantidade de Resíduos: %s\nEstimativa de Custos: %s\n\n",
            gtk_entry_get_text(GTK_ENTRY(entries[0])),
            gtk_entry_get_text(GTK_ENTRY(entries[1])),
            gtk_entry_get_text(GTK_ENTRY(entries[2])),
            gtk_entry_get_text(GTK_ENTRY(entries[3])),
            gtk_entry_get_text(GTK_ENTRY(entries[4])),
            gtk_entry_get_text(GTK_ENTRY(entries[5])),
            gtk_entry_get_text(GTK_ENTRY(entries[6])),
            gtk_entry_get_text(GTK_ENTRY(entries[7])),
            gtk_entry_get_text(GTK_ENTRY(entries[8])));

    fclose(file);
    g_print("Dados ambientais salvos com sucesso.\n");
}

// Função callback para o botão "Buscar"
void on_buscar_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const char *cnpj = gtk_entry_get_text(GTK_ENTRY(entries[1]));

    if (*cnpj == '\0') {
        g_print("Erro: CNPJ não foi inserido.\n");
        return;
    }

    buscar_dados_cliente(cnpj, entries);
}

// Função callback para o botão "Inserir"
void on_inserir_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    salvar_dados_ambientais(entries);
}

// Função para abrir a janela de atualização de dados ambientais
void open_ambiental_window() {
    GtkWidget *window, *vbox, *grid, *buscar_button, *inserir_button;
    GtkWidget *labels[9];
    static GtkWidget *entries[9]; // Array de campos de entrada
    const char *label_texts[] = {
        "Nome", "CNPJ", "Razão Social", "Telefone", "Endereço", "E-mail", "Data de Abertura", "Quantidade de Resíduos", "Estimativa de Custos"
    };

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Atualização de Dados Ambientais");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    for (int i = 0; i < 9; i++) {
        labels[i] = gtk_label_new(label_texts[i]);
        entries[i] = gtk_entry_new();

        // Tornar todos os campos somente leitura, exceto o CNPJ
        if (i != 1) {  // O índice 1 corresponde ao campo CNPJ
            gtk_widget_set_sensitive(entries[i], FALSE);  // Desabilita a edição
            gtk_widget_set_name(entries[i], "readonly_entry");
        }

        gtk_grid_attach(GTK_GRID(grid), labels[i], 0, i, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), entries[i], 1, i, 1, 1);
    }

    // Estilo CSS para os campos de leitura
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, "#readonly_entry { background-color: #E0E0E0; }", -1, NULL);
    GtkStyleContext *context;
    for (int i = 0; i < 7; i++) {
        context = gtk_widget_get_style_context(entries[i]);
        gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    }

    // Botão Buscar
    buscar_button = gtk_button_new_with_label("Buscar");
    g_signal_connect(buscar_button, "clicked", G_CALLBACK(on_buscar_clicked), entries);
    gtk_box_pack_start(GTK_BOX(vbox), buscar_button, FALSE, FALSE, 0);

    // Botão Inserir
    inserir_button = gtk_button_new_with_label("Inserir");
    g_signal_connect(inserir_button, "clicked", G_CALLBACK(on_inserir_clicked), entries);
    gtk_box_pack_start(GTK_BOX(vbox), inserir_button, FALSE, FALSE, 0);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), window);
    gtk_widget_show_all(window);
}
