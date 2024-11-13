cmake_minimum_required(VERSION 3.10)
project(program C)

set(CMAKE_C_STANDARD 11)

# Caminho para os cabeçalhos e bibliotecas GTK
set(GTK_DIR "C:/Users/Henrique/Downloads/program/ucrt64")

# Inclui diretórios de cabeçalhos do GTK, GLib, Pango e HarfBuzz
include_directories(${GTK_DIR}/include/gtk-3.0)
include_directories(${GTK_DIR}/include/glib-2.0)
include_directories(${GTK_DIR}/lib/glib-2.0/include)
include_directories(${GTK_DIR}/include/pango-1.0)
include_directories(${GTK_DIR}/include/harfbuzz)
include_directories(${GTK_DIR}/include/cairo)
include_directories(${GTK_DIR}/include/gdk-pixbuf-2.0)
include_directories(${GTK_DIR}/include/atk-1.0)

# Linka com os diretórios de biblioteca
link_directories(${GTK_DIR}/lib)

# Define o executável e inclui os arquivos de código modular
add_executable(program login.c menu.c cliente.c funcionarios.c cliente.h funcionarios.h ambientais.c relatorios.c relatorios.h)

# Subsistema Windows para ocultar o console
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-mwindows")
endif()

# Incluir outras bibliotecas necessárias
target_link_libraries(program gtk-3 gobject-2.0 gdk-3 gdk_pixbuf-2.0 gio-2.0 pango-1.0 pangocairo-1.0 gthread-2.0)
target_link_libraries(program glib-2.0 cairo gobject-2.0 harfbuzz gdk_pixbuf-2.0 atk-1.0)
