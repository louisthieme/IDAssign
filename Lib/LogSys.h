#include <iostream>
#include <vector>
#include <cstdarg>
#include <fstream>
#include <streambuf>
#include <string>

#pragma once

namespace lsys
{
	class Log
	{
		// For logging
		std::string const NAMESPACE { "lsys" };
		std::string const CLASS		{ "Log" };

		size_t const LOG_RETURN_SUCCES	{ 0 };
		size_t const LOG_RETURN_ERROR	{ 1 };
	
		std::vector<std::string> Log_VecLogMsg {};

		size_t MaxTempSize	{1024};
		std::string Temp	{};

		public:

			const std::string NO_PREFIX		{ "" };
			const std::string WARNING		{ "WARNING: " };
			const std::string ERROR			{ "ERROR: " };
			const std::string INFO			{ "INFO: " };

			size_t MaxLenght {1000};

			size_t				SetTemp(std::string sTemp);
			void				ClearTemp() { Temp.clear(); }
			std::string const	GetTemp() { return Temp; }

			size_t			Add(std::string LogMsg);
			size_t			Add(std::string PreFix, std::string LogMsg);
			size_t			AddFunction(std::string PreFix, std::string Function, std::string LogMsg);
			size_t			AddClass(std::string PreFix, std::string Class, std::string Function, std::string LogMsg);
			size_t			AddNameSpace(std::string PreFix, std::string NameSpace, std::string Class, std::string Function, std::string LogMsg);

			size_t			DeleteLastLog();
			size_t			DeleteLog();
			size_t const	ShowLastLogMsg();
			size_t const	ShowAll(std::string NameSpace, std::string Class);

			size_t			Write_To_File(std::string FileName);
			size_t			Append_To_File(std::string FileName);
			
			std::vector<std::string> Get() { return Log_VecLogMsg; }

			~Log() 
			{ 
				Temp.clear(); 
			}
	};
}