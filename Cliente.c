#include <gtk/gtk.h>
#include <stdio.h>

// Função para salvar dados do cliente em um arquivo
void salvar_dados_cliente(const char *nome, const char *cnpj, const char *razao, const char *telefone, const char *endereco, const char *email, const char *data_abertura) {
    FILE *file = fopen("clientes.txt", "a");
    if (file == NULL) {
        g_print("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    fprintf(file, "Nome: %s\nCNPJ: %s\nRazão Social: %s\nTelefone: %s\nEndereço: %s\nE-mail: %s\nData de Abertura: %s\n\n", nome, cnpj, razao, telefone, endereco, email, data_abertura);
    fclose(file);
    g_print("Dados do cliente salvos com sucesso.\n");
}

// Callback para salvar os dados quando o botão "Salvar" for clicado
void on_salvar_cliente_clicked(GtkWidget *widget, gpointer data) {
    g_print("Botão Salvar clicado!\n");

    GtkWidget **entries = (GtkWidget **)g_object_get_data(G_OBJECT(data), "entries");

    // Verifica se as entradas são válidas e cada campo está atribuído
    for (int i = 0; i < 7; i++) {
        if (entries[i] == NULL) {
            g_print("Erro: Campo de entrada %d é nulo.\n", i);
            return;
        }
    }

    const char *nome = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *cnpj = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const char *razao = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const char *telefone = gtk_entry_get_text(GTK_ENTRY(entries[3]));
    const char *endereco = gtk_entry_get_text(GTK_ENTRY(entries[4]));
    const char *email = gtk_entry_get_text(GTK_ENTRY(entries[5]));
    const char *data_abertura = gtk_entry_get_text(GTK_ENTRY(entries[6]));

    // Verifica se algum campo está vazio
    if (*nome == '\0' || *cnpj == '\0' || *razao == '\0' || *telefone == '\0' ||
        *endereco == '\0' || *email == '\0' || *data_abertura == '\0') {
        g_print("Erro: Um ou mais campos de entrada estão vazios.\n");
        return;
    }

    salvar_dados_cliente(nome, cnpj, razao, telefone, endereco, email, data_abertura);
}

// Função para abrir a janela de cadastro de cliente
void open_cliente_window() {
    GtkWidget *window, *vbox, *grid;
    GtkWidget *labels[7];
    static GtkWidget *entries[7]; // Array estático para garantir que os dados persistam após a função retornar
    const char *label_texts[] = {
        "Nome", "CNPJ", "Razão Social", "Telefone", "Endereço", "E-mail", "Data de Abertura"
    };

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Cadastro de Clientes");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);  // Ajuste do tamanho da janela

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    for (int i = 0; i < 7; i++) {
        labels[i] = gtk_label_new(label_texts[i]);
        entries[i] = gtk_entry_new();

        // Verifica imediatamente se o campo foi criado com sucesso
        if (entries[i] == NULL) {
            g_print("Erro: Não foi possível criar a entrada para o campo %d (%s)\n", i, label_texts[i]);
            return;
        }

        // Distribuindo os campos em duas colunas no grid
        int row = i / 2;  // Determina a linha
        int col = i % 2;  // Determina a coluna (0 ou 1)
        gtk_grid_attach(GTK_GRID(grid), labels[i], col * 2, row, 1, 1);  // Coloca o label
        gtk_grid_attach(GTK_GRID(grid), entries[i], col * 2 + 1, row, 1, 1);  // Coloca a entrada
    }

    // Armazena o array de entradas na janela para acessar na função de salvar
    g_object_set_data(G_OBJECT(window), "entries", entries);

    GtkWidget *save_button = gtk_button_new_with_label("Salvar");
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_salvar_cliente_clicked), window);

    gtk_box_pack_start(GTK_BOX(vbox), save_button, FALSE, FALSE, 0);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), window);

    gtk_widget_show_all(window);
}
