// WatanTypes.ixx
export module WatanTypes;
import <string>;

// Types of resources available on tiles.
export enum class ResourceType {
    Caffeine = 0,
    Lab = 1,
    Lecture = 2,
    Study = 3,
    Tutorial = 4,
    Netflix = 5
};

// Player colours (students)
export enum class PlayerColour {
    None = 0,    // IMPORTANT: Added None for unowned criteria/goals
    Blue = 1,
    Red = 2,
    Orange = 3,
    Yellow = 4
};

// Convert ResourceType to a readable string
export inline std::string toString(ResourceType r) {
    switch (r) {
    case ResourceType::Caffeine: return "CAFFEINE";
    case ResourceType::Lab:      return "LAB";
    case ResourceType::Lecture:  return "LECTURE";
    case ResourceType::Study:    return "STUDY";
    case ResourceType::Tutorial: return "TUTORIAL";
    case ResourceType::Netflix:  return "NETFLIX";
    }
    return "UNKNOWN";
}

// Convert PlayerColour to string
export inline std::string toString(PlayerColour c) {
    switch (c) {
    case PlayerColour::None:   return "None";
    case PlayerColour::Blue:   return "Blue";
    case PlayerColour::Red:    return "Red";
    case PlayerColour::Orange: return "Orange";
    case PlayerColour::Yellow: return "Yellow";
    }
    return "Unknown";
}
