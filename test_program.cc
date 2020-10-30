#include "classes/common_init.hh"
#include "classes/command_line_tools.hh"

#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

void PrintUsage()
{
	printf("USAGE: program <option> <option>");
	printf("OPTIONS:");
	printf("    -cfg <file>       config file");
	printf("    -dgn <string>     diagonal");
}

//----------------------------------------------------------------------------------------------------

int main(int argc, const char **argv)
{
	// defaults
	string cfg_file = "config.py";
	string diagonal_input = "";

	// parse command line
	// TODO: update
	for (int argi = 1; (argi < argc) && (cl_error == 0); ++argi)
	{
		if (strcmp(argv[argi], "-h") == 0 || strcmp(argv[argi], "--help") == 0)
		{
			cl_error = 1;
			continue;
		}

		if (TestStringParameter(argc, argv, argi, "-cfg", cfg_file)) continue;
		if (TestStringParameter(argc, argv, argi, "-dgn", diagonal_input)) continue;

		printf("ERROR: unknown option '%s'.\n", argv[argi]);
		cl_error = 1;
	}

	if (cl_error)
	{
		PrintUsage();
		return 1;
	}

	// run initialisation
	if (Init(cfg_file, diagonal_input) != 0)
		return 2;

	return 0;
}
