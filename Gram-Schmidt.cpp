#include<bits/stdc++.h>

#define nmax 16

typedef struct{
  double coord[nmax];
} vetor;

//calcula produto escalar entre dois vetores
double prod_escalar(vetor *a, vetor *b, int *dim){
  double prod = 0;
  for(int i = 0; i < *dim; i++)
    prod += a->coord[i] * b->coord[i];
  return prod;
}

//multiplica vetor por escalar
vetor * mult_vetor(vetor * ve,int *dim, double *k){
  vetor * vs = (vetor *) malloc(sizeof(vetor*));
  for(int i = 0; i < *dim; i++)
    vs->coord[i] = ve->coord[i] * (*k);
  return vs;
}

//cria vetor a partir de canal de entrada
vetor * make_vetor(int *dim){
  vetor *v = (vetor*) malloc(sizeof(vetor));
  for(int i = 0; i < *dim; i++)
    scanf("%lf", &(v->coord[i]));
  return v;
}

//subtrai dois vetores
vetor * subtracao(vetor *a, vetor *b, int *dim){
  for(int i = 0; i < *dim; i++){
    a->coord[i] -= b->coord[i];
  }
  return a;
}

//projeta vetor em espaco perpendicular a outro
vetor * proj_perp(vetor *esse, vetor *nesse, int *dim){
  double k = prod_escalar(esse,nesse,dim) * prod_escalar(nesse,nesse,dim);
  esse = subtracao(esse,mult_vetor(nesse,dim,&k),dim);
  return esse;
}

//calc vetor unitario
vetor * unitario(vetor *v, int *dim){
  double k = 1/sqrt(prod_escalar(v,v,dim));
  return mult_vetor(v, dim, &k);
}

int main(){

  //leitura de parametros
  int qnt_vet, dim;
  printf("Determine:\nQuantidade de vetores\tDimensao do espaco vetorial (max. 16)\n");
  scanf("%d %d", &qnt_vet, &dim);

  //declaracao do vetor de vetores
  vetor * lista_vetores[qnt_vet];

  //leitura dos vetores e armazenamento no vetor
  printf("Digite as coordenadas para cada vetor\nc1 ... cn\n");
  for(int i = 0; i < qnt_vet; i++)
    lista_vetores[i] = make_vetor(&dim);

  //algoritmo
  for(int i = 0; i < qnt_vet; i++){
    //obter qi final, perpendicular a todos outros qj (j!=i)
    for(int j = 0; j < i; j++)
      lista_vetores[i] = proj_perp(lista_vetores[i], lista_vetores[j], &dim);

    //tornar qi vetor unitario
    lista_vetores[i] = unitario(lista_vetores[i], &dim);
  }

  //Impressao de vetores
  for(int i = 0; i < qnt_vet; i++){
    printf("Vetor %d\n", i+1);
    for(int j = 0; j < dim; j++){
      printf("%.3lf ", lista_vetores[i]->coord[j]);
    }printf("\n");
  }

}
