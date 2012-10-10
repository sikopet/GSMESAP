--
-- PostgreSQL database dump
--

-- Dumped from database version 9.2.1
-- Dumped by pg_dump version 9.2.1
-- Started on 2012-10-10 13:42:30

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- TOC entry 181 (class 3079 OID 11727)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 1981 (class 0 OID 0)
-- Dependencies: 181
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 171 (class 1259 OID 24586)
-- Name: categoria; Type: TABLE; Schema: public; Owner: smesap_user; Tablespace: 
--

CREATE TABLE categoria (
    categoria_id integer NOT NULL,
    categoria character varying(40) NOT NULL
);


ALTER TABLE public.categoria OWNER TO smesap_user;

--
-- TOC entry 170 (class 1259 OID 24584)
-- Name: categoria_categoria_id_seq; Type: SEQUENCE; Schema: public; Owner: smesap_user
--

CREATE SEQUENCE categoria_categoria_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.categoria_categoria_id_seq OWNER TO smesap_user;

--
-- TOC entry 1982 (class 0 OID 0)
-- Dependencies: 170
-- Name: categoria_categoria_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: smesap_user
--

ALTER SEQUENCE categoria_categoria_id_seq OWNED BY categoria.categoria_id;


--
-- TOC entry 177 (class 1259 OID 24610)
-- Name: disciplina; Type: TABLE; Schema: public; Owner: smesap_user; Tablespace: 
--

CREATE TABLE disciplina (
    disciplina_id integer NOT NULL,
    disciplina character varying(40) NOT NULL
);


ALTER TABLE public.disciplina OWNER TO smesap_user;

--
-- TOC entry 176 (class 1259 OID 24608)
-- Name: disciplina_disciplina_id_seq; Type: SEQUENCE; Schema: public; Owner: smesap_user
--

CREATE SEQUENCE disciplina_disciplina_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.disciplina_disciplina_id_seq OWNER TO smesap_user;

--
-- TOC entry 1983 (class 0 OID 0)
-- Dependencies: 176
-- Name: disciplina_disciplina_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: smesap_user
--

ALTER SEQUENCE disciplina_disciplina_id_seq OWNED BY disciplina.disciplina_id;


--
-- TOC entry 179 (class 1259 OID 24618)
-- Name: professor; Type: TABLE; Schema: public; Owner: smesap_user; Tablespace: 
--

CREATE TABLE professor (
    professor_id integer NOT NULL,
    nome character varying(80) NOT NULL,
    dn date,
    reg_jur_id integer,
    situacao_id integer,
    sede_id integer,
    categoria_id integer,
    disciplina_id integer
);


ALTER TABLE public.professor OWNER TO smesap_user;

--
-- TOC entry 173 (class 1259 OID 24594)
-- Name: regime_juridico; Type: TABLE; Schema: public; Owner: smesap_user; Tablespace: 
--

CREATE TABLE regime_juridico (
    reg_jur_id integer NOT NULL,
    regime_juridico character varying(40) NOT NULL
);


ALTER TABLE public.regime_juridico OWNER TO smesap_user;

--
-- TOC entry 175 (class 1259 OID 24602)
-- Name: sede; Type: TABLE; Schema: public; Owner: smesap_user; Tablespace: 
--

CREATE TABLE sede (
    sede_id integer NOT NULL,
    sede character varying(40) NOT NULL
);


ALTER TABLE public.sede OWNER TO smesap_user;

--
-- TOC entry 169 (class 1259 OID 24578)
-- Name: situacao; Type: TABLE; Schema: public; Owner: smesap_user; Tablespace: 
--

CREATE TABLE situacao (
    situacao_id integer NOT NULL,
    situacao character varying(40) NOT NULL
);


ALTER TABLE public.situacao OWNER TO smesap_user;

--
-- TOC entry 180 (class 1259 OID 24650)
-- Name: lista_professores; Type: VIEW; Schema: public; Owner: smesap_user
--

