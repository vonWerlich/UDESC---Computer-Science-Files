-- 1) Recupere o CPF e o nome dos mecânicos que trabalham nos setores número 1 e 2
-- (faça a consulta utilizando a cláusula IN).
-- select cpf,nome from mecanico WHERE cods IN (1,2)

-- 2) Recupere o CPF e o nome dos mecânicos que trabalham nos setores 'Funilaria' e 'Pintura'
-- (faça a consulta utilizando sub-consultas aninhadas).
-- select cpf,m.nome from mecanico m join setor s ON m.cods=s.cods WHERE m.cods IN (select cods FROM setor WHERE 
-- nome='Funilaria' OR nome='Pintura')
-- -- ou
-- select cpf,m.nome from mecanico m join setor s using (cods) WHERE m.cods IN (select cods FROM setor WHERE 
-- nome='Funilaria' OR nome='Pintura')

-- 3) Recupere o CPF e nome dos mecânicos que atenderam no dia 13/06/2014 (faça a consulta usando INNER JOIN).
-- SELECT distinct cpf,nome FROM mecanico m inner join conserto c ON m.codm=c.codm WHERE data='2014-06-13'
-- -- ou
-- SELECT distinct cpf,nome FROM mecanico m inner join conserto c using (codm) WHERE data='2014-06-13'

-- 4) Recupere o nome do mecânico, o nome do cliente e a hora do conserto para os consertos realizados no dia
-- 12/06/2014 (faça a consulta usando INNER JOIN).
-- select m.nome, cl.nome, co.hora from cliente cl inner join veiculo v using (codc) inner join conserto co using (codv) 
-- join mecanico m using (codm) where co.data='2014-06-12'

-- 5) Recupere o nome e a função de todos os mecânicos, e o número e o nome dos setores para os mecânicos que
-- tenham essa informação.
-- select m.nome, funcao, m.cods, s.nome FROM mecanico m LEFT JOIN setor s using (cods) 

-- 6) Recupere o nome de todos os mecânicos, e as datas dos consertos para os mecânicos que têm consertos feitos
-- (deve aparecer apenas um registro de nome de mecânico para cada data de conserto).
-- select distinct nome, c.data FROM mecanico INNER JOIN conserto c using (codm) 

-- 7) Recupere a média da quilometragem de todos os veículos dos clientes.
-- select AVG(quilometragem) FROM veiculo

-- 8) Recupere a soma da quilometragem dos veículos de cada cidade onde residem seus proprietários.
-- select cidade,SUM(quilometragem) FROM veiculo inner join cliente using(codc) GROUP BY cidade

-- 9) Recupere a quantidade de consertos feitos por cada mecânico durante o período de 12/06/2014 até 19/06/2014.
-- select nome, COUNT(*),c.data FROM mecanico join conserto c using(codm) WHERE c.data>='2014-06-12'
-- AND c.data<='2014-06-19' GROUP BY nome, c.data

-- 10) Recupere a quantidade de consertos feitos agrupada pela marca do veículo.
-- select COUNT(*), marca FROM veiculo join conserto using(codv) GROUP BY marca

-- 11) Recupere o modelo, a marca e o ano dos veículos que têm quilometragem maior que a média de quilometragem
-- de todos os veículos.
-- SELECT modelo,marca,ano FROM veiculo WHERE quilometragem>(select AVG(quilometragem) from veiculo)

-- 12) Recupere o nome dos mecânicos que têm mais de um conserto marcado para o mesmo dia.
-- SELECT distinct nome FROM (SELECT nome, COUNT(*),c.data FROM mecanico join conserto c using(codm)
		--		  GROUP BY nome, c.data) AS consertos
-- WHERE consertos.count>1
