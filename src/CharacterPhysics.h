#pragma once
#include "ofMain.h"
#include "World.h"

// A class for handling a character affected by gravity.
class CharacterPhysics
{
public:
    // Initializes an instance by copying a World with it's parameters and pointer to a heightmap, 
    // and specifying the height of the character and their starting position.
    CharacterPhysics(World world = {}, float characterHeight = 1.0f, glm::vec3 startingPosition = glm::vec3(0));

    // This function advances time by dt for the character, 
    // updating the character velocity and position appropriately.  
    void update(float dt);

    // Gets the position of the character’s head.
    glm::vec3 getPosition() const;

    // If the character is on the ground, this function increases the y-velocity so that they jump into the air.  
    // If the character is not on the ground, this function does nothing (no double-jumping).
    void jump(float speed);

    // Sets the character's intended velocity in world space.
    void setDesiredVelocity(glm::vec3 velocity);

private:
    World world;
    float characterHeight;
    float swimmingHeight { 0.1f * characterHeight };

    glm::vec3 position;
    bool inAir { false };
    glm::vec3 desiredVelocity { 0 };
    glm::vec3 prevVelocity { 0 };
};