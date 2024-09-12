
\c :dbname postgres

-- user already exists
GRANT ALL PRIVILEGES ON DATABASE :dbname to :username ;

ALTER TABLE Customer OWNER TO :username ;

ALTER TABLE Vendor OWNER TO :username ;

ALTER TABLE Insertion OWNER TO :username ;

ALTER TABLE orders OWNER TO :username ;

ALTER TABLE Transporter OWNER TO :username ;

ALTER TABLE Shipping OWNER TO :username ;

-- grant all privileges on all tables in schema public to :username ;
-- grant all privileges on all sequences in schema public to :username ;

GRANT ALL ON SCHEMA public TO :username ;
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO :username ;
