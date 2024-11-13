#ifndef RELATORIOS_H
#define RELATORIOS_H

char* escolher_local_salvamento(const char* titulo);
void gerar_relatorio_funcionarios(const char *cnpj);
void gerar_relatorio_dados_ambientais(const char *cnpj);
void on_relatorio_funcionarios_clicked(GtkWidget *widget, gpointer data);
void on_relatorio_dados_ambientais_clicked(GtkWidget *widget, gpointer data);
void open_relatorios_window();

#endif
