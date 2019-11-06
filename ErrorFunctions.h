#pragma once
#include <string>

void OnError(int err, std::string msg = "");
void MessageBoxStr(std::string msg);
void MessageBoxStream(std::stringstream msg);