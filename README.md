# Study Group Recommendation System

A data-driven study group matching system that pairs students based on **complementary skill gaps**. Instead of random grouping, we use the **Gale-Shapley stable matching algorithm** with a custom bid formula that rewards extreme complementarity — a strong student paired with a weak student in the same topic scores higher than two average students.

---

## The Core Idea

Most study groups fail because everyone is confused about the same topic. This system solves that by finding pairs where **Student A's strength fills Student B's weakness**, and vice versa — creating a mutual mentor-mentee loop.

**Bid formula:**
```
score(A, B) = Σ over all topics t:
    skill_A[t] × (1 - skill_B[t])    ← A can teach B
  + skill_B[t] × (1 - skill_A[t])    ← B can teach A

Final score × availability_overlap_bonus
```

A 0.9-expert paired with a 0.1-beginner scores much higher than two 0.5-mediocre students.

---

## Team

| Member | Module | Responsibilities |
|--------|--------|-----------------|
| **Amanpreet** | Algorithm · Integration | matcher.hpp, matcher.cpp (Gale-Shapley loop + stability verification), bindings.cpp (pybind11 bridge), CMakeLists.txt, end-to-end integration testing |
| **Ayush Chauhan** | Algorithm · Frontend | bid_calculator.hpp/cpp (complementarity scoring + availability overlap), index.html, register.html, results.html, app.js, style.css |
| **Mohit Khatri** | Algorithm · Backend | build_preferences() + compute_all_scores(), models.py, database.py, main.py (FastAPI), routes/students.py, routes/matches.py, test_algorithm.py |

---

## Project Structure
```
study-group-recommender/
├── algorithm/
│   ├── matcher.hpp          ← Student, MatchResult structs + GaleShapley class (Amanpreet)
│   ├── matcher.cpp          ← Gale-Shapley loop, preferences, scoring (Amanpreet + Mohit)
│   ├── bid_calculator.hpp   ← BidCalculator class declaration (Ayush)
│   ├── bid_calculator.cpp   ← Complementarity scoring formula (Ayush)
│   ├── bindings.cpp         ← pybind11 bridge: C++ → Python (Amanpreet)
│   └── CMakeLists.txt       ← Build config (Amanpreet)
├── backend/
│   ├── main.py              ← FastAPI server entry point (Mohit)
│   ├── models.py            ← Student + MatchResult data models (Mohit)
│   ├── database.py          ← SQLite setup and queries (Mohit)
│   ├── schemas.py           ← Request/response validation (Mohit)
│   └── routes/
│       ├── students.py      ← POST/GET /api/students (Mohit)
│       └── matches.py       ← POST/GET /api/match (Mohit)
├── frontend/
│   ├── index.html           ← Landing page (Ayush)
│   ├── register.html        ← Student profile form (Ayush)
│   ├── results.html         ← Match results display (Ayush)
│   └── static/
│       ├── app.js           ← API calls + UI logic (Ayush)
│       └── style.css        ← Styling (Ayush)
├── tests/
│   ├── test_algorithm.py    ← Algorithm unit tests (Mohit)
│   └── test_api.py          ← API endpoint tests
├── requirements.txt
├── setup.py
├── .gitignore
└── README.md
```

---

## Tech Stack

| Layer | Technology | Why |
|-------|-----------|-----|
| Algorithm | C++ 17 + STL | Maximum performance for Gale-Shapley, O(n²) complexity |
| Bridge | pybind11 | Exposes C++ engine to Python with zero-copy data transfer |
| Backend | Python + FastAPI | Fast to develop, clean REST API, auto-generates docs at /docs |
| Database | SQLite | Zero setup, sufficient for prototype scale |
| Frontend | HTML + CSS + JavaScript | No framework needed, simple and transparent |

---

## Interface Contract

All three modules communicate using these agreed JSON formats. **Do not rename fields without updating all modules.**

### Student Profile — Frontend → Backend
```json
{
  "id": "STU001",
  "name": "Ayush Chauhan",
  "skill_level": {
    "data_structures":   0.9,
    "operating_systems": 0.2,
    "algorithms":        0.7,
    "databases":         0.4
  },
  "availability": ["mon_9am", "wed_3pm", "fri_11am"]
}
```

### Match Result — Algorithm → Backend → Frontend
```json
{
  "matches": [
    {
      "student_a_id": "STU001",
      "student_b_id": "STU002",
      "compatibility_score": 1.44,
      "is_stable": true
    }
  ],
  "total_students": 2,
  "unmatched_students": [],
  "algorithm": "gale_shapley"
}
```

### API Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| `POST` | `/api/students` | Register a new student profile |
| `GET` | `/api/students` | Get all registered students |
| `POST` | `/api/match` | Run Gale-Shapley matching, return results |
| `GET` | `/api/match/results` | Get latest match results |

---

## How to Run

### 1. Build the C++ Algorithm
```bash
cd algorithm
mkdir build && cd build
cmake ..
make
```

### 2. Install Python Dependencies
```bash
pip install -r requirements.txt
```

### 3. Start the Backend
```bash
cd backend
uvicorn main:app --reload
```

### 4. Open the Frontend
```bash
open frontend/index.html
# or serve it:
python -m http.server 3000 --directory frontend
```

Backend runs at `http://localhost:8000` · API docs at `http://localhost:8000/docs`

---

## Algorithm — How It Works

1. **Input:** List of students with skill scores (0.0–1.0 per topic) and availability slots.
2. **Scoring:** For every pair, compute complementarity score using the bid formula.
3. **Preferences:** Each student gets a ranked list of all others sorted by compatibility score.
4. **Matching:** Gale-Shapley runs proposal rounds until all students are stably matched.
5. **Verification:** Stability check confirms no blocking pair exists.

**Time Complexity:** O(n²) — each of n students proposes to at most n−1 others.  
**Stability Guarantee:** Gale-Shapley always produces a stable matching. No student can unilaterally improve their match.

---

## Golden Rules for Contributors

> Never rename a JSON field without updating all three modules and telling the team.

- Skill scores are always decimals between `0.0` and `1.0`
- Availability slots use format `day_time` e.g. `mon_9am`
- Student IDs are always generated by the backend, never the frontend
- Base URL during development: `http://localhost:8000`
- Commit to GitHub daily with a descriptive message

---

## 9-Day Build Plan

| Day | Amanpreet | Ayush Chauhan | Mohit Khatri |
|-----|-----------|---------------|--------------|
| 1–2 | matcher.hpp, structs | bid_calculator.hpp, index.html | compute_all_scores(), models.py |
| 3–4 | matcher.cpp — run() loop | bid_calculator.cpp, register.html | build_preferences(), /api/students |
| 5–6 | verify_stability(), bindings.cpp | results.html, app.js | /api/match, schemas.py |
| 7–8 | Integration testing | UI polish, error states | test_algorithm.py, error handling |
| 9 | Full end-to-end test · Final commit · Evaluation ready (25 March) | | |

---

*PBL Phase 3 · Study Group Recommendation System · Team: Amanpreet, Ayush Chauhan, Mohit Khatri*