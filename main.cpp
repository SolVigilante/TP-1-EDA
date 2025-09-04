/**
 * @brief Orbital simulation main module
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

 #include <stdio.h>

#include "OrbitalSim.h"
#include "View.h"

#define INITIAL_BODYS 1009

#define SECONDS_PER_DAY 86400

int main()
{
    int fps = 60;                                 // Frames per second
    float timeMultiplier = 100 * SECONDS_PER_DAY; // Simulation speed: 100 days per simulation second
    float timeStep = timeMultiplier / fps;

    OrbitalBody initialBodies[INITIAL_BODYS];
    
    configurePlanet(initialBodies);

    for(int i= PLANET_NUM; i < INITIAL_BODYS; i++) {
        configureAsteroid(initialBodies+i, initialBodies[0].mass);
        initialBodies[i].asteroid = true;
    }

    OrbitalSim *sim = constructOrbitalSim(timeStep, INITIAL_BODYS, initialBodies);
    
    View *view = constructView(fps);

    while (isViewRendering(view))
    {
        updateOrbitalSim(sim);

        renderView(view, sim);
    }

    destroyView(view);
    destroyOrbitalSim(sim);

    return 0;
}
