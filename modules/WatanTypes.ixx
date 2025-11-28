export module WatanTypes;

import <string>;

export enum class ResourceType {
    Caffeine,
    Lab,
    Lecture,
    Study,
    Tutorial,
    Netflix
};

export enum class PlayerColour {
    Blue,
    Red,
    Orange,
    Yellow
};

// Convert ResourceType to a readable string
export inline std::string toString(ResourceType r) {
    switch (r) {
    case ResourceType::Caffeine: return "Caffeine";
    case ResourceType::Lab:      return "Lab";
    case ResourceType::Lecture:  return "Lecture";
    case ResourceType::Study:    return "Study";
    case ResourceType::Tutorial: return "Tutorial";
    case ResourceType::Netflix:     return "Netflix";
    }
    return "Unknown";
}
