#include "settings.hpp"
#include "nlohmann/json.hpp"
#include <filesystem>
#include <fstream>
#include <globals.hpp>

#include <nexus/Nexus.h>

using json = nlohmann::json;
namespace Settings
{
json json_settings;
std::mutex mutex;
std::filesystem::path settings_path;


void load()
{
    json_settings = json::object();
    if (!std::filesystem::exists(settings_path)) {
        return;
    }

    {
        std::lock_guard lock(mutex);
        try {
            if (std::ifstream file(settings_path); file.is_open()) {
                json_settings = json::parse(file);
                file.close();
            }
        } catch (json::parse_error &ex) {
            api->Log(ELogLevel_WARNING, addon_name, "settings.json could not be parsed.");
            api->Log(ELogLevel_WARNING, addon_name, ex.what());
        }
    }
    // if (!json_settings[SETTING].is_null())
    //     json_settings[SETTING].get_to(variable);
    api->Log(ELogLevel_INFO, addon_name, "settings loaded!");
}

void save()
{
    if (!std::filesystem::exists(settings_path.parent_path())) {
        std::filesystem::create_directories(settings_path.parent_path());
    }
    {
        std::lock_guard lock(mutex);
        if (std::ofstream file(settings_path); file.is_open()) {
            file << json_settings.dump(1, '\t') << std::endl;
            file.close();
        }
        api->Log(ELogLevel_INFO, addon_name, "settings saved!");
    }
}
} // namespace Settings
