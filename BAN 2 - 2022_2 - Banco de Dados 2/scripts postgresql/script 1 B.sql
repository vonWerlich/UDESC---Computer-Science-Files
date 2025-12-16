create table cultura (
	id int,
	cultura varchar (150),
	periodo varchar (150),
	informacoes varchar (150),
	primary key (id)
);

create sequence id_cultura;

create table artista (
	id int,
	nome varchar (150),
	periodo varchar (150),
	paisOrigem varchar (150),
	estiloPrincipal varchar (150),
	descricao varchar (200),
	dataNasc varchar (20),
	dataMorte varchar (20),
	primary key (id)
);

create sequence id_artista;

create table objetosArte (
	numId int,
	ano int,
	titulo varchar(150),
	descricao varchar(200),
	cultura int,
	primary key (numId),
	foreign key (cultura) references cultura
);

create sequence id_objetosArte;

create table exposicao (
	id int,
	nome varchar(150),
	dataInicio varchar(150),
	dataFinal varchar(150),
	primary key (id)
);

create sequence id_exposicao;

create table escultura (
	numId int,
	peso decimal,
	altura decimal,
	estilo varchar(100),
	material varchar(100),
	foreign key (numId) references objetosArte
);

create table pintura (
	numId int,
	tipoTinta varchar (50),
	suporte varchar (150),
	estilo varchar (150),
	foreign key (numId) references objetosArte
);

create table estatuaria (
	numId int,
	peso decimal,
	altura decimal,
	estilo varchar(100),
	material varchar(100),
	foreign key (numId) references objetosArte
);

create table outros (
	numId int,
	estilo varchar(150),
	tipo varchar(150),
	foreign key (numId) references objetosArte
);

create table emprestado (
	numId int,
	dataEmp varchar (150),
	dataDev varchar (150),
	colecao varchar (150),
	foreign key (numId) references objetosArte
);

create table colecaoPermanente (
	numId int,
	expostaOuNao int, -- 1 para sim, 0 para nao
	custo decimal,
	dataAquisicao varchar(150),
	foreign key (numId) references objetosArte
);

create table outrascolecoes (
	numId int,
	nome varchar(150),
	pessoaContato varchar(150),
	Tipo varchar(150),
	endereco varchar(150),
	descricao varchar(150),
	telefone varchar(15),
	foreign key (numId) references objetosArte
);

create table objetosExpostos (
	objetoid int,
	expoid int,
	
	foreign key (objetoid) references objetosArte,
	foreign key (expoid) references exposicao
);


