// ambientais.h
#ifndef AMBIENTAIS.H
#define AMBIENTAIS.H

void buscar_dados_cliente(const char *cnpj, GtkWidget **entries);
void salvar_dados_ambientais(GtkWidget **entries, GtkWidget *message_label);
void on_buscar_clicked(GtkWidget *widget, gpointer data);
void on_inserir_clicked(GtkWidget *widget, gpointer data);
void open_ambiental_window();

#endif // AMBIENTAIS.H
