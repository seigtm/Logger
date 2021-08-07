#include "logger.h"

int main()
{
  Logger logger("settings.json", Level::Info);

  logger.write("Test message...");
  logger.write("Three integers! {} {} {}", 5, 3, 4);
  logger.write("Integer: {}, string: {}, char: {}, boolean: {}", 255, "str", 'a', false);

  return 0;
}
