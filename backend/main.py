from fastapi import FastAPI
import models
from database import engine
from routes import students, matches

models.Base.metadata.create_all(bind=engine)

app = FastAPI()

app.include_router(students.router, prefix="/api")
app.include_router(matches.router, prefix="/api")

@app.get("/")
def home():
    return {"message": "Study Group Recommender API is running"}