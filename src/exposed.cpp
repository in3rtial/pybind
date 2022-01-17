#include <pybind11/pybind11.h>
#include <string_view>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

struct Pet {
    Pet(const std::string &name_) : name(name_) { }
    std::string name;
};

struct Dog : Pet {
    Dog(const std::string &name_) : Pet(name_) { }
    std::string bark() const { return "woof!"; }
};

bool getNextLine(std::string_view& line, std::string_view& rest) {
    if(rest.empty()) {
        return false;
    }

    const size_t position = rest.find('\n');
    if(position == rest.npos) {
        line = rest;
        rest = {};
    }
    else {
        line = rest.substr(0, position);
        rest = rest.substr(position+1);
    }

    return true;
}


size_t lineCounter(const std::string_view chars) {
    std::string_view line;
    std::string_view rest = chars;
    size_t count = 0;
    while(getNextLine(line, rest)) {
        ++count;
    }
    return count;
}

PYBIND11_MODULE(exposed, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("add", &add, "A function that adds two numbers");

    m.def("linecount", &lineCounter, "A function to read bytes and return the number of lines");

py::class_<Pet>(m, "Pet")
   .def(py::init<const std::string &>())
   .def_readwrite("name", &Pet::name);

// Method 1: template parameter:
py::class_<Dog, Pet /* <- specify C++ parent type */>(m, "Dog")
    .def(py::init<const std::string &>())
    .def("bark", &Dog::bark);
}
