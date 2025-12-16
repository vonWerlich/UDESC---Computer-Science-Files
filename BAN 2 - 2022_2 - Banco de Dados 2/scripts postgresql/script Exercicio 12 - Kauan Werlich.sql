--1) Crie um índice para cada uma das chaves estrangeiras presentes do esquema de dados.
create index idx_conserto_codm on conserto using hash(codm);
create index idx_conserto_codv on conserto using hash(codv);
create index idx_mecanico_cods on mecanico using hash(cods);
create index idx_veiculo_codc on veiculo using hash(codc);

--2) Crie um índice para acelerar a busca dos mecânicos pela função.
create index idx_espec on mecanico using btree(funcao);
	--ou
create index idx_espec on mecanico using hash(funcao);
	--ou  => pode usar hash por ser busca por igualdade
create index idx_espec on mecanico using btree(substr(funcao,1,5));

--3) Crie um índice para acelerar a ordenação dos consertos pela data e hora.
create index idx_datahora on conserto using btree(data,hora);

--4) Crie um índice para acelerar a busca de clientes pelo cpf.
create index idx_cpf on cliente using btree(cpf);

--5) Crie um índice para acelerar a busca pelas primeiras 5 letras do nome dos clientes.
create index idx_nome on cliente using hash(substr(nome,1,5));
	-- ou
create index idx_nome on cliente using btree(substr(nome,1,5));

--6) Crie um índice para acelerar a busca dos clientes com CPF com final XXX.XXX.XXX-55.
create index idx_cpf55 on cliente using btree(cpf) where cpf like '%55';
	--ou
create index idx_cpf55 on cliente using btree(cpf) where cpf like '___.___.___-55';
