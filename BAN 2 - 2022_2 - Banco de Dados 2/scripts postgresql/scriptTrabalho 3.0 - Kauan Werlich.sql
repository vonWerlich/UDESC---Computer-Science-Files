create table pessoa (
	matricula int not null,
	nome varchar(250),
	idade int,
	primary key (matricula)
);

create sequence seqmatricula;

create table professor (
	matricula int not null,
	especialidade varchar(200),
	sala varchar(15),
	foreign key (matricula) references pessoa on delete cascade on update cascade,
	primary key (matricula)
);

create table departamento (
	numDep int not null,
	nomeDep varchar(250),
	escritorioPrincipal varchar (250),
	professorLider int,
	unique(nomeDep),
	foreign key(professorLider) references professor on delete cascade on update cascade,
	primary key (numDep)
);

create sequence seqnumDep;

create table estudante (
	matricula int not null,
	tipoCurso varchar(100),
	depCurso int,
	foreign key (matricula) references pessoa on delete cascade on update cascade,
	foreign key (depCurso) references departamento on delete cascade on update cascade,
	primary key (matricula)
);

create table projeto (
	numProjeto int not null,
	orgaoFinanciador varchar(150),
	dataInicio varchar(13),
	dataTermino varchar(13),
	orcamento real,
	pesquisadorPrinc int,
	foreign key (pesquisadorPrinc) references professor on delete cascade on update cascade,
	primary key(numProjeto)
);

create sequence seqnumProjeto;

create table profDepartamento (
	matricula int not null,
	numDep int not null,
	porcentagem decimal,
	foreign key (matricula) references professor on delete cascade on update cascade,
	foreign key (numDep) references departamento on delete cascade on update cascade,
	primary key(matricula, numDep)
);

create table aconselhamento (
	matricula1 int not null,
	matricula2 int not null,
	foreign key (matricula1) references estudante on delete cascade on update cascade,
	foreign key (matricula2) references estudante on delete cascade on update cascade,
	primary key (matricula1, matricula2)
);

create table projetoEstudante (
	numProjeto int not null,
	estudante int not null,
	supervisor int not null,
	foreign key (numProjeto) references projeto on delete cascade on update cascade,
	foreign key (estudante) references estudante on delete cascade on update cascade,
	foreign key (supervisor) references professor on delete cascade on update cascade,
	primary key (numProjeto, estudante, supervisor)
);

create table projetoProfessor (
	numProjeto int not null,
	professor int not null,
	foreign key (numProjeto) references projeto on delete cascade on update cascade,
	foreign key (professor) references professor on delete cascade on update cascade,
	primary key (numProjeto, professor)
);

--------------------------------------------------------------------

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
/*
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
	 FOR EACH ROW EXECUTE PROCEDURE dataProjeto();*/
	 
-----------------------------------------------------------------------

-- trigger para verificar se um professor a ser inserido como participante em um projeto
-- não é o professor que gerencia o projeto 


CREATE OR REPLACE FUNCTION profParticipante() RETURNS TRIGGER AS
$$
DECLARE pmatricula integer;
BEGIN
	SELECT pesquisadorprinc FROM projeto WHERE new.numprojeto=numprojeto INTO pmatricula;
	IF TG_OP = 'INSERT' THEN
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
		SELECT COUNT(*) FROM projetoprofessor WHERE professor=new.pesquisadorprinc AND numprojeto=new.numprojeto INTO cont;
		IF (cont>0) THEN
			DELETE FROM projetoprofessor WHERE professor=new.pesquisadorprinc AND numprojeto=new.numprojeto;
		END IF;
	END IF;
	RETURN new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER profLider BEFORE UPDATE ON projeto
	 FOR EACH ROW EXECUTE PROCEDURE profLider();

--------------------------------------------------------------------
--Triggers para evitar que uma pessoa que seja professor e estudante ao
-- mesmo tempo na universidade seja cadastrada duas vezes em um mesmo
-- projeto (uma vez como aluno e outra como professor)

CREATE OR REPLACE FUNCTION professorDuplicado() RETURNS TRIGGER AS
$$
DECLARE cont integer;
BEGIN
	IF TG_OP = 'INSERT' THEN
		SELECT COUNT(*) FROM projetoestudante WHERE estudante=new.professor AND numprojeto=new.numprojeto INTO cont;
		IF (cont>0) THEN
			RAISE EXCEPTION 'Esse professor já está cadastrado como aluno no mesmo projeto.';
		END IF;
	END IF;
	RETURN new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER professorDuplicado BEFORE INSERT ON projetoprofessor
	 FOR EACH ROW EXECUTE PROCEDURE professorDuplicado();
	 
CREATE OR REPLACE FUNCTION alunoDuplicado() RETURNS TRIGGER AS
$$
DECLARE cont integer;
BEGIN
	IF TG_OP = 'INSERT' THEN
		SELECT COUNT(*) FROM projetoprofessor WHERE new.estudante=professor AND numprojeto=new.numprojeto INTO cont;
		IF (cont>0) THEN
			RAISE EXCEPTION 'Esse aluno já está cadastrado como professor no mesmo projeto.';
		END IF;
	END IF;
	RETURN new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER alunoDuplicado BEFORE INSERT ON projetoestudante
	 FOR EACH ROW EXECUTE PROCEDURE alunoDuplicado();
	 
CREATE OR REPLACE FUNCTION porcentagemtempo() RETURNS TRIGGER AS
$$
DECLARE cont integer;
BEGIN
	IF TG_OP = 'INSERT' THEN
		SELECT SUM(porcentagem) FROM profdepartamento WHERE new.matricula=matricula AND numdep=new.numdep INTO cont;
		cont = cont + new.porcentagem;
		IF (cont>100) THEN
			RAISE EXCEPTION 'Esse professor não pode ter carga horária maior que cem porcento';
		END IF;
	END IF;
	RETURN new;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER porcentagemtempo BEFORE INSERT OR UPDATE ON profdepartamento
	 FOR EACH ROW EXECUTE PROCEDURE porcentagemtempo();