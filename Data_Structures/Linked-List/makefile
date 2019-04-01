# FOLDERS
srcdir = ./src
objdir = ./obj
outdir = ./out
incdir = ./include

# ENV VARS
objects = $(objdir)/main.o

CPPFLAGS = -Wall -I include -std=c++11 -g

.PHONY: clean clean_exe clean_obj clean_out
.PHONY: test

tor: $(objects)
	mkdir -p res
	g++ -o test $(objects) $(FLAGS)
	@echo "\n\n\nTo execute, type:"
	@echo "./test\n"

$(objdir)/main.o: $(srcdir)/main.cpp
	mkdir -p obj
	g++ $(CPPFLAGS) -c $(srcdir)/main.cpp -o $(objdir)/main.o

# Limpa o executável e o diretorio de arquivos objeto
clean: clean_obj clean_out clean_exe

#Limpa o executável
clean_exe:
	@echo "Cleaning binaries..."
	@rm ./test -f

# Limpa diretorio de arquivos objeto
clean_obj:
	@echo "Cleaning objects..."
	@rm -rf $(objdir)

# Limpa diretorio de arquivos de saida
clean_out:
	@echo "Cleaning output files..."
	@rm -rf $(outdir)
