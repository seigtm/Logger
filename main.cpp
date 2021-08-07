#include "logger.h"
#include <iostream>

int main()
{
  Logger logger("settings.json", Level::Debug);

  logger.write("Test message...");
  logger.write("Ну-ка встаньте цифры в ряд! {} {} {}", 5, 3, 4);
  logger.write("Integer: {}, string: {}, char: {}, boolean: {}", 255, "str", 'a', false);

  return 0;
}