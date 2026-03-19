// bid_calculator.hpp
// iska kaam hai do students ke beech compatibility score calculate karna
// simple logic hai — jahan A strong hai aur B weak hai
// wahan A, B ko teach kar sakta hai, aur vice versa
// isliye dono ka combination best study pair banta hai

#pragma once
#include "matcher.hpp"

// -----------------------------------------------
// BidCalculator class
// isko ek simple scoring machine samjho
// do students do, score milega
// -----------------------------------------------

class BidCalculator {
public:

    // main scoring function
    // formula: skill_A[t] * (1 - skill_B[t]) + skill_B[t] * (1 - skill_A[t])
    // ye calculation har topic ke liye hoti hai
    // phir sab add ho jaate hain
    // jitna zyada score, utna zyada complementary pair hai
    double compute(const Student& a, const Student& b) const;

    // ye check karta hai kitne common free slots hain dono ke beech
    // agar dono kabhi free hi nahi hain ek saath
    // toh best match hone ka bhi koi fayda nahi
    // returns a multiplier:
    //   1.0  = koi common slot nahi (no bonus)
    //   1.2  = 1 common slot
    //   1.35 = 2 common slots
    //   1.5  = 3 ya zyada common slots (best bonus)
    double availability_overlap(const Student& a, const Student& b) const;
};
