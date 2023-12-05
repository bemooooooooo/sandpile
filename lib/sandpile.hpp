#include "bmp.hpp"
#include "my_container.hpp"
#include "parse_arguments.hpp"

void setValues(uint64_t**& sandpile, Options& options);

bool isCollapsePossible(uint64_t** &sandpile, Options& options);

void collapse(uint64_t**& sandpile, Options& options);

void resize(uint64_t**& arr, Options& options);
