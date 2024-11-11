// cliente.h
#ifndef CLIENTE_H
#define CLIENTE_H

void open_cliente_window();
void salvar_dados_cliente(const char *nome, const char *cpf, const char *endereco, const char *telefone);
void on_salvar_cliente_clicked(GtkWidget *widget, gpointer data);

#endif // CLIENTE_H
