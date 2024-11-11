#include <gtk/gtk.h>
#include "cliente.h"
#include "funcionarios.h"
#include "ambientais.h"  // Inclui o arquivo ambientais.h

// Funções de callback para cada botão
void on_cadastro_cliente_clicked(GtkWidget *widget, gpointer data) {
    g_print("Cadastro de Clientes\n");
    open_cliente_window();
}

void on_cadastro_funcionario_clicked(GtkWidget *widget, gpointer data) {
    g_print("Cadastro de Funcionários\n");
    open_funcionario_window();
}

void on_atualizacao_dados_ambientais_clicked(GtkWidget *widget, gpointer data) {
    g_print("Atualização de dados ambientais\n");
    open_ambiental_window();  // Chama a função para abrir a janela de atualização de dados ambientais
}

void on_geracao_relatorios_clicked(GtkWidget *widget, gpointer data) {
    g_print("Geração de relatórios\n");
}

void open_menu_window() {
    GtkWidget *window, *vbox;
    GtkWidget *cadastro_cliente_button, *cadastro_funcionario_button;
    GtkWidget *atualizacao_dados_button, *geracao_relatorios_button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Menu Principal");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    cadastro_cliente_button = gtk_button_new_with_label("Cadastro de Clientes");
    cadastro_funcionario_button = gtk_button_new_with_label("Cadastro de Funcionários");
    atualizacao_dados_button = gtk_button_new_with_label("Atualização de dados ambientais");
    geracao_relatorios_button = gtk_button_new_with_label("Geração de relatórios");

    gtk_box_pack_start(GTK_BOX(vbox), cadastro_cliente_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), cadastro_funcionario_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), atualizacao_dados_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), geracao_relatorios_button, TRUE, TRUE, 0);

    // Conexões dos sinais para cada botão
    g_signal_connect(cadastro_cliente_button, "clicked", G_CALLBACK(on_cadastro_cliente_clicked), NULL);
    g_signal_connect(cadastro_funcionario_button, "clicked", G_CALLBACK(on_cadastro_funcionario_clicked), NULL);
    g_signal_connect(atualizacao_dados_button, "clicked", G_CALLBACK(on_atualizacao_dados_ambientais_clicked), NULL);
    g_signal_connect(geracao_relatorios_button, "clicked", G_CALLBACK(on_geracao_relatorios_clicked), NULL);

    // Mostra a janela do menu principal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}
