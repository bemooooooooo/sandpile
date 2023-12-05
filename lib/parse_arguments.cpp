#include "parse_arguments.hpp"

Options::Options() {
	tsv_filename = nullptr;
	output_directory = "0";
	max_iterations = INT64_MAX;
	frequency = 0;
	x = NULL;
	y = NULL;
}

Options::~Options() {}

void Options::ErrorHandler(char* Error) {
	std::cerr << Error;
	exit(EXIT_FAILURE);
}

void Options::GetTVSFilename(int argc, char** arg, int& iter) {
	char* pEnd = nullptr;
	const char* short_option = "-i";
	const char* long_option = "--input=";
	if (!strcmp(arg[iter], short_option) && iter + 1 < argc)
	{
		if (arg[iter + 1] == pEnd) {
			ErrorHandler("The -i and --input arguments are not provided with data");
		}
		tsv_filename = arg[iter + 1];
		++iter;
	}
	else if (!strncmp(arg[iter], long_option, len_TVS_filename)) {
		if (arg[iter] + len_TVS_filename == pEnd) {
			ErrorHandler("The -i and --input arguments are not provided with data");
		}
		tsv_filename = arg[iter] + len_TVS_filename;
	}
}

void Options::GetOutputDirectory(int argc, char** arg, int& iter) {
	char* pEnd = nullptr;
	const char* short_option = "-o";
	const char* long_option = "--output=";
	if (!strcmp(arg[iter], short_option) && iter + 1 < argc) {
		if (arg[iter + 1] == pEnd) {
			ErrorHandler("The -0 and --output arguments are not provided with data");
		}
		output_directory = arg[iter + 1];
		++iter;
	}
	else if (!strncmp(arg[iter], long_option, len_output_directory)) {
		if (arg[iter] + len_output_directory == pEnd) {
			ErrorHandler("The -o and --output arguments are not provided with data");
		}
		output_directory = arg[iter] + len_output_directory;
	}
}

void Options::GetMaxIterations(int argc, char** arg, int& iter) {
	char* pEnd = nullptr;
	const char* short_option = "-m";
	const char* long_option = "--max-iter=";
	int64_t check = 0;
	errno = 0;
	if (!strcmp(arg[iter], short_option) && iter + 1 < argc) {
		check = strtol(arg[iter + 1], &pEnd, 10);
		++iter;
		if (arg[iter + 1] == pEnd || errno == ERANGE) {
			ErrorHandler("The -m and --max-iter arguments are not provided with data");
		}
		max_iterations = check;
	}
	else if (!strncmp(arg[iter], long_option, len_max_iterations)) {
		check = _strtoi64(arg[iter] + len_max_iterations, &pEnd, 10);
		if (arg[iter] + len_max_iterations == pEnd || errno == ERANGE) {
			ErrorHandler("The -m and --max-iter arguments are not provided with data");
		}
		max_iterations = check;
	}
}

void Options::GetFrequency(int argc, char** arg, int& iter) {
	char* pEnd = nullptr;
	const char* short_option = "-f";
	const char* long_option = "--freq=";
	int64_t check = 0;
	errno = 0;
	if (!strcmp(arg[iter], short_option) && iter + 1 < argc) {
		check = strtol(arg[iter + 1], &pEnd, 10);
		++iter;
		if (arg[iter + 1] == pEnd || errno == ERANGE) {
			ErrorHandler("The -f and --freq arguments are not provided with data");
		}
		frequency = check;
	}
	else if (!strncmp(arg[iter], long_option, len_frequency)) {
		check = strtol(arg[iter] + len_frequency, &pEnd, 10);
		if (arg[iter] + len_frequency == pEnd || errno == ERANGE) {
			ErrorHandler("The -f and --freq arguments are not provided with data");
		}
		frequency = check;
	}
}

void Options::GetGridSize() {
	if (tsv_filename != nullptr) {
		in.open(tsv_filename);
		int16_t x_max = 0;
		int16_t y_max = 0;
		int16_t x_min = 0;
		int16_t y_min = 0;
		int16_t x_new;
		int16_t y_new;
		uint64_t value;
		while (!in.eof()) {
			in >> x_new >> y_new >> value;

			x_max = std::max(x_max, x_new);
			x_min = std::min(x_max, x_new);
			y_max = std::max(y_max, y_new);
			y_min = std::min(y_min, y_new);
		}
		x = abs(x_max) - abs(x_min);
		y = abs(y_max) - abs(y_min);
	}
}


void Options::GetOptions(int argc, char** argv) {
	for (int i = 1; i < argc; ++i) {
		GetTVSFilename(argc, argv, i);
		GetOutputDirectory(argc, argv, i);
		GetMaxIterations(argc, argv, i);
		GetFrequency(argc, argv, i);
		GetGridSize();
	}
}
