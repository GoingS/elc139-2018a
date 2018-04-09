# Nome: Victor Marquezini Fernandes

## Pthreads

1. 
### Particionamento:
A operação pode ser particionada sem grandes complicações. Se um vetor de 1000 dimensões é calculado por 2 threads, a primeira cuida das primeiras 500 casas e a segunda cuida do restante.

int start = offset*wsize;
int end = start + wsize;

### Comunicação: 
É feito o somatório dos resultados de cada thread no final da execução.

dotdata.c += mysum;

### Aglomeração:
As threads são criadas no começo pelo número definido e executam independentemente de si. No final, a soma de cada uma é juntada para o resultado final.

### Mapeamento:
O número de thread a ser usado é definido pelo argumento na chamada do programa.

2. A aceleração de um vetor com 1 milhão de casas com 2 threads é 1.7618.

3. Até 8 threads a aceleração aumenta. Após isso o tempo não diminui, tende a aumentar inclusive. Isso acontece porquê o processador que testei tem só 8 núcleos virtuais.

4. 
Vetor com 1 milhão de dimensões
|Threads| Rep. | Tempo | Aceler |
|-------|------|-------|--------|
| 1 	| 2000 | 7.3s  | -	|
| 1	| 5000 | 18.4s | -	|
| 2	| 2000 | 4.4s  | 1.76	|
| 2	| 5000 | 10.4s | 1.77	|
| 4	| 2000 | 3.7s  | 1.97	|
| 4	| 5000 | 9.8s  | 1.87	|
| 8	| 2000 | 3.5s  | 2.09	|
| 8	| 5000 | 8.8s  | 2.09	|
| 16	| 2000 | 3.5s  | 2.09	|
| 16	| 5000 | 8.3s  | 2.21	|

5. A única diferença é o mutex. Ele não permite que a soma total seja acessada por mais de uma thread ao mesmo tempo. Isso é útil para evitar que sejam realizadas escritas e leituras incompletas quando são acessadas ao mesmo tempo.




## OpenMP


## Referências
