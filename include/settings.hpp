#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <mutex>
#include <nlohmann/json.hpp>

namespace Settings
{

void load();
void save();

extern nlohmann::json json_settings;
extern std::filesystem::path settings_path;
extern std::mutex mutex;
} // namespace Settings

#endif // SETTINGS_HPP
