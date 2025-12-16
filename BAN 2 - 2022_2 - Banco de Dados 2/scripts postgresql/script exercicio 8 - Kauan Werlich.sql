/*
Nota: Para a implementação dos gatilhos devem ser utilizadas as funções
implementadas no exercício 7, quando possível. Considerando o BD de uma oficina
mecânica desenvolvido nas últimas aulas (e disponível na página da disciplina),
faça a especificação dos seguintes gatilhos em PostgreSQL:
*/

-- 1) Gatilho para impedir a inserção ou atualização de Clientes com o mesmo CPF.
-- Onde: Cliente | Quando: Before | Operações: Insert ou Update | Nível: Each Row

create or replace function verificaCpf() returns trigger as
$$
begin
	IF TG_OP = 'INSERT' THEN
		IF (SELECT 1 FROM cliente WHERE cpf=new.cpf and codc<>new.codc) THEN
			RAISE EXCEPTION 'Cliente com cpf repetido!';
		END IF;
	ELSIF TG_OP = 'UPDATE' THEN
		IF (old.cpf<>new.cpf)THEN
			IF (SELECT 1 FROM cliente WHERE cpf=new.cpf and codc<>new.codc) THEN
				RAISE EXCEPTION 'Cliente com cpf repetido!';
			END IF;
		END IF;
	END IF;
	return new;
end;
$$
language plpgsql;

-- teste: update cliente set nome = 'Fabiano' where codc=7


CREATE TRIGGER verificaCpf BEFORE INSERT OR UPDATE ON cliente
	FOR EACH ROW EXECUTE PROCEDURE verificaCpf();

-- 2) Gatilho para impedir a inserção ou atualização de Mecânicos com idade menor que 20 anos.

CREATE OR REPLACE FUNCTION verificaMecanico() RETURNS TRIGGER AS
$$
BEGIN
	IF TG_OP = 'INSERT' THEN
		IF (new.idade<20) THEN
			RAISE EXCEPTION 'Novo mecânico é muito jovem!';
		END IF;
	ELSIF TG_OP = 'UPDATE' THEN
		IF ((old.idade<>new.idade)&&(new.idade<20)) THEN
			RAISE EXCEPTION 'O mecânico atualizado é muito jovem!';
		END IF;
	END IF;
	return new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER verificaIdadeMecanico BEFORE INSERT OR UPDATE ON mecanico
	FOR EACH ROW EXECUTE PROCEDURE verificaMecanico();

-- 3) Gatilho para atribuir um cods (sequencial) para um novo setor inserido.
CREATE SEQUENCE novo_cods start 10;

CREATE OR REPLACE FUNCTION novo_cods() RETURNS TRIGGER AS
$$
BEGIN
	new.cods := nextval('novo_cods');
	return new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER novo_cods BEFORE INSERT ON setor
	FOR EACH ROW EXECUTE PROCEDURE novo_cods();

-- 4) Gatilho para impedir a inserção de um mecânico ou cliente com CPF inválido.
CREATE OR REPLACE FUNCTION validarCpf(pcpf varchar(11)) RETURNS bool AS
$$
DECLARE 
cpf integer[11];
charcpf char(11);
sequencia1 integer[] default array [10,9,8,7,6,5,4,3,2];
sequencia2 integer[] default array [11,10,9,8,7,6,5,4,3,2];
pdigito integer[9];
sdigito integer[10];
somapdigito integer default 0;
somasdigito integer default 0;
cont integer default 0;
resto integer;
digito integer;

BEGIN
		FOR cont IN 1..11 LOOP
			cpf[cont] := CAST(substring(pcpf from cont for 1) AS integer);
		END LOOP;
		-- Verifica 1º Dígito
		FOR cont in 1..9 LOOP
			pdigito[cont] := cpf[cont] * sequencia1[cont];
			somapdigito := somapdigito + pdigito[cont];
		END LOOP;
		resto := somapdigito % 11;
		IF resto < 2 THEN
			digito := 0;
		ELSE
			digito := 11 - resto;
		END IF;
		IF digito <> cpf[10] THEN
			RAISE EXCEPTION 'CPF Inválido!';
		END IF;
		-- Verifica 2º Dígito 
		FOR cont in 1..10 LOOP
			sdigito[cont] := cpf[cont] * sequencia2[cont];
			somasdigito := somasdigito + sdigito[cont];
		END LOOP;
		resto := somasdigito % 11;
		IF resto < 2 THEN
			digito := 0;
		ELSE
			digito := 11 - resto;
		END IF;
		IF digito <> cpf[11] THEN
			RAISE EXCEPTION 'CPF Inválido!';
		END IF;
		RETURN true;
END;
$$
LANGUAGE PLPGSQL;

