create table aluno (
	cpf char(11),
	nome varchar(100),
	rua varchar(225),
	numero int,
	estado char(2),
	cidade varchar(100),
	cep int,
	primary key (cpf)
);

create table curso (
	sigla_curso char(10),
	nome varchar(100),
	titulacao varchar(100),
	primary key (sigla_curso)
);

create table disciplina (
	sigla_disc char(10),
	nome varchar(100),
	carga_horaria int,
	primary key (sigla_disc)
);

create table professor (
	reg_mec int,
	nome varchar(100),
	rua varchar(225),
	numero int,
	cidade varchar(100),
	estado char(2),
	cep int,
	primary key (reg_mec)
);

create table area (
	cod_area int,
	descricao varchar(100),
	primary key (cod_area)
);

create table responsavel (
	reg_mec int references professor on delete cascade on update cascade,
	cod_area int references area on delete cascade on update cascade,
	ate date,
	primary key (reg_mec, cod_area)
);

create table grade (
	sigla_curso char(10) references curso on delete cascade on update cascade,
	sigla_disc char(10) references disciplina on delete cascade on update cascade,
	primary key (sigla_curso, sigla_disc)
);

create table requisito (
	sigla_curso_req char(10),
	sigla_disc_req char(10),
	sigla_curso char(10),
	sigla_disc char(10),
	primary key (sigla_curso_req, sigla_disc_req, sigla_curso, sigla_disc),
	foreign key (sigla_curso_req,sigla_disc_req) references grade on delete cascade on update cascade,
	foreign key (sigla_curso, sigla_disc) references grade on delete cascade on update cascade
);

create table inscricao (
	matricula int primary key,
	sigla_curso char(10) references curso on delete cascade on update cascade,
	cpf char(11) references aluno on delete cascade on update cascade
);

create table matricula (
	ano date,
	matricula int references inscricao on delete cascade on update cascade,
	sigla_disc char(10) references disciplina on delete cascade on update cascade,
	semestre int,
	primary key (ano, matricula, sigla_disc, semestre)
);

create table leciona (
	sigla_disc char(10) references disciplina on delete cascade on update cascade,
	reg_mec int references professor on delete cascade on update cascade,
	ano date,
	semestre int,
	primary key (sigla_disc, reg_mec, ano, semestre)
);

create table habilitacao (
	sigla_disc char(10) references disciplina on delete cascade on update cascade,
	reg_mec int references professor on delete cascade on update cascade,
	primary key (sigla_disc, reg_mec)
);

create table titulo (
	reg_mec int references professor on delete cascade on update cascade,
	cod_area int references area on delete cascade on update cascade,
	data_da_titulacao date,
	primary key (reg_mec, cod_area, data_da_titulacao)
);
