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
