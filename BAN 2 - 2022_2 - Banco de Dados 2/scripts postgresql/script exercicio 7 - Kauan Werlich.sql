/*Considerando o BD de uma oficina mecânica desenvolvido nas últimas aulas
(e disponível na página da disciplina), faça a especificação das seguintes
funções em PostgreSQL. OBS.: para chamar a função, faça um querry usando
SELECT nome_da_funcao(parametros)  */

-- 1) Função para inserção de um mecânico.
/*CREATE OR REPLACE FUNCTION inserir_mecanico(codm int, cpf char(11), nome
varchar(50), idade int, endereco varchar(500), cidade  varchar(500), 
funcao varchar(50), cods int) RETURNS void AS
$$
INSERT INTO mecanico values (codm,cpf,nome,idade,endereco,cidade,funcao,cods);
$$
LANGUAGE SQL;*/

-- 2) Função para exclusão de um mecânico.
/*CREATE OR REPLACE FUNCTION excluir_mecanico(pcodm int) RETURNS void AS
$$
DELETE FROM mecanico WHERE codm=pcodm
$$
LANGUAGE SQL;*/

-- 3) Função única para inserção, atualizar e exclusão de um cliente.
/*
CREATE OR REPLACE FUNCTION cliente(op char, pcodc int, pcpf 
char(11), pnome varchar(50), pidade int, pendereco varchar(500), pcidade 
varchar(500)) RETURNS int AS
$$
-- I:insercao, D:deletar, U:update
DECLARE
	linhas int;
BEGIN
	IF UPPER(op) = 'I' THEN
		INSERT INTO cliente values (pcodc,cpf,nome,idade,endereco,cidade);
	ELSIF UPPER(op) = 'D' THEN
		DELETE FROM cliente WHERE codc=pcodc;
	ELSIF UPPER(op) = 'U' THEN
		UPDATE cliente SET codc=pcodc, cpf=pcpf,nome=pnome,idade=pidade,endereco=pendereco,cidade=pcidade;
	END IF;
	GET DIAGNOSTICS linhas = row_count;
	return linhas;
END
$$
LANGUAGE plpgsql;
*/

-- 4) Função que limite o cadastro de no máximo 10 setores na oficina mecânica.
/*
CREATE OR REPLACE FUNCTION cadastraSetor (pcods int, pnome varchar(50)) RETURNS void AS
$$
DECLARE
		quantSetor int;
BEGIN
	SELECT COUNT(*) setor INTO quantSetor;
	IF quantSetor > 10 THEN
		RAISE EXCEPTION 'Já alcançou a quantidade máxima de setores';
	END IF;
	INSERT INTO setor VALUES (pcods,pnome);
END;
$$
LANGUAGE plpgsql;
*/

-- 5) Função que limita o cadastro de um conserto apenas se o mecânico tiver
-- mais de 3 consertos agendados para o mesmo dia.
/*
CREATE OR REPLACE FUNCTION cadastra_conserto (pcodm int, pcodv int, pdata date,
											 phora time) RETURNS void AS
$$
DECLARE totalconsertos int default 0;
BEGIN
	totalconsertos := (SELECT COUNT(*) FROM conserto WHERE codm=pcodm AND data=pdata);
	IF (totalconsertos>=3) THEN
		RAISE EXCEPTION 'O mecânico já tem 3 consertos marcados para esse dia';
	ELSIF (totalconsertos<3) THEN 
		INSERT INTO conserto values(pcodm,pcodv,pdata,phora);
	END IF;
END;
$$
LANGUAGE plpgsql;
--select cadastra_conserto(2,4,'2014-06-13','9:00:00');
*/

-- 6) Função para calcular a média geral de idade dos Mecânicos e Clientes.
/*
CREATE OR REPLACE FUNCTION calculaMediaMecCli () RETURNS FLOAT AS
$$
DECLARE vidade int default 0;
		somaidade int default 0;
		resultado float default 0;
		quant int default 0;
BEGIN
	FOR vidade IN SELECT idade from mecanico LOOP
		somaidade := somaidade + vidade;
		quant := quant + 1;
	END LOOP;
	FOR vidade IN SELECT idade FROM cliente LOOP
		somaidade := somaidade + vidade;
		quant := quant + 1;
	END LOOP;
	resultado := somaidade / quant;
	RETURN resultado;
END
$$
LANGUAGE plpgsql;
*/

