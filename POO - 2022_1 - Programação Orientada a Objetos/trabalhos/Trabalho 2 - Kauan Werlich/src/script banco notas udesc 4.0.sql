create table semestre (
	id int,
	nomesemestre varchar(100),
	primary key (id)
);

create sequence id_semestre;

create table disciplina (
	id int,
	nomedisciplina varchar(100),
	primary key (id)
);

create sequence id_disciplina;

--tabela que relaciona disciplina com semestre
create table disciplinasemestre (
	id_semestre int,
	id_disciplina int,
	foreign key (id_semestre) references semestre,
	foreign key (id_disciplina) references disciplina
);

create table aluno (
	id int,
	matricula int,
	nomealuno varchar (150),
	primary key (id)
);

create sequence id_aluno;

--tabela que relaciona o aluno com uma disciplina de um semestre
create table alunodisciplinasemestre (
	id_aluno int,
	id_disciplina int,
	id_semestre int,
	foreign key (id_aluno) references aluno,
	foreign key (id_disciplina) references disciplina,
	foreign key (id_semestre) references semestre
);

create table avaliacao (
	id int,
	nomeavaliacao varchar(50),
	dataavaliacao varchar(30),
	peso decimal,
	id_disciplina int,
	id_semestre int,
	primary key (id),
	foreign key (id_disciplina) references disciplina,
	foreign key (id_semestre) references semestre
);

create sequence id_avaliacao;

--tabela que relaciona um aluno com uma avaliacao
create table alunoavaliacao (
	id_aluno int,
	id_avaliacao int,
	nota decimal,
	foreign key (id_aluno) references aluno,
	foreign key (id_avaliacao) references avaliacao
);