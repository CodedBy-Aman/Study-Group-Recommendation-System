from sqlalchemy import create_engine  # to connect to database
from sqlalchemy.ext.declarative import declarative_base # used to create a base class for tables ,this helps us create table later
from sqlalchemy.orm import sessionmaker #used to create session (communicate with database)

DATABASE_URL = "sqlite:///./students.db" #here it is url which defines database location

engine = create_engine(DATABASE_URL, connect_args={"check_same_thread": False}) #allows multiple API calls
SessionLocal = sessionmaker(bind=engine, autoflush=False, autocommit=False) #session:-used to insert,read,update data,it will create DB sessions whenever needed
Base = declarative_base()  # it is base class for all tables means all tables will be created using this Base

#Purpose of this to connects backend to the database(SQLite)
#Without this project cannot store data so basially it is to store the data in the database
