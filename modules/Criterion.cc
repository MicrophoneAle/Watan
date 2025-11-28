module Criterion;

import WatanTypes;

Criterion::Criterion(int id)
    : id{ id },
    // owner value is irrelevant when level == None
    owner{ PlayerColour::Blue },
    level{ CompletionLevel::None } {
}

int Criterion::getId() const {
    return id;
}

PlayerColour Criterion::getOwner() const {
    return owner;
}

CompletionLevel Criterion::getLevel() const {
    return level;
}

bool Criterion::isOwned() const {
    return level != CompletionLevel::None;
}

void Criterion::complete(PlayerColour colour) {
    if (!isOwned()) {
        owner = colour;
        level = CompletionLevel::Assignment;
    }
    // If already owned, we silently ignore here; higher-level logic
    // (Game/Board) should prevent illegal double completion.
}

void Criterion::improve() {
    if (level == CompletionLevel::Assignment) {
        level = CompletionLevel::Midterm;
    }
    else if (level == CompletionLevel::Midterm) {
        level = CompletionLevel::Exam;
    }
    // If None or Exam, nothing happens. Higher-level logic
    // should enforce legal improves.
}