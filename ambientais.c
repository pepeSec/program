#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função para buscar dados do cliente no arquivo "clientes.txt"
void buscar_dados_cliente(const char *cnpj, GtkWidget **entries) {
    FILE *file = fopen("clientes.txt", "r");
    if (file == NULL) {
        g_print("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    char linha[256];
    int encontrado = 0;

    // Limpar os campos antes de realizar a busca, mas mantendo o CNPJ
    for (int i = 0; i < 9; i++) {  // Ajustando para 9 campos
        if (i != 1)  // Não limpar o campo do CNPJ
            gtk_entry_set_text(GTK_ENTRY(entries[i]), "");
    }

    // Variáveis temporárias para armazenar os dados
    char nome[100] = "", cnpj_tmp[50] = "", razao_social[100] = "", telefone[50] = "";
    char endereco[100] = "", email[100] = "", data_abertura[50] = "";

    // Loop para ler todas as linhas do arquivo
    while (fgets(linha, sizeof(linha), file)) {
        // Verificar e extrair cada campo
        if (strncmp(linha, "Nome: ", 6) == 0) {
            sscanf(linha, "Nome: %[^\n]", nome);
        } else if (strncmp(linha, "CNPJ: ", 6) == 0) {
            sscanf(linha, "CNPJ: %[^\n]", cnpj_tmp);

            // Verificar se o CNPJ encontrado corresponde ao CNPJ procurado
            if (strcmp(cnpj_tmp, cnpj) == 0) {
                encontrado = 1;
            }
        } else if (strncmp(linha, "Razão Social: ", 13) == 0) {
            sscanf(linha, "Razão Social: %[^\n]", razao_social);
        } else if (strncmp(linha, "Telefone: ", 9) == 0) {
            sscanf(linha, "Telefone: %[^\n]", telefone);
        } else if (strncmp(linha, "Endereço: ", 9) == 0) {
            sscanf(linha, "Endereço: %[^\n]", endereco);
        } else if (strncmp(linha, "E-mail: ", 7) == 0) {
            sscanf(linha, "E-mail: %[^\n]", email);
        } else if (strncmp(linha, "Data de Abertura: ", 17) == 0) {
            sscanf(linha, "Data de Abertura: %[^\n]", data_abertura);
        }

        // Ao encontrar o CNPJ correspondente e ler todos os campos, interromper o loop
        if (encontrado && linha[0] == '\n') {
            break;
        }
    }

    // Verificar se o CNPJ foi encontrado e preencher os campos
    if (encontrado) {
        gtk_entry_set_text(GTK_ENTRY(entries[0]), nome);            // Nome
        gtk_entry_set_text(GTK_ENTRY(entries[1]), cnpj);            // CNPJ (não alterado)
        gtk_entry_set_text(GTK_ENTRY(entries[2]), razao_social);    // Razão Social
        gtk_entry_set_text(GTK_ENTRY(entries[3]), telefone);        // Telefone
        gtk_entry_set_text(GTK_ENTRY(entries[4]), endereco);        // Endereço
        gtk_entry_set_text(GTK_ENTRY(entries[5]), email);           // E-mail
        gtk_entry_set_text(GTK_ENTRY(entries[6]), data_abertura);   // Data de Abertura

        // Mensagens de debug para verificar conteúdo das variáveis
        g_print("Dados extraídos:\n");
        g_print("Nome: %s\n", nome);
        g_print("CNPJ: %s\n", cnpj_tmp);
        g_print("Razão Social: %s\n", razao_social);
        g_print("Telefone: %s\n", telefone);
        g_print("Endereço: %s\n", endereco);
        g_print("E-mail: %s\n", email);
        g_print("Data de Abertura: %s\n", data_abertura);
    } else {
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

    fprintf(file, "Nome: %s\nCNPJ: %s\nRazão Social: %s\nTelefone: %s\nEndereço: %s\nE-mail: %s\nData de Abertura: %s\nData de Medição: %s\nQuantidade de Resíduos: %s\nEstimativa de Custos: %s\n\n",
            gtk_entry_get_text(GTK_ENTRY(entries[0])),
            gtk_entry_get_text(GTK_ENTRY(entries[1])),
            gtk_entry_get_text(GTK_ENTRY(entries[2])),
            gtk_entry_get_text(GTK_ENTRY(entries[3])),
            gtk_entry_get_text(GTK_ENTRY(entries[4])),
            gtk_entry_get_text(GTK_ENTRY(entries[5])),
            gtk_entry_get_text(GTK_ENTRY(entries[6])),
            gtk_entry_get_text(GTK_ENTRY(entries[9])),  // Incluindo Data de Medição
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
    GtkWidget *labels[10];
    static GtkWidget *entries[10];
    const char *label_texts[] = {
        "Nome", "CNPJ", "Razão Social", "Telefone",
        "Endereço", "E-mail", "Data de Abertura",
        "Quantidade de Resíduos", "Estimativa de Custos", "Data de Medição"
    };

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Atualização de Dados Ambientais");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 200);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    for (int i = 0; i < 10; i++) {
        labels[i] = gtk_label_new(label_texts[i]);
        entries[i] = gtk_entry_new();

        // Torna campos não editáveis, exceto CNPJ, Quantidade de Resíduos, Estimativa de Custos e Data de Medição
        if (i != 1 && i != 7 && i != 8 && i != 9) {
            gtk_widget_set_sensitive(entries[i], FALSE);
            gtk_entry_set_text(GTK_ENTRY(entries[i]), "");
            gtk_widget_override_background_color(entries[i], GTK_STATE_FLAG_NORMAL, &(GdkRGBA){0.9, 0.9, 0.9, 1});
        }

        // Organiza os labels e campos em 4 colunas
        gtk_grid_attach(GTK_GRID(grid), labels[i], (i % 4) * 2, i / 4, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), entries[i], (i % 4) * 2 + 1, i / 4, 1, 1);
    }

    buscar_button = gtk_button_new_with_label("Buscar");
    g_signal_connect(buscar_button, "clicked", G_CALLBACK(on_buscar_clicked), entries);
    gtk_box_pack_start(GTK_BOX(vbox), buscar_button, FALSE, FALSE, 0);

    inserir_button = gtk_button_new_with_label("Inserir");
    g_signal_connect(inserir_button, "clicked", G_CALLBACK(on_inserir_clicked), entries);
    gtk_box_pack_start(GTK_BOX(vbox), inserir_button, FALSE, FALSE, 0);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), window);

    gtk_widget_show_all(window);
}