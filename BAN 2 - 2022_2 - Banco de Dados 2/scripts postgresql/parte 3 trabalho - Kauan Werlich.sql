-- função para calcular a porcentagem total que o professor trabalha em todos os departamentos
CREATE OR REPLACE FUNCTION calculaPorcentagemTempo (pmatricula int) RETURNS NUMERIC AS
$$
DECLARE porcento numeric;
BEGIN
	SELECT SUM(porcentagem) FROM (SELECT * FROM profdepartamento WHERE matricula=pmatricula) AS porcento INTO porcento;
	RETURN porcento;
END;
$$
LANGUAGE plpgsql;

-- select calculaPorcentagemTempo (0001); --teste

---------------------------------------------------------------------

-- gatilho para verificar se a data de termino de um projeto é depois da data de inicio
CREATE OR REPLACE FUNCTION dataProjeto() RETURNS TRIGGER AS
$$
BEGIN
	IF TG_OP = 'INSERT' THEN
		IF (new.datainicio>=new.datatermino) THEN
			RAISE EXCEPTION 'A data de término do projeto deve ser depois da data de início!';
		END IF;
	ELSIF TG_OP = 'UPDATE' THEN
		IF (new.datainicio>=new.datatermino) THEN
			RAISE EXCEPTION 'A data de término do projeto deve ser depois da data de início!';
		END IF;
	END IF;
	RETURN new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER dataProjeto BEFORE INSERT OR UPDATE ON projeto
	 FOR EACH ROW EXECUTE PROCEDURE dataProjeto();
	 
-----------------------------------------------------------------------

-- trigger para verificar se um professor a ser inserido como participante em um projeto
-- não é o professor que gerencia o projeto 


CREATE OR REPLACE FUNCTION profParticipante() RETURNS TRIGGER AS
$$
DECLARE pmatricula integer;
BEGIN
	IF TG_OP = 'INSERT' THEN
		SELECT pesquisadorprinc FROM projeto WHERE new.numprojeto=numprojeto INTO pmatricula;
		IF (new.professor=pmatricula) THEN
			RAISE EXCEPTION 'Esse professor não pode ser inserido como participante, pois já gerencia o projeto!';
		END IF;
	ELSIF TG_OP = 'UPDATE' THEN
		IF (new.professor=pmatricula) THEN
			RAISE EXCEPTION 'Esse professor não pode ser inserido como participante, pois já gerencia o projeto!';
		END IF;
	END IF;
	RETURN new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER profParticipante BEFORE INSERT OR UPDATE ON projetoprofessor
	 FOR EACH ROW EXECUTE PROCEDURE profParticipante();
	 
----------------------------------------------------------------------

-- trigger para evitar que a atualização do professor líder de um projeto deixe 
-- o seu registro duplicado na tabela de professores participantes, então se antes
-- de se tornar o líder ele estava nessa tabela esse registro deve ser excluído

CREATE OR REPLACE FUNCTION profLider() RETURNS TRIGGER AS
$$
DECLARE cont integer;
BEGIN
	IF TG_OP = 'UPDATE' THEN
		SELECT COUNT(*) FROM projetoprofessor WHERE professor=new.pesquisadorprinc INTO cont;
		IF (cont>0) THEN
			DELETE FROM projetoprofessor WHERE professor=new.pesquisadorprinc;
		END IF;
	END IF;
	RETURN new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER profLider BEFORE UPDATE ON projeto
	 FOR EACH ROW EXECUTE PROCEDURE profLider();
