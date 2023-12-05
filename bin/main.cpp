#include <lib/sandpile.hpp>
#include <lib/parse_arguments.hpp>

int main(int argc, char**argv) {
	Options options;
	options.GetOptions(argc, argv);
	uint64_t** sandpile;
	setValues(sandpile, options);
	collapse(sandpile, options);
	return 0;
}
