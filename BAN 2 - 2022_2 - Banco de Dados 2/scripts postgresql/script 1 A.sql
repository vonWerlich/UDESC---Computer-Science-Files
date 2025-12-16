create table estilo (
	id int,
	nomeEstilo varchar (150),
	primary key (id)
);

create sequence id_estilo;

create table artista (
	id int,
	nome varchar(100),
	nacionalidade varchar(100),
	id_estilo int,
	primary key (id),
	foreign key (id_estilo) references estilo
);

create sequence id_artista;

create table midia (
	id int,
	tipo int, -- 1 para fita, 2 para vinil
	numMusicas int,
	nmFita int,
	id_artista int,
	primary key (id),
	foreign key (id_artista) references artista
);

create sequence id_midia;

create table categoria (
	codigo int,
	nomeCategoria varchar (150),
	primary key (codigo)
);

create sequence id_categoria;

create table filme (
	id int,
	titulo varchar(150),
	id_categoria int,
	primary key (id),
	foreign key (id_categoria) references categoria
);

create sequence id_filme;

create table ator (
	id int,
	nomeArtistico varchar(150),
	nomeReal varchar(150),
	dataNasc varchar(150),
	primary key (id)
);

create sequence id_ator;

create table cliente (
	id int,
	nome varchar (150),
	sobrenomenome varchar (150),
	telefone varchar (15),
	endereco varchar (200),
	primary key (id)
);

create sequence id_cliente;


create table emprestimo (

	numeroMidia int,
	numeroCliente int,
	dataInicio varchar(150),
	dataFim varchar(150),

	foreign key (numeroMidia) references midia,
	foreign key (numeroCliente) references cliente
);

create table filmefita (
	id_fita int,
	id_filme int,

	foreign key (id_fita) references midia,
	foreign key (id_filme) references filme
);

create table estrelas (
	id_ator int,
	id_filme int,

	foreign key (id_ator) references ator,
	foreign key (id_filme) references filme
);



