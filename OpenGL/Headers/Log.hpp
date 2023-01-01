#pragma once

#include <filesystem>
#include <fstream>
#include <string>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

namespace Core::Debug
{
	void DebugLog(const std::string p_filename, const int p_line, const std::string p_functionName, const std::string p_log);

	#define DEBUG_LOG(p_log) Core::Debug::DebugLog(__FILENAME__ ,__LINE__, __FUNCTION__, p_log)
	
	enum class LogLevel : unsigned int
	{
		None,
		Notification,
		Test,
		Warning,
		Critical,
	};

	static class Log
	{
		// Attribute
	private:
		static std::ofstream logFile;

		// Methode
	public:
		static void OpenFile(std::filesystem::path const& p_filename);
		static void Print(const std::string& p_log, const LogLevel& p_level);
		static void CloseFile();
	};

}