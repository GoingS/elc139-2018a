# T4: Scheduling com OpenMP 
# Victor Marquezini Fernandes

## Código do programa
[programa.c](programa.c)

## Exemplo de saída
Vetor sem mutex 1
```
AAAAAAAAAAAAAAAAAAAACBCBCBBCBCBCBCB-BCBCBCBBCCCCCCCC--------
Vetor sem mutex 2
BCBBCBCCBCBCBCCBCBBCBBCBBCBCCCCAAAAAAAAAAAAAAAAAAAA---------
Vetor com mutex
AAAAAAAABBBAAAABBBBBBBCCCCCCCCCCAAAABBACCCCCCCAAACCCBBBBBBBB
```

## Mais um exemplo
```
Vetor sem mutex 1
AAAAAAAAAAAAAAAAAABCBBCBCCBBBCBCCBCBBCBCBCBCCCCBCCCC--------
Vetor sem mutex 2
CCBBBBCBBCBBCBBCBBCCBCCCCCCAAAAAAAAAAAAAAAAAAAA-------------
Vetor com mutex
AAAAAAAAAAAACAACCCCCAABBBBBBBBABBBBBAABABBCCBBCCCCCCCCBBCCCC
```


## Referências
http://cs.umw.edu/~finlayson/class/fall16/cpsc425/notes/12-scheduling.html
