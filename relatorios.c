#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

// Função para abrir o explorador de arquivos e escolher o local de salvamento
char* escolher_local_salvamento(const char* titulo) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new(titulo, NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "_Cancelar", GTK_RESPONSE_CANCEL,
                                         "_Salvar", GTK_RESPONSE_ACCEPT, NULL);

    // Configura a extensão padrão para ".xls"
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "relatorio.xls");

    char *nome_arquivo = NULL;

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        nome_arquivo = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }

    gtk_widget_destroy(dialog);
    return nome_arquivo;
}

// Função para gerar o relatório de funcionários
void gerar_relatorio_funcionarios(const char *cnpj) {
    char *caminho_relatorio = escolher_local_salvamento("Salvar Relatório de Funcionários");
    if (!caminho_relatorio) {
        g_print("Salvamento cancelado.\n");
        return;
    }

    FILE *arquivo_funcionarios = fopen("funcionarios.txt", "r");
    FILE *relatorio = fopen(caminho_relatorio, "w");

    if (!arquivo_funcionarios || !relatorio) {
        g_print("Erro ao abrir os arquivos.\n");
        g_free(caminho_relatorio);
        return;
    }

    // Escreve o cabeçalho do arquivo Excel
    fprintf(relatorio, "Nome\tCPF\tCargo\tTelefone\tE-mail\tCNPJ\tRazao Social\n");

    char linha[256];
    char nome[50], cpf[20], cargo[50], telefone[20], email[50], cnpj_lido[20], razao_social[50];
    int encontrou_funcionario = 0;

    // Lê o arquivo funcionarios.txt linha por linha
    while (fgets(linha, sizeof(linha), arquivo_funcionarios)) {
        // Remove nova linha
        linha[strcspn(linha, "\n")] = 0;

        // Verifica e armazena cada campo de informação
        if (sscanf(linha, "Nome: %[^\n]", nome) == 1) {
            fgets(linha, sizeof(linha), arquivo_funcionarios); sscanf(linha, "CPF: %[^\n]", cpf);
            fgets(linha, sizeof(linha), arquivo_funcionarios); sscanf(linha, "Cargo: %[^\n]", cargo);
            fgets(linha, sizeof(linha), arquivo_funcionarios); sscanf(linha, "Telefone: %[^\n]", telefone);
            fgets(linha, sizeof(linha), arquivo_funcionarios); sscanf(linha, "E-mail: %[^\n]", email);
            fgets(linha, sizeof(linha), arquivo_funcionarios); sscanf(linha, "CNPJ: %[^\n]", cnpj_lido);
            fgets(linha, sizeof(linha), arquivo_funcionarios); sscanf(linha, "Razão Social: %[^\n]", razao_social);

            // Verifica se o CNPJ coincide com o inserido pelo usuário
            if (strcmp(cnpj, cnpj_lido) == 0) {
                encontrou_funcionario = 1;
                fprintf(relatorio, "%s\t%s\t%s\t%s\t%s\t'%s\t%s\n", nome, cpf, cargo, telefone, email, cnpj_lido, razao_social);
            }
        }
    }

    // Mensagem caso nenhum funcionário seja encontrado com o CNPJ informado
    if (!encontrou_funcionario) {
        g_print("Nenhum funcionário encontrado para o CNPJ: %s\n", cnpj);
    } else {
        g_print("Relatório de funcionários gerado com sucesso!\n");
    }

    fclose(arquivo_funcionarios);
    fclose(relatorio);
    g_free(caminho_relatorio);
}

