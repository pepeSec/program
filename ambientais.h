// ambientais.h
#ifndef AMBIENTAIS.H
#define AMBIENTAIS.H

void buscar_dados_cliente(const char *cnpj, GtkWidget **entries);
void salvar_dados_ambientais(const char *nome, const char *cnpj, const char *razao, const char *telefone, const char *endereco, const char *email, const char *data_abertura, const char *residuos, const char *custo);
void on_buscar_clicked(GtkWidget *widget, gpointer data);
void on_inserir_clicked(GtkWidget *widget, gpointer data);
void open_ambiental_window();

#endif // AMBIENTAIS.H
