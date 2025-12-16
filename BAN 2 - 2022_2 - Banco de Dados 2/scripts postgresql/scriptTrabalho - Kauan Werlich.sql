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
	dataInicio date,
	dataTermino date,
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



