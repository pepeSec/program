// funcionarios.h
#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

void open_funcionario_window();
void salvar_dados_funcionario(const char *nome, const char *cpf, const char *cargo, const char *telefone, const char *email);
void on_salvar_funcionario_clicked(GtkWidget *widget, gpointer data);

#endif // FUNCIONARIOS_H