-- 7) Função única que permita fazer a exclusão de um Setor, Mecânico, Cliente ou Veículo.
/*
CREATE OR REPLACE FUNCTION excluiSetor(chave varchar, valor int) returns 
void AS
$$
BEGIN
	EXECUTE 'delete from setor where ' ||chave|| ' = ' ||valor;
END;
$$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION excluiMecanico(chave varchar, valor int) returns 
void AS
$$
BEGIN
	EXECUTE 'delete from mecanico where ' ||chave|| ' = ' ||valor;
END;
$$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION excluiCliente(chave varchar, valor int) returns 
void AS
$$
BEGIN
	EXECUTE 'delete from cliente where ' ||chave|| ' = ' ||valor;
END;
$$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION excluiVeiculo(chave varchar, valor int) returns 
void AS
$$
BEGIN
	EXECUTE 'delete from veiculo where ' ||chave|| ' = ' ||valor;
END;
$$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION alteraBD(nomeTabela varchar, chave varchar,valor int)
RETURNS void AS
$$
BEGIN
	IF UPPER(nomeTabela) = 'SETOR' THEN
		execute excluiSetor(chave,valor);
	ELSIF UPPER(nomeTabela) = 'MECANICO' THEN 
		execute excluiMecanico(chave,valor);
	ELSIF UPPER(nomeTabela) = 'CLIENTE' THEN 
		execute excluiCliente(chave,valor);
	ELSIF UPPER(nomeTabela) = 'VEICULO' THEN 
		execute excluiVeiculo(chave,valor);
	END IF;
END
$$
LANGUAGE plpgsql;

-- select alteraBD('setor', 'cods', 1); -- excluir setor com cods=1.
*/

-- 8) Considerando que na tabela Cliente apenas codc é a chave primária, faça uma
-- função que remova clientes com CPF repetido, deixando apenas um cadastro para cada CPF.
-- Escolha o critério que preferir para definir qual cadastro será mantido: aquele com a
-- menor idade, que possuir mais consertos agendados, etc. Para testar a função, não se
-- esqueça de inserir na tabela alguns clientes com este problema.

/*
CREATE OR REPLACE FUNCTION removerRepetidos() RETURNS void AS
$$
BEGIN
DELETE FROM
   cliente a
        USING cliente b
WHERE
    a.codc < b.codc
    AND a.cpf = b.cpf;
END;
$$
LANGUAGE PLPGSQL;

--select removerRepetidos();
*/

-- 9) Função para calcular se o CPF é válido*.
/*
CREATE OR REPLACE FUNCTION validarCpf(cpf varchar(11)) RETURNS bool AS $$
DECLARE	x real default 0;
		y real; 
		soma integer default 0;
		dig1 integer default 0;
		dig2 integer default 0;
		len integer;
		cont integer default 0; 
		val_cpf varchar(11);
BEGIN
	IF char_length(cpf) = 11 THEN
	ELSE
		RAISE EXCEPTION 'CPF menor que o esperado';
		RETURN false;
	END IF;

	val_cpf := $1;
	len := char_length(val_cpf);
	x := len -1;

	cont :=1;
	WHILE cont <= (len - 2) LOOP
		y := CAST(substring(val_cpf from cont for 1) AS NUMERIC);
		soma := soma + ( y * x);
		x := x - 1;
		cont := cont +1;
	END LOOP;
	dig1 := 11 - CAST((soma % 11) AS INTEGER);
	if (dig1 = 10) THEN dig1 :=0 ; END IF;
	if (dig1 = 11) THEN dig1 :=0 ; END IF;

	-- Dígito 2
	x := 11; soma :=0;
	cont :=1;
	WHILE cont <= (len-1) LOOP
		soma := soma + CAST((substring(val_cpf FROM cont FOR 1)) AS REAL) * x;
		x := x - 1;
		cont := cont +1;
	END LOOP;
	dig2 := 11 - CAST ((soma % 11) AS INTEGER);
	IF (dig2 = 10) THEN dig2 := 0; END IF;
	IF (dig2 = 11) THEN dig2 := 0; END IF;
	--Teste do CPF
	IF ((dig1 || '' || dig2) = substring(val_cpf FROM len-1 FOR 2)) THEN
	RETURN true;
	ELSE
		RAISE EXCEPTION 'DV do CPF Inválido1';
	RETURN false;
	END IF;
END;
$$ LANGUAGE PLPGSQL;
--select validarCpf('11111222233');
*/

-- 10) Função que calcula a quantidade de horas extras de um mecânico em um mês de trabalho.
-- O número de horas extras é calculado a partir das horas que excedam as 160 horas de
-- trabalho mensais. O número de horas mensais trabalhadas é calculada a partir dos consertos
-- realizados. Cada conserto tem a duração de 1 hora.
/*
CREATE OR REPLACE FUNCTION horasextras(pcodm int,pdata date) RETURNS int AS 
$$
DECLARE	totalhoras int default 0;
BEGIN
	totalhoras := (SELECT COUNT(*) FROM conserto WHERE month(pdata)=month(data) AND year(pdata)=year(data));
	IF (totalhoras <= 160) THEN
		RETURN 0;
	ELSE 
		RETURN totalhoras-160;
	END IF;
END;
$$ 
LANGUAGE PLPGSQL;
*/

