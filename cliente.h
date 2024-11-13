// cliente.h
#ifndef CLIENTE_H
#define CLIENTE_H

void open_cliente_window();
void salvar_dados_cliente(const char *nome, const char *cnpj, const char *razao, const char *telefone, const char *endereco, const char *email, const char *data_abertura, GtkWidget *message_label);
void on_salvar_cliente_clicked(GtkWidget *widget, gpointer data);

#endif // CLIENTE_H
