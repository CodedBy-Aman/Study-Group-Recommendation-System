from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
from database import SessionLocal
import models

router = APIRouter()

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

@router.get("/match")
def match_students(db: Session = Depends(get_db)):
    students = db.query(models.Student).all()
    matches = []
    used = set()

    for i in range(len(students)):
        if i in used:
            continue

        best_match = -1
        best_score = -1

        for j in range(i + 1, len(students)):
            if j in used:
                continue
            if students[i].subject != students[j].subject:
                continue

            score = abs(students[i].skill_level - students[j].skill_level)

            if score > best_score:
                best_score = score
                best_match = j

        if best_match != -1:
            matches.append({
                "student1": students[i].name,
                "student2": students[best_match].name,
                "score": best_score
            })
            used.add(i)
            used.add(best_match)

    return matches