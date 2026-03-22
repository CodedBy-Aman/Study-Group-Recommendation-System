#include "bid_calculator.hpp"
#include <algorithm>
#include <cmath>
using namespace std;

double BidCalculator::compute(const Student& a, const Student& b) const {
    double score=0.0;

    for(auto p:a.skill_level) {
        string topic=p.first;
        double skill_a=p.second;
        if(b.skill_level.find(topic)!=b.skill_level.end()) {
            double skill_b=b.skill_level.at(topic);
            score+=skill_a*(1.0-skill_b)+skill_b*(1.0-skill_a);
        }
    }
    return score*availability_overlap(a, b);
}

double BidCalculator::availability_overlap(const Student& a, const Student& b) const {
    int common_slots=0;
    for(auto slot_a:a.availability) {
        for(auto slot_b:b.availability) {
            if(slot_a==slot_b) {
                common_slots++;
                break;
            }
        }
    }
    
    if(common_slots==0)
    return 1.0;
    if(common_slots==1)
    return 1.2;
    if(common_slots==2)
    return 1.35;
    return 1.5;
}
