
-- database already exists

\c :dbname 

CREATE DOMAIN  String4VarName AS VARCHAR(30) ;
CREATE DOMAIN  String4Info as VARCHAR(200) ;

CREATE domain Password as varchar(30);

--CREATE DOMAIN DomainEmail AS VARCHAR(255)
  --CHECK (VALUE ~* '^[A-Za-z0-9._%+-]+@example\.com$');

--CREATE DOMAIN DomainPhone AS VARCHAR(20)
  --CHECK (VALUE ~ '^(\+\d{1,3}\s?)?(\(\d{1,4}\)|\d{1,4})[-.\s]?\d{1,10}[-.\s]?\d{1,10}$');

CREATE DOMAIN DomainCap AS VARCHAR(5);

CREATE TYPE DomainStatus AS ENUM ('available', 'unavailable');

CREATE TYPE ShippingStatus AS ENUM ('pendant', 'delivering', 'delivered');


CREATE TABLE IF NOT EXISTS Customer (
        id serial PRIMARY KEY,
        username String4VarName NOT NULL,
        password Password NOT NULL, 
        email String4Info NOT NULL,
        shipping_address String4Info NOT NULL;
);

CREATE TABLE IF NOT EXISTS Vendor (
        id serial PRIMARY KEY,
        username String4VarName UNIQUE NOT NULL,
        password Password NOT NULL, 
        email String4Info UNIQUE NOT NULL
);


CREATE TABLE IF NOT EXISTS Insertion (
        id serial PRIMARY KEY,
        product String4Info,
        price real NOT NULL,
        instant TIMESTAMP DEFAULT now(),
        insertion_status DomainStatus DEFAULT 'available',
        vendor INTEGER REFERENCES Vendor(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS orders (
        id serial PRIMARY KEY,
        product INTEGER REFERENCES Insertion(id) ON DELETE SET NULL,
        quantity INTEGER NOT NULL,
        customer INTEGER REFERENCES Customer(id) ON DELETE SET NULL,
        instant_date TIMESTAMP DEFAULT now(),
        assigned BOOLEAN DEFAULT FALSE

);

CREATE TABLE IF NOT EXISTS Transporter (
        id serial PRIMARY KEY,
        username String4Info NOT NULL,
        email String4Info NOT NULL,
        password String4Info NOT NULL
);


CREATE TABLE IF NOT EXISTS Shipping (
        id serial PRIMARY KEY,
        id_order INTEGER REFERENCES orders(id) ON DELETE CASCADE,
        transporter INTEGER REFERENCES Transporter(id) ON DELETE SET NULL,
        shipping_status ShippingStatus DEFAULT 'pendant',
        delivered  TIMESTAMP
);