CREATE OR REPLACE FUNCTION verificaCpf() RETURNS TRIGGER AS 
$$
BEGIN
	if (not (validarCpf(new.cpf))) then
		RAISE EXCEPTION 'CPF inválido';
	end if;
	return new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER verificaCpf1 BEFORE INSERT OR UPDATE ON mecanico
	FOR EACH ROW EXECUTE PROCEDURE verificaCpf();
	
CREATE TRIGGER verificaCpf2 BEFORE INSERT OR UPDATE ON cliente
	FOR EACH ROW EXECUTE PROCEDURE verificaCpf();

-- 5) Gatilho para impedir que um mecânico seja removido caso não exista outro mecânico com a mesma função.
CREATE OR REPLACE FUNCTION removeMecanico() RETURNS TRIGGER AS
$$
BEGIN
	IF (SELECT COUNT(*) FROM mecanico WHERE funcao=new.funcao) <= 1 THEN
		RAISE EXCEPTION 'Esse é o único mecânico com essa função!';
	end if;
	return new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER removeMecanico BEFORE DELETE ON mecanico
	FOR EACH ROW EXECUTE PROCEDURE removeMecanico();
	

-- 6) Gatilho que ao inserir, atualizar ou remover um mecânico, reflita as mesmas modificações na tabela de Cliente.
-- Em caso de atualização, se o mecânico ainda não existir na tabela de Cliente, deve ser inserido.

CREATE OR REPLACE FUNCTION atualizaMecCli() RETURNS TRIGGER AS
$$
BEGIN
	IF TG_OP = 'INSERT' THEN
		INSERT INTO cliente VALUES (nextval('cliente_codc_seq'), new.cpf, new.nome, new.idade, new.endereco, new.cidade);
	ELSIF TG_OP = 'UPDATE' THEN
		IF (SELECT 1 FROM cliente WHERE cpf = new.cpf) THEN
			UPDATE cliente set nome = new.nome, idade = new.idade, endereco = new.endereco, cidade = new.cidade where cpf = new.cpf;
		ELSE
			INSERT INTO cliente VALUES (nextval('cliente_cod_seq'), new.cpf, new.nome, new.idade, new.endereco, new.cidade);
		END IF;
	ELSIF TG_OP = 'DELETE' THEN
		DELETE FROM cliente where cpf = old.cpf;
	END IF;
	RETURN null;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER atualizaMecCli AFTER INSERT OR UPDATE OR DELETE ON mecanico
	 FOR EACH ROW EXECUTE PROCEDURE atualizaMecCli();
	 
	 
-- 7) Gatilho para impedir que um conserto seja inserido na tabela Conserto se o mecânico já realizou mais de 20
-- horas extras no mês.

CREATE OR REPLACE FUNCTION calculaHorasExtras(pcodm int, mes int, ano int) RETURNS INT AS
$$
DECLARE
vHoras int default 0;
sql text;
diasMes int[] default array [31,28,31,30,31,30,31,31,30,31,30,31];
BEGIN
	sql := 'select count(1) from conserto c where c.codm = ' ||pcodm||
	' and c.data between '||'''01/'||mes||'/'||ano||''''||' and '||''''||
	diasMes[mes]||'/'||mes||'/'||ano||'''';
	RAISE notice 'SQL = %', sql;
	EXECUTE SQL INTO vHoras;
	RAISE NOTICE 'vHoras = %', vHoras;
	IF vHoras <= 160 THEN
		RETURN 0;
	ELSE
		RETURN vHoras - 160;
	END IF;
END;
$$
LANGUAGE plpgsql;

--select calculaHorasExtras(1,6,2014)

CREATE OR REPLACE FUNCTION verificaHoraExtra() RETURNS TRIGGER AS
$$
DECLARE mes int; ano int;
BEGIN
	mes := date_part('month', new.data);
	ano := date_part('year', new.data);
	IF (calculaHorasExtras(new.codm,mes,ano) > 20) THEN
		RAISE EXCEPTION 'O funcionário excedeu a quantidade de horas extras no mês.';
	END IF;
	RETURN NEW;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER verificaHoraExtra BEFORE INSERT OR UPDATE ON conserto
	FOR EACH ROW EXECUTE PROCEDURE verificaHoraExtra();

-- 8) Gatilho para impedir que mais de 1 conserto seja agendado no mesmo setor na mesma hora. 

CREATE OR REPLACE FUNCTION verificaHorario() RETURNS TRIGGER AS
$$
BEGIN
	IF (SELECT COUNT(1) FROM conserto JOIN mecanico USING (codm) WHERE data=new.data and hora=new.hora GROUP BY cods) > 0 THEN
		RAISE EXCEPTION 'Setor já tem conserto agendado para esta data e hora';
	END IF;
	RETURN NEW;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER verificaHorario BEFORE INSERT OR UPDATE ON conserto 
	FOR EACH ROW EXECUTE PROCEDURE verificaHorario();
