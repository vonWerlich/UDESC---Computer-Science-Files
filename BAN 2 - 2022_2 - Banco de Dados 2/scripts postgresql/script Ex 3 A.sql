Create Table setor (
	cods int,
	nome varchar(150),
	primary key (cods)
);

create sequence id_setor;

Create Table cliente (
	codc int,
	cpf char(11) unique,
	nome varchar(150),
	idade int,
	endereco varchar(200),
	cidade varchar(150),
	primary key (codc)
);

create sequence id_cliente;

Create Table mecanico (
	codm int,
	cpf char(11) unique,
	nome varchar(150),
	idade int,
	endereco varchar(200),
	cidade varchar(150),
	funcao varchar(150),
	cods int references setor on delete set null on update cascade, --se o setor ao qual ele
--referencia for deletado, seta o valor para zero, e se for atualizado, atualiza o valor também
	primary key (codm)
);

Create Table veiculo (
	codv int,
	renavam char(11) unique,
	modelo varchar (100),
	marca varchar(100),
	ano int,
	quilometragem int,
	codc int,
	primary key (codv),
	foreign key (codc) references cliente
);

Create Table conserto (
	codm int,
	codv int,
	dataconserto varchar (15),
	hora varchar (15),
	primary key (codm, codv, dataconserto)
);