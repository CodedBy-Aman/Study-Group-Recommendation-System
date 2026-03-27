from pydantic import BaseModel  #pydantic lib is used for data validation

class StudentCreate(BaseModel):  #this define what user must send example in name i entered Ram then ok but if i entered 0_123 then error
    name: str
    subject: str
    skill_level: int

class StudentResponse(StudentCreate):     # thiss defines what backend returns
    id: int

    class Config:
        from_attributes = True

#It's purpose is to defines what data is allowed in API request and responses means it checks and control incoming and outgoing data
#validate users input from frontend and send output to user
