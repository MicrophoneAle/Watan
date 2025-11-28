export module WatanTypes;

import <string>;

// Types of resources available on tiles.
export enum class ResourceType {
    Caffeine,
    Lab,
    Lecture,
    Study,
    Tutorial,
    Netflix
};

// Player colours (students)
export enum class PlayerColour {
    None,
    Blue,
    Red,
    Orange,
    Yellow
};

// Convert ResourceType to a readable string
export inline std::string toString(ResourceType r) {
    using std::string;
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

// (Optional but handy) Convert PlayerColour to string
export inline std::string toString(PlayerColour c) {
    using std::string;
    switch (c) {
    case PlayerColour::Blue:   return "Blue";
    case PlayerColour::Red:    return "Red";
    case PlayerColour::Orange: return "Orange";
    case PlayerColour::Yellow: return "Yellow";
    }
    return "Unknown";
}