CREATE VIEW lista_professores WITH (security_barrier=true) AS
    SELECT professor.professor_id AS cod, professor.nome, professor.dn, situacao.situacao AS sit, categoria.categoria, regime_juridico.regime_juridico AS reg_jur, sede.sede, disciplina.disciplina FROM (((((professor JOIN situacao ON ((professor.situacao_id = situacao.situacao_id))) JOIN categoria ON ((professor.categoria_id = categoria.categoria_id))) JOIN regime_juridico ON ((professor.reg_jur_id = regime_juridico.reg_jur_id))) JOIN sede ON ((professor.sede_id = sede.sede_id))) JOIN disciplina ON ((professor.disciplina_id = disciplina.disciplina_id))) ORDER BY professor.nome, professor.dn;


ALTER TABLE public.lista_professores OWNER TO smesap_user;

--
-- TOC entry 178 (class 1259 OID 24616)
-- Name: professor_professor_id_seq; Type: SEQUENCE; Schema: public; Owner: smesap_user
--

CREATE SEQUENCE professor_professor_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.professor_professor_id_seq OWNER TO smesap_user;

--
-- TOC entry 1984 (class 0 OID 0)
-- Dependencies: 178
-- Name: professor_professor_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: smesap_user
--

ALTER SEQUENCE professor_professor_id_seq OWNED BY professor.professor_id;


--
-- TOC entry 172 (class 1259 OID 24592)
-- Name: regime_juridico_reg_jur_id_seq; Type: SEQUENCE; Schema: public; Owner: smesap_user
--

CREATE SEQUENCE regime_juridico_reg_jur_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.regime_juridico_reg_jur_id_seq OWNER TO smesap_user;

--
-- TOC entry 1985 (class 0 OID 0)
-- Dependencies: 172
-- Name: regime_juridico_reg_jur_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: smesap_user
--

ALTER SEQUENCE regime_juridico_reg_jur_id_seq OWNED BY regime_juridico.reg_jur_id;


--
-- TOC entry 174 (class 1259 OID 24600)
-- Name: sede_sede_id_seq; Type: SEQUENCE; Schema: public; Owner: smesap_user
--

CREATE SEQUENCE sede_sede_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.sede_sede_id_seq OWNER TO smesap_user;

--
-- TOC entry 1986 (class 0 OID 0)
-- Dependencies: 174
-- Name: sede_sede_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: smesap_user
--

ALTER SEQUENCE sede_sede_id_seq OWNED BY sede.sede_id;


--
-- TOC entry 168 (class 1259 OID 24576)
-- Name: situacao_situacao_id_seq; Type: SEQUENCE; Schema: public; Owner: smesap_user
--

CREATE SEQUENCE situacao_situacao_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.situacao_situacao_id_seq OWNER TO smesap_user;

--
-- TOC entry 1987 (class 0 OID 0)
-- Dependencies: 168
-- Name: situacao_situacao_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: smesap_user
--

ALTER SEQUENCE situacao_situacao_id_seq OWNED BY situacao.situacao_id;


--
-- TOC entry 1952 (class 2604 OID 24589)
-- Name: categoria_id; Type: DEFAULT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY categoria ALTER COLUMN categoria_id SET DEFAULT nextval('categoria_categoria_id_seq'::regclass);


--
-- TOC entry 1955 (class 2604 OID 24613)
-- Name: disciplina_id; Type: DEFAULT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY disciplina ALTER COLUMN disciplina_id SET DEFAULT nextval('disciplina_disciplina_id_seq'::regclass);


--
-- TOC entry 1956 (class 2604 OID 24621)
-- Name: professor_id; Type: DEFAULT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY professor ALTER COLUMN professor_id SET DEFAULT nextval('professor_professor_id_seq'::regclass);


--
-- TOC entry 1953 (class 2604 OID 24597)
-- Name: reg_jur_id; Type: DEFAULT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY regime_juridico ALTER COLUMN reg_jur_id SET DEFAULT nextval('regime_juridico_reg_jur_id_seq'::regclass);


