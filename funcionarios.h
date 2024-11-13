// funcionarios.h
#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

void buscar_razao_social(const char *cnpj, GtkWidget *razao_social_entry);
void open_funcionario_window();
void salvar_dados_funcionario(const char *nome, const char *cpf, const char *cargo, const char *telefone, const char *email, const char *cnpj, const char *razao_social);
void on_salvar_funcionario_clicked(GtkWidget *widget, gpointer data);
void on_buscar_clicado(GtkWidget *widget, gpointer data);

#endif // FUNCIONARIOS_H
