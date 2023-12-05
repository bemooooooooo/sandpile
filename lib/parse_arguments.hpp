#pragma once
#include <iostream>
#include <fstream>
#include <string>

struct Options
{
	char* tsv_filename;
	std::string output_directory;
	int64_t max_iterations;
	int64_t frequency;
	int16_t x;
	int16_t y;

	Options();
	~Options();

	void GetOptions(int argc, char** argv);

private:

	const static int len_TVS_filename = 8;
	const static int len_output_directory = 9;
	const static int len_max_iterations = 11;
	const static int len_frequency = 7;

	std::ifstream in;

	void ErrorHandler(char* Error);
	void GetTVSFilename(int argc, char** arg, int& iter);
	void GetOutputDirectory(int argc, char** arg, int& iter);
	void GetMaxIterations(int argc, char** arg, int& iter);
	void GetFrequency(int argc, char** arg, int& iter);
	void GetGridSize();
};
