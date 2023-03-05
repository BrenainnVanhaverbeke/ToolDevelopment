#include <direct.h> // _getwcwd
#include <iostream >
#include <fstream >

#include "rapidjson.h"
#include "istreamwrapper.h"
#include "document.h"

#include <windows.h>

int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
	using rapidjson::Document;
	Document jsonDoc;

	SetConsoleOutputCP(CP_UTF8);

	// Enable buffering to prevent VS from chopping
	// up UTF -8 byte sequences
	setvbuf(stdout, nullptr, _IOFBF, 1000);
	std::cout << "number of arguments :" << argc << std::endl;
	// argv [0] is the name of the executable
	// argv [1] is the filename to read.
	if (argc >= 2) {
		std::wcout << "Executable itself : " << argv[0] << std::endl;
		std::wcout << "File to read : " << argv[1] << std::endl;


		if (std::ifstream is{ argv[1] })
		{
			//std::cout << is.rdbuf() << std::endl;
			rapidjson::IStreamWrapper isw{ is };
			jsonDoc.ParseStream(isw);

			using rapidjson::Value;


			const Value& valName = jsonDoc["name"];
			const char* valString = valName.GetString();

			std::cout << "name is : " << valString << std::endl;
			return 0;
		}
		else {
			return -2;
		}
	}
	else {
		return -1; // file not found.
	}
}