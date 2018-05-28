[Programação Paralela](https://github.com/GoingS/elc139-2018a) > Trabalhos

# Victor Marquezini Fernandes


1. Testes do programa [vetor.c](vetor.c)
(Um processo é usado para fazer a soma, por isso são 3, 5 e 9 e não 2, 4 e 8)

| NP 		| Tamanho vetor(vezes processos)	| Repetições	| Tempo	|
|-----------|-----------------------------------|---------------|-------|
| 3			| 2000								| 20,000        | 0.2s	|
| 3			| 2000								| 200,000       | 2.0s	|
| 5			| 2000								| 20,000        | 0.5s	|
| 5			| 2000								| 200,000       | 3.9s	|
| 9			| 2000								| 20,000        | 1.0s	|
| 9			| 2000								| 200,000       | 6.6s	|

2. Exemplo de execução do programa [pipeline.c](pipeline.c):
```
mpiexec -np 5 ./pipeline
4 receving from 3
1 receving from 0
msg: 1
2 receving from 1
msg: 2
3 receving from 2
msg: 3
msg: 4
O resultado final eh 4
```

3. O primeiro programa usa a tag igual a seu rank. Assim cada processo tem uma tag diferente e nunca vai receber mensagem ou conseguir enviar, pois todas as tags são diferentes.

O segundo programa não estava finalizando apropriadamente. A função MPI_Finalize não estava sendo chamada.
