#include "logger.h"
#include <iostream>

int main()
{
  setm::Logger::config("settings.json", setm::Level::Error);

  setm::Logger::info("Welcome, brother!");
  setm::Logger::warning("True is indeed {}", true);
  setm::Logger::error("{} equals {}", 5, "five");
  setm::Logger::debug("And this will never be shown!");

  return 0;
}
