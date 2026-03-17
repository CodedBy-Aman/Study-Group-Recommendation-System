// matcher.hpp
// ye file basically poora algorithm ka backbone hai
// isme humne saare data structures define kiye hain
// jaise Student kaisa dikhega, match result kaisa hoga etc.
// baaki sab files isi file ko include karengi

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

// -----------------------------------------------
// Student struct
// ek student ka poora data yahan store hoga
// -----------------------------------------------

// skill_level mein hum store karte hain ki student
// kis topic mein kitna strong ya weak hai
// example: { "data_structures": 0.9, "os": 0.2 }
// 0.0 matlab bilkul nahi aata, 1.0 matlab expert hai

struct Student {
    std::string id;    // unique id jaise STU001
    std::string name;  // student ka naam

    // topic -> score (0.0 to 1.0)
    std::unordered_map<std::string, double> skill_level;

    // free time slots jaise ["mon_9am", "wed_3pm"]
    std::vector<std::string> availability;
};

// -----------------------------------------------
// CompatibilityScore struct
// do students ke beech compatibility score store karta hai
// ye score Ayush ka bid_calculator calculate karega
// -----------------------------------------------

struct CompatibilityScore {
    std::string student_a_id;
    std::string student_b_id;

    // jitna zyada score, utna better match
    double score;
};

// -----------------------------------------------
// MatchResult struct
// algorithm run hone ke baad final output yahi hoga
// Java backend is result ko JSON mein convert karega
// -----------------------------------------------

struct MatchResult {
    std::string student_a_id;
    std::string student_b_id;

    double compatibility_score; // Ayush ke formula se aata hai

    // is_stable = true matlab koi blocking pair nahi hai
    // matlab koi bhi student apna match improve nahi kar sakta
    bool is_stable;
};

// -----------------------------------------------
// GaleShapley class
// ye main algorithm hai jo sab kuch handle karta hai
//
// kaise kaam karta hai:
// 1. har student ek preference list banata hai
//    (sabse compatible student pehle)
// 2. proposal rounds chalta hai
//    har free student apni list ke next person ko propose karta hai
// 3. jab tak sab match nahi ho jaate tab tak chalta hai
// 4. end mein verify karta hai ki matching stable hai ya nahi
// -----------------------------------------------

class GaleShapley {
public:
    // constructor mein simply students ki list de do
    explicit GaleShapley(const std::vector<Student>& students);

    // run() call karo aur matched pairs ki list milegi
    // time complexity: O(n^2) — n students, n-1 proposals each
    std::vector<MatchResult> run();

    // ye check karta hai ki koi blocking pair toh nahi hai
    // blocking pair = do students jo dono ek dusre ko
    // apne current match se zyada prefer karte hain
    // agar true aaya toh matching stable hai
    bool verify_stability(const std::vector<MatchResult>& results);

private:
    std::vector<Student> students_;

    // har student ki preference list banata hai
    // sorted by compatibility score (highest first)
    std::unordered_map<std::string, std::vector<std::string>> build_preferences();

    // sabke beech pairwise compatibility calculate karta hai
    // Mohit ne ye function implement kiya hai matcher.cpp mein
    std::unordered_map<std::string, double> compute_all_scores();
};