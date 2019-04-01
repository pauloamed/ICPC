# Compactador Huffman - Compilação e Execução

## Compilação

Com os arquivos prontos, vai ser necessário:
```
g++
```
Para compilar, use:
```
make
```
Para limpeza, use:
```
make clean
```

## Execução

Para comprimir um arquivo, use:

```
./huffman -c file_name
ou
./huffman file_name -c
```
Para decomprimir um arquivo, use:

```
./huffman -u file_name
ou
./huffman file_name -u
```

Onde `file_name` é o arquivo que será comprimido/descomprimido.

Na compressão, o arquivo comprimido terá nome `file_name` + `_c.out`.

Na descompressão, o arquivo descomprimido terá nome `file_name` + `_u.out`.