// Função para gerar o relatório de dados ambientais
void gerar_relatorio_dados_ambientais(const char *cnpj) {
    char *caminho_relatorio = escolher_local_salvamento("Salvar Relatório de Dados Ambientais");
    if (!caminho_relatorio) {
        g_print("Salvamento cancelado.\n");
        return;
    }

    FILE *arquivo_dados_ambientais = fopen("dadosAmbientais.txt", "r");
    FILE *relatorio = fopen(caminho_relatorio, "w");

    if (!arquivo_dados_ambientais || !relatorio) {
        g_print("Erro ao abrir os arquivos.\n");
        g_free(caminho_relatorio);
        return;
    }

    // Escreve o cabeçalho do arquivo Excel
    fprintf(relatorio, "Nome\tCNPJ\tRazao Social\tTelefone\tEndereco\tEmail\tData de Abertura\tData de Medicao\tQuantidade de Residuos\tEstimativa de Custos\n");

    char linha[256];
    char nome[50], cnpj_lido[20], razao_social[50], telefone[20], endereco[100], email[50];
    char data_abertura[20], data_medicao[20], quantidade_residuos[20], estimativa_custos[20];
    int encontrou_dado_ambiental = 0;

    // Lê o arquivo dadosAmbientais.txt linha por linha
    while (fgets(linha, sizeof(linha), arquivo_dados_ambientais)) {
        // Remove nova linha
        linha[strcspn(linha, "\n")] = 0;

        // Verifica e armazena cada campo de informação
        if (sscanf(linha, "Nome: %[^\n]", nome) == 1) {
            fgets(linha, sizeof(linha), arquivo_dados_ambientais); sscanf(linha, "CNPJ: %[^\n]", cnpj_lido);
            fgets(linha, sizeof(linha), arquivo_dados_ambientais); sscanf(linha, "Razão Social: %[^\n]", razao_social);
            fgets(linha, sizeof(linha), arquivo_dados_ambientais); sscanf(linha, "Telefone: %[^\n]", telefone);
            fgets(linha, sizeof(linha), arquivo_dados_ambientais); sscanf(linha, "Endereço: %[^\n]", endereco);
            fgets(linha, sizeof(linha), arquivo_dados_ambientais); sscanf(linha, "E-mail: %[^\n]", email);
            fgets(linha, sizeof(linha), arquivo_dados_ambientais); sscanf(linha, "Data de Abertura: %[^\n]", data_abertura);
            fgets(linha, sizeof(linha), arquivo_dados_ambientais); sscanf(linha, "Data de Medição: %[^\n]", data_medicao);
            fgets(linha, sizeof(linha), arquivo_dados_ambientais); sscanf(linha, "Quantidade de Resíduos: %[^\n]", quantidade_residuos);
            fgets(linha, sizeof(linha), arquivo_dados_ambientais); sscanf(linha, "Estimativa de Custos: %[^\n]", estimativa_custos);

            // Verifica se o CNPJ coincide com o inserido pelo usuário
            if (strcmp(cnpj, cnpj_lido) == 0) {
                encontrou_dado_ambiental = 1;
                // Escreve os dados no arquivo Excel com o CNPJ em formato de texto
                fprintf(relatorio, "%s\t'%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
                        nome, cnpj_lido, razao_social, telefone, endereco, email,
                        data_abertura, data_medicao, quantidade_residuos, estimativa_custos);
            }
        }
    }

    // Mensagem caso nenhum dado ambiental seja encontrado com o CNPJ informado
    if (!encontrou_dado_ambiental) {
        g_print("Nenhum dado ambiental encontrado para o CNPJ: %s\n", cnpj);
    } else {
        g_print("Relatório de dados ambientais gerado com sucesso!\n");
    }

    fclose(arquivo_dados_ambientais);
    fclose(relatorio);
    g_free(caminho_relatorio);
}

// Função de callback para o botão de Relatório de Funcionários
void on_relatorio_funcionarios_clicked(GtkWidget *widget, gpointer data) {
    const char *cnpj = gtk_entry_get_text(GTK_ENTRY(data));
    g_print("Gerando relatório de Funcionários para CNPJ: %s\n", cnpj);
    gerar_relatorio_funcionarios(cnpj);
}

// Função de callback para o botão de Relatório de Dados Ambientais
void on_relatorio_dados_ambientais_clicked(GtkWidget *widget, gpointer data) {
    const char *cnpj = gtk_entry_get_text(GTK_ENTRY(data));
    g_print("Gerando relatório de Dados Ambientais para CNPJ: %s\n", cnpj);
    gerar_relatorio_dados_ambientais(cnpj);
}

// Função para abrir a janela de geração de relatórios
void open_relatorios_window() {
    GtkWidget *window, *vbox, *grid;
    GtkWidget *cnpj_label, *cnpj_entry;
    GtkWidget *relatorio_funcionarios_button, *relatorio_dados_ambientais_button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Geração de Relatórios");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Centralizando o grid no vbox
    GtkWidget *alignment = gtk_alignment_new(0.5, 0.5, 0, 0);  // Alinhamento central
    gtk_box_pack_start(GTK_BOX(vbox), alignment, TRUE, TRUE, 0);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(alignment), grid);  // Adiciona o grid ao alinhamento centralizado

    // Campo de entrada do CNPJ
    cnpj_label = gtk_label_new("CNPJ:");
    cnpj_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), cnpj_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cnpj_entry, 1, 0, 1, 1);

    // Botão para Relatório de Funcionários
    relatorio_funcionarios_button = gtk_button_new_with_label("Relatório de Funcionários");
    g_signal_connect(relatorio_funcionarios_button, "clicked", G_CALLBACK(on_relatorio_funcionarios_clicked), cnpj_entry);
    gtk_box_pack_start(GTK_BOX(vbox), relatorio_funcionarios_button, TRUE, TRUE, 0);

    // Botão para Relatório de Dados Ambientais
    relatorio_dados_ambientais_button = gtk_button_new_with_label("Relatório de Dados Ambientais");
    g_signal_connect(relatorio_dados_ambientais_button, "clicked", G_CALLBACK(on_relatorio_dados_ambientais_clicked), cnpj_entry);
    gtk_box_pack_start(GTK_BOX(vbox), relatorio_dados_ambientais_button, TRUE, TRUE, 0);

    // Exibir a janela de relatórios
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_widget_show_all(window);
}
