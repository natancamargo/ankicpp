#pragma once

#include <cstdint>
#include <string>
#include <vector>
namespace ankicpp {
class ConfigDTO {
public:
  std::string KEY;
  std::int64_t usn;
  std::int64_t mtime_secs;
  std::vector<unsigned char> val;

  static std::vector<ConfigDTO> createDTOs() {
    std::vector<ConfigDTO> configDTOs;

    ConfigDTO configDTO;

    configDTO.KEY = "activeDecks";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.insert(configDTO.val.end(), {'[', '1', ']'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "addToCur";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'t', 'r', 'u', 'e'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "collapseTime";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'1', '2', '0', '0'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "creationOffset";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'1', '8', '0'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "curDeck";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'1'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "curModel";
    configDTO.usn = -1;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'0'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "dayLearnFirst";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'f', 'a', 'l', 's', 'e'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "dueCounts";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'t', 'r', 'u', 'e'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "estTimes";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'t', 'r', 'u', 'e'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "newSpread";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'0'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "nextPos";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'1'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "sched2021";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'t', 'r', 'u', 'e'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "schedVer";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'2'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "sortBackwards";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'f', 'a', 'l', 's', 'e'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "sortType";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(),
                         {'"', 'n', 'o', 't', 'e', 'F', 'l', 'd', '"'});
    configDTOs.push_back(configDTO);

    configDTO.KEY = "timeLim";
    configDTO.usn = 0;
    configDTO.mtime_secs = 0;
    configDTO.val.clear();
    configDTO.val.insert(configDTO.val.end(), {'0'});
    configDTOs.push_back(configDTO);

    return configDTOs;
  }
};
} // namespace ankicpp
