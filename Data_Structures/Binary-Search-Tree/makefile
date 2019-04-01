# Pastas
srcdir = ./src
objdir = ./obj
incdir = ./include

#Vars
objects = $(objdir)/main.o

CPPFLAGS = -Wall -Iinclude/ -std=c++11

.PHONY: clean clean_exe clean_obj
.PHONY: abb

abb: $(objects)
	g++ -o abb $(objects) $(FLAGS)
	@echo "\n\n\nPara executar:"
	@echo "./abb arquivo_arvore arquivo_comandos\n"
$(objdir)/main.o: $(incdir)/ABB.hpp $(srcdir)/main.cpp
	mkdir -p obj
	g++ $(CPPFLAGS) -c $(srcdir)/main.cpp -o $(objdir)/main.o

# Limpa o executável e o diretorio de arquivos objeto
clean: clean_exe clean_obj

#Limpa o executável
clean_exe:
	@rm ./abb -f
	@echo "Arquivo executavel foi deletado"

# Limpa diretorio de arquivos objeto
clean_obj:
	@rm -rf $(objdir)
	@echo "Arquivos objeto foram deletados"
