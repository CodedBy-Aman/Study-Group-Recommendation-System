#the purpose of this file is :This file allows frontend/user to send and retrieve student data ad Connect frontend to backend

#This file is used to add students and see students.


from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
from database import SessionLocal
import models, schemas

router = APIRouter()

# DB connection
def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

# Add student
@router.post("/students")
def add_student(student: schemas.StudentCreate, db: Session = Depends(get_db)):
    new_student = models.Student(
        name=student.name,
        subject=student.subject,
        skill_level=student.skill_level
    )
    db.add(new_student)
    db.commit()
    db.refresh(new_student)
    return new_student

# Get all students
@router.get("/students")
def get_students(db: Session = Depends(get_db)):
    return db.query(models.Student).all()