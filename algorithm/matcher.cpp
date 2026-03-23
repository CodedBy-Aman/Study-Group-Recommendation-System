// matcher.cpp
// isme Gale-Shapley algorithm implement kiya hai
// har student propose karta hai jab tak sab ka match nahi ho jaata
// saare structs matcher.hpp mai  hain

#include "matcher.hpp"
#include "bid_calculator.hpp"
#include <algorithm>
#include <queue>
#include <stdexcept>


//Constructor:   students ki list store kar lo

GaleShapley::GaleShapley(const std::vector<Student>& students)
    : students_(students) {
    // kam se kam 2 students toh chahiye match karne ke liye
    if (students_.size() < 2)
        throw std::invalid_argument("kam se kam 2 students chahiye matching ke liye");
}

// compute_all_scores
// har possible pair ke beech compatibility score nikalta hai
// Ayush ka BidCalculator use karta hai score ke liye
//
// key format: "id_a:id_b" — alphabetically sorted
// taaki A:B aur B:A alag alag store na ho

std::unordered_map<std::string, double>
GaleShapley::compute_all_scores() {
    std::unordered_map<std::string, double> scores;
    BidCalculator calc;

    // har pair ek baar hi calculate karo — i < j se duplicate avoid hota hai
    for (size_t i = 0; i < students_.size(); ++i) {
        for (size_t j = i + 1; j < students_.size(); ++j) {
            std::string key = students_[i].id + ":" + students_[j].id;
            scores[key] = calc.compute(students_[i], students_[j]);
        }
    }
    return scores;
}
