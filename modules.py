import sys
import os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from sqlalchemy import Column, Integer, String
from database import Base

class Student(Base):
    __tablename__ = "students"

    id = Column(Integer, primary_key=True, index=True)
    name = Column(String)
    subject = Column(String)
    skill_level = Column(Integer)