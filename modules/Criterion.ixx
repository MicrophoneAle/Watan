export module Criterion;

import WatanTypes;

// Level of completion of a course criterion
export enum class CompletionLevel {
    None = 0,       // Not completed
    Assignment = 1, // Level 1
    Midterm = 2,    // Level 2
    Exam = 3        // Level 3
};

export class Criterion {
public:
    // id: 0..53 (vertex index). Defaults to -1 meaning "uninitialized".
    Criterion(int id = -1);

    int getId() const;
    PlayerColour getOwner() const;
    CompletionLevel getLevel() const;

    bool isOwned() const;

    // First completion: becomes Assignment and records owner.
    void complete(PlayerColour colour);

    // Upgrade Assignment -> Midterm -> Exam (no effect if already Exam or None).
    void improve();

private:
    int id;
    PlayerColour owner;
    CompletionLevel level;
};