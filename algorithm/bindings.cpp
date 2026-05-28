#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "matcher.hpp"

namespace py = pybind11;

PYBIND11_MODULE(matcher_bindings, m) {
    m.doc() = "pybind11 bridge connecting the Python backend with the C++ Gale-Shapley engine";

    py::class_<Student>(m, "Student")
        .def(py::init<>())
        .def_readwrite("id", &Student::id)
        .def_readwrite("name", &Student::name)
        .def_readwrite("skill_level", &Student::skill_level)
        .def_readwrite("availability", &Student::availability);

    py::class_<MatchResult>(m, "MatchResult")
        .def(py::init<>())
        .def_readwrite("student_a_id", &MatchResult::student_a_id)
        .def_readwrite("student_b_id", &MatchResult::student_b_id)
        .def_readwrite("compatibility_score", &MatchResult::compatibility_score)
        .def_readwrite("is_stable", &MatchResult::is_stable);

    m.def("run_match", [](const std::vector<Student>& students) {
        return GaleShapley(students).run();
    }, "Run the Gale-Shapley matching engine on a list of students");

    m.def("verify_stability", [](const std::vector<Student>& students,
    const std::vector<MatchResult>& results) {
        return GaleShapley(students).verify_stability(results);
    }, "Verify whether the produced matching is stable");
}
