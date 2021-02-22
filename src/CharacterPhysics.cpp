#include "CharacterPhysics.h"

using namespace glm;

CharacterPhysics::CharacterPhysics(World world, float characterHeight, vec3 startingPosition)
    : world { world }, characterHeight { characterHeight }, position { startingPosition }
{
    // Make sure the player starts on the ground.
    float heightFromTerrain { std::max(swimmingHeight + world.waterHeight, characterHeight + world.getTerrainHeightAtPosition(position)) };
    position.y = std::max(position.y, heightFromTerrain);
}

glm::vec3 CharacterPhysics::getPosition() const
{
    return position;
}

void CharacterPhysics::update(float dt)
{
    vec3 newVelocity;

    if (!inAir)
    {
        // Not jumping; set velocity to desired velocity
        newVelocity = desiredVelocity;
        newVelocity.y = prevVelocity.y;
    }
    else
    {
        newVelocity = prevVelocity;
    }

    newVelocity.y += world.gravity * dt;

    vec3 prevPosition = position;
    position += (prevVelocity + newVelocity) * 0.5f * dt; // trapezoidal approximation

    float heightFromTerrain { std::max(swimmingHeight + world.waterHeight, characterHeight + world.getTerrainHeightAtPosition(position)) };
    position.y = std::max(position.y, heightFromTerrain);

    if (abs(position.y - heightFromTerrain) < abs(world.gravity) * 0.001f)
    {
        // Jump ended
        newVelocity.y = 0;
        inAir = false;
    }
    else if (!inAir)
    {
        // Allow player to run down slope up to 45 degrees without falling
        if (prevPosition.y - heightFromTerrain < length(vec2(prevPosition.x - position.x, prevPosition.z - position.z))) 
        {
            position.y = heightFromTerrain;
        }
    }
    else
    {
        inAir = true;
    }

    prevVelocity = newVelocity;
}
void CharacterPhysics::jump(float speed)
{
    float heightFromTerrain { std::max(swimmingHeight + world.waterHeight, characterHeight + world.getTerrainHeightAtPosition(position)) };
    if (!inAir) // No double jump
    {
        prevVelocity.y = speed;
        inAir = true;
    }
}

void CharacterPhysics::setDesiredVelocity(glm::vec3 velocity)
{
    this->desiredVelocity = velocity;
}