from fastapi import FastAPI  # import FastAPI framework ..tool to create backend server
import models               #import module file so that table can be created means bring database table structure
from database import engine  # bring database connections
from routes import students, matches   # import API route files to handels student data(students.py) handles matching logic(matches.py)

models.Base.metadata.create_all(bind=engine)   #create tables in database if does not exists then create taable else do nothing...

app = FastAPI()    #start backend aap

app.include_router(students.router, prefix="/api")   # .student becomes api_student  means add student APIs to app
app.include_router(matches.router, prefix="/api")   # connect match api same as above line

@app.get("/")              #to check weatherb it is working or not
def home():
    return {"message": "Study Group Recommender API is running"}

#It is the important one(main)  of backend which connects everything togather starts the FastAPI server
#Basically it connnects all API's and run backend
