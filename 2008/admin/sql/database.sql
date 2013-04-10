
CREATE TABLE material
(
	cod_material serial primary key,
	nome varchar(64) not null,
	densidade double precision not null
) without OIDS;

CREATE TABLE tipo
(
	cod_tipo serial primary key,
	nome varchar(64) not null

) without OIDS;

CREATE TABLE especie
(
	cod_especie serial primary key,
	nome varchar(64) not null
) without OIDS;

CREATE TABLE materialespecie
(
	cod_materialespecie serial primary key,
	nome varchar(64) not null
) without OIDS;

CREATE TABLE materiaprima
(
	cod_materiaprima serial primary key,
	nome varchar(128) not null,
	cod_material integer references material(cod_material),
	cod_materialespecie integer references materialespecie(cod_materialespecie),
	tipo integer not null,
	qualidade varchar(64) not null,
	preco double precision,
	pesolinear double precision,
	var1 double precision,
	var2 double precision,
	var3 double precision,
	var4 double precision,
	var5 double precision
) without OIDS;

CREATE TABLE programas
(
	cod_programa serial primary key,
	nome varchar(128) not null,
	programa text
) without OIDS;

CREATE TABLE pecas
(
	cod_peca serial primary key,
	nome varchar(128) not null,
	preco double precision
) without OIDS;

CREATE TABLE materiaprimapecas
(
	cod_materiaprimapecas serial primary key,
	cod_peca integer references pecas(cod_peca),
	cod_materiaprima integer references materiaprima(cod_materiaprima),
	quantidade integer
) without OIDS;

CREATE TABLE programaspecas
(
	cod_programaspecas serial primary key,
	cod_programa integer references programas(cod_programa),
	cod_peca integer references pecas(cod_peca)
) without OIDS;

CREATE TABLE desenhos
(
	cod_desenho serial primary key,
	nome varchar(128) not null,
	desenho bytea
) without OIDS;

CREATE TABLE desenhopecas
(
	cod_desenhopeca serial primary key,
	cod_desenho integer references desenhos(cod_desenho),
	cod_peca integer references pecas(cod_peca)
) without OIDS;

CREATE TABLE pessoas
(
	cod_pessoa serial primary key,
	nome varchar(128) not null
) without OIDS;

CREATE TABLE clientes
(
	cod_cliente serial primary key,
	cod_pessoa integer references pessoas(cod_pessoa)
) without OIDS;

CREATE TABLE fornecedores
(
	cod_fornecedor serial primary key,
	cod_pessoa integer references pessoas(cod_pessoa)
) without OIDS;

CREATE TABLE orcamentos
(
	cod_orcamento serial primary key
) without OIDS;

CREATE TABLE orcamentopecas
(
	cod_orcamentopeca serial primary key,
	cod_orcamento integer references orcamentos(cod_orcamento),
	cod_peca integer references pecas(cod_peca)
) without OIDS;

