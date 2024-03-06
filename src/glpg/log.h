#pragma once

#include <string>

namespace glpg::log {

void info(const std::string& text);
void warn(const std::string& text, bool colored = true);
void error(const std::string& text, bool colored = true);
void success(const std::string& text, bool colored = true);

} // glpg::log
