#include "logger.h"
#include <iostream>

int main()
{
  Logger::config("settings.json", Level::Error);

  Logger::info("Info test");       // должно сработать.
  Logger::warning("Warning test"); // должно сработать.
  Logger::error("Error test");     // должно сработать.
  Logger::debug("Debug test");     // не должно сработать.

  return 0;
}