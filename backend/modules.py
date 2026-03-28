from sqlalchemy import Column, Integer, String  #imort datatypes for table's column means column can store data in terms of integer and text..
from database import Base #import database from databae.py ...as we are using Base to create Table

class Student(Base):    # creates a class named student this represents a table called  student in database
    __tablename__ = "students"
                                ## Table student has attribute id ,nam ,subject,skill level in form of column
    id = Column(Integer, primary_key=True, index=True)   
    name = Column(String)
    subject = Column(String)
    skill_level = Column(Integer)

#The purpose of this what data will be stored and how it will be store
