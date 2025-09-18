create table cliente (
	id int,
	nomecliente varchar(100),
	telefone varchar(15),
	primary key (id)
);

create sequence id_cliente;

create table imovel (
	id int,
	area decimal,
	preco decimal,
	descricao varchar (200),
	cep varchar (15),
	primary key (id)
);

create sequence id_imovel;

create table proprietario (
	id int,
	nomeprop varchar (100),
	telefone varchar (15),
	primary key (id)
);

create sequence id_proprietario;

create table imovelproprietario (
	id_imovel int,
	id_proprietario int,
	foreign key (id_imovel) references imovel,
	foreign key (id_proprietario) references proprietario
);

create table compra (
	id_imovel int,
	id_cliente int,
	id int,
	datacompra varchar (15),
	foreign key (id_imovel) references imovel,
	foreign key (id_cliente) references cliente,
	primary key (id)
);

create sequence id_compra;

create table aluguel (
	id_imovel int,
	id_cliente int,
	id int,
	datainicio varchar (15),
	datatermino varchar (15),
	foreign key (id_imovel) references imovel,
	foreign key (id_cliente) references cliente,
	primary key (id)
);

create sequence id_aluguel;

