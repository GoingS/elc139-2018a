##Parte 1

(a) O perfil é afetado pelas opções de configuração?

Sim, como o esperado. Testei com um vetor com 3 milhões de casas. Para 10 repetições, que demorou 0.16s, apenas 81% do tempo foi usado para os cálculos de fato, o resto foi usado para a inicialização dos vetores. Já para 1000 repetições, demorando 10.27s, 99.8% do tempo foi alocado para os cálculos.

(b) Pelo perfil de execução, há alguma função que poderia ser candidata a paralelização? Por quê?

Não há função que possa ser paralizada. Isso porque as duas funções principais dot_product e init_vectors são chamadas apenas uma vez.

##Parte 2
