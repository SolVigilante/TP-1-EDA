/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H
#include <raylib.h>

/**
 * @brief Orbital body definition
 */
struct OrbitalBody
{
    // Fill in your code here...
    const char *name; // Name
    double mass;		  // [kg]
    double radius;	  // [m]
    Color color;	  // Raylib color
    Vector3 position; // [m]
    Vector3 velocity; // [m/s]
    Vector3 acceleration; //[m/s^2]
    Vector3 FGravity; //[N]
    bool asteroid;
};

/**
 * @brief Orbital simulation definition
 */
struct OrbitalSim
{
    // Fill in your code here...
    float timestep;
    float timestart;
    int bodynum;
    OrbitalBody  * bodys;


};

OrbitalSim *constructOrbitalSim(float timeStep, int bodynum, OrbitalBody *initialBodies);
void destroyOrbitalSim(OrbitalSim *sim);
void updateOrbitalSim2(OrbitalSim *sim);
void configureAsteroid(OrbitalBody *body, float centerMass);
void updateOrbitalSim(OrbitalSim *sim);

#endif
