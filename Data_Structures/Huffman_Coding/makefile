# Pastas
srcdir = ./src
objdir = ./obj
incdir = ./include

#Vars
objects = $(objdir)/main.o

CPPFLAGS = -Wall -Iinclude/ -std=c++11

.PHONY: clean clean_exe clean_obj
.PHONY: huffman

huffman: $(objects)
	g++ -o huffman $(objects) $(FLAGS)
	@echo "\n\n\nPara executar:"
	@echo "./huffman {-c ou -u} file_name\n"
$(objdir)/main.o: $(incdir)/Node.hpp $(incdir)/Huffman.hpp $(incdir)/HeapMin.hpp $(srcdir)/main.cpp
	mkdir -p obj
	g++ $(CPPFLAGS) -c $(srcdir)/main.cpp -o $(objdir)/main.o

# Limpa o executável e o diretorio de arquivos objeto
clean: clean_exe clean_obj

#Limpa o executável
clean_exe:
	@rm ./huffman -f
	@echo "Arquivo executavel foi deletado"

# Limpa diretorio de arquivos objeto
clean_obj:
	@rm -rf $(objdir)
	@echo "Arquivos objeto foram deletados"