--
-- TOC entry 1954 (class 2604 OID 24605)
-- Name: sede_id; Type: DEFAULT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY sede ALTER COLUMN sede_id SET DEFAULT nextval('sede_sede_id_seq'::regclass);


--
-- TOC entry 1951 (class 2604 OID 24581)
-- Name: situacao_id; Type: DEFAULT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY situacao ALTER COLUMN situacao_id SET DEFAULT nextval('situacao_situacao_id_seq'::regclass);


--
-- TOC entry 1960 (class 2606 OID 24591)
-- Name: categoria_pkey; Type: CONSTRAINT; Schema: public; Owner: smesap_user; Tablespace: 
--

ALTER TABLE ONLY categoria
    ADD CONSTRAINT categoria_pkey PRIMARY KEY (categoria_id);


--
-- TOC entry 1966 (class 2606 OID 24615)
-- Name: disciplina_pkey; Type: CONSTRAINT; Schema: public; Owner: smesap_user; Tablespace: 
--

ALTER TABLE ONLY disciplina
    ADD CONSTRAINT disciplina_pkey PRIMARY KEY (disciplina_id);


--
-- TOC entry 1968 (class 2606 OID 24623)
-- Name: professor_pkey; Type: CONSTRAINT; Schema: public; Owner: smesap_user; Tablespace: 
--

ALTER TABLE ONLY professor
    ADD CONSTRAINT professor_pkey PRIMARY KEY (professor_id);


--
-- TOC entry 1962 (class 2606 OID 24599)
-- Name: regime_juridico_pkey; Type: CONSTRAINT; Schema: public; Owner: smesap_user; Tablespace: 
--

ALTER TABLE ONLY regime_juridico
    ADD CONSTRAINT regime_juridico_pkey PRIMARY KEY (reg_jur_id);


--
-- TOC entry 1964 (class 2606 OID 24607)
-- Name: sede_pkey; Type: CONSTRAINT; Schema: public; Owner: smesap_user; Tablespace: 
--

ALTER TABLE ONLY sede
    ADD CONSTRAINT sede_pkey PRIMARY KEY (sede_id);


--
-- TOC entry 1958 (class 2606 OID 24583)
-- Name: situacao_pkey; Type: CONSTRAINT; Schema: public; Owner: smesap_user; Tablespace: 
--

ALTER TABLE ONLY situacao
    ADD CONSTRAINT situacao_pkey PRIMARY KEY (situacao_id);


--
-- TOC entry 1970 (class 2606 OID 24629)
-- Name: professor_categoria_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY professor
    ADD CONSTRAINT professor_categoria_id_fkey FOREIGN KEY (categoria_id) REFERENCES categoria(categoria_id);


--
-- TOC entry 1973 (class 2606 OID 24644)
-- Name: professor_disciplina_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY professor
    ADD CONSTRAINT professor_disciplina_id_fkey FOREIGN KEY (disciplina_id) REFERENCES disciplina(disciplina_id);


--
-- TOC entry 1971 (class 2606 OID 24634)
-- Name: professor_reg_jur_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY professor
    ADD CONSTRAINT professor_reg_jur_id_fkey FOREIGN KEY (reg_jur_id) REFERENCES regime_juridico(reg_jur_id);


--
-- TOC entry 1972 (class 2606 OID 24639)
-- Name: professor_sede_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY professor
    ADD CONSTRAINT professor_sede_id_fkey FOREIGN KEY (sede_id) REFERENCES sede(sede_id);


--
-- TOC entry 1969 (class 2606 OID 24624)
-- Name: professor_situacao_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: smesap_user
--

ALTER TABLE ONLY professor
    ADD CONSTRAINT professor_situacao_id_fkey FOREIGN KEY (situacao_id) REFERENCES situacao(situacao_id);


--
-- TOC entry 1980 (class 0 OID 0)
-- Dependencies: 5
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2012-10-10 13:42:30

--
-- PostgreSQL database dump complete
--

