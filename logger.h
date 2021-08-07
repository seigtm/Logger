#include "nlohmann/json.hpp"
#include "fmt/core.h"
#include "fmt/chrono.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <string>
#include <iostream>

enum class Level
{
  Info,
  Warning,
  Error,
  Debug
};

enum class OutputType
{
  File,
  Console
};

namespace std
{
  using L = Level;
  string to_string(const Level &level)
  {
    switch (level)
    {
    case L::Info:
      return "[Info]";
    case L::Warning:
      return "[Warning]";
    case L::Error:
      return "[Error]";
    case L::Debug:
      return "[Debug]";
    }

    return "[INVALID LEVEL]";
  }
}

class Logger
{
public:
  Logger(const std::string &pathToJSON = "settings.json",
         const Level &level = Level::Debug)
      : mLevel{level}
  {
    std::ifstream jsonFile(pathToJSON);

    // If JSON File not opened.
    if (!jsonFile)
    {
      return;
    }

    // Parse JSON data from file.
    auto json{nlohmann::json::parse(jsonFile)};

    // If logger disabled.
    if (!json[0]["enable"])
    {
      return;
    }

    // Get info about whether datetime needs to be printed.
    mIsDateTimePrinting = json[0]["datetime"]["print"];

    // If datetime needs to be printed by logger.
    if (mIsDateTimePrinting)
    {
      // Get format of datetime.
      mDateTimeFormat = json[0]["datetime"]["format"].get<std::string>();
    }

    // Get output type (where the log should be written).
    std::string outputType = json[0]["output"]["format"].get<std::string>();

    // If it's file.
    if (outputType.find("file") != std::string::npos)
    {
      mOutputType = OutputType::File;
      std::stringstream filePathString;
      filePathString << json[0]["output"]["path"].get<std::string>()
                     // << getDateTime(mDateTimeFormat)
                     << ".log";

      mOutputFilePath = filePathString.str();
    }
    // If it's console.
    else if (outputType.find("console") != std::string::npos)
    {
      mOutputType = OutputType::Console;
    }
    else
    {
      // static_assert("");
    }
  }

  ~Logger()
  {
  }

  template <typename... Args>
  void write(const std::string &format, Args... args);

private:
  std::string getDateTime(const std::string &format)
  {
    if (format.empty())
    {
      return {};
    }

    return fmt::format("[" + format + "]", fmt::localtime(time(nullptr)));
  }

  void _write(const std::string &message)
  {
    switch (mOutputType)
    {
    case OutputType::Console:
      std::cout << message;
      break;

    case OutputType::File:
      std::ofstream outputFile(mOutputFilePath, std::ios::app);
      outputFile << message;
      outputFile.close();
      break;
    }
  }

  Level mLevel;
  OutputType mOutputType;

  bool mIsDateTimePrinting;
  std::string mDateTimeFormat;

  std::string mOutputFilePath;
};

template <class... Args>
void Logger::write(const std::string &format, Args... args)
{
  std::stringstream logRecord;
  logRecord << getDateTime(mDateTimeFormat)
            << " "
            << std::to_string(mLevel)
            << " "
            << fmt::format(format, args...)
            << "\n";

  auto str = logRecord.str();

  _write(str);
}

template <>
void Logger::write(const std::string &message)
{
  std::stringstream logRecord;
  logRecord << getDateTime(mDateTimeFormat)
            << " "
            << std::to_string(mLevel)
            << " "
            << message
            << "\n";

  auto str = logRecord.str();

  _write(str);
}