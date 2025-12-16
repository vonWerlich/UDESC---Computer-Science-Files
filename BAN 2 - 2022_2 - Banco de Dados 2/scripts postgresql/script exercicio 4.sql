-- 1) Recupere o nome e o endereço de cada cliente.
-- select nome,endereco from cliente

-- 2) Recupere o nome e a função dos mecânicos que trabalham no setor número 2 (cods 2).
-- select nome,funcao from mecanico where cods=2

-- 3) Recupere o CPF e o nome de todos os mecânicos que são clientes da oficina (utilize operação de conjuntos).
-- select m.cpf,m.nome from mecanico m join cliente c on m.cpf=c.cpf
-- ou
-- select m.cpf,m.nome from mecanico m, cliente c where m.cpf=c.cpf

-- 4) Recupere as cidades das quais os mecânicos e clientes são oriundos.
select cidade

-- 5) Recupere as marcas distintas dos veículos dos clientes que moram em Joinville.
-- select distinct marca from cliente c join veiculo v on c.codc=v.codc where c.cidade='Joinville'

-- 6) Recupere as funções distintas dos mecânicos da oficina.
-- select distinct funcao from mecanico

-- 7) Recupere todas as informações dos clientes que têm idade maior que 25 anos.
-- select * from cliente where idade>25

-- 8) Recupere o CPF e o nome dos mecânicos que trabalham no setor de mecânica.
-- select m.cpf,m.nome from mecanico m join setor s on m.cods=s.cods where s.nome='Mecânica'

-- 9) Recupere o CPF e nome dos mecânicos que trabalharam no dia 13/06/2014.
-- select distinct m.cpf,m.nome from mecanico m join conserto c ON m.codm=c.codm where c.data='2014-06-13'

-- 10) Recupere o nome do cliente, o modelo do seu veículo, o nome do mecânico e sua função para todos os
-- consertos realizados (utilize join para realizar a junção).

-- select cl.nome, v.modelo, m.nome, m.funcao from cliente cl join veiculo v on cl.codc=v.codc join conserto co ON
-- v.codv=co.codv join mecanico m ON co.codm=m.codm

-- 11) Recupere o nome do mecânico, o nome do cliente e a hora do conserto para as serviços realizados no dia
-- 19/06/2014 (utilize join para realizar a junção).
-- select m.nome, cl.nome, co.hora from cliente cl join veiculo v on cl.codc=v.codc join conserto co ON
-- v.codv=co.codv join mecanico m ON co.codm=m.codm where co.data='2014-06-19'

-- 12) Recupere o código e o nome dos setores que foram utilizados entre os dias 12/06/2014 e 14/06/2014
-- (utilize join para realizar a junção).
-- select s.cods, s.nome from conserto c join mecanico m ON c.codm=m.codm join setor s ON s.cods=m.cods
-- where c.data>='2014-06-12' AND c.data<='2014-06-14'

