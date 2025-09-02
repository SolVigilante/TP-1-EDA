/**
 * @brief Orbital simulation main module
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

#include "OrbitalSim.h"
#include "View.h"

#define SECONDS_PER_DAY 86400

int main()
{
    int fps = 60;                                 // Frames per second
    float timeMultiplier = 100 * SECONDS_PER_DAY; // Simulation speed: 100 days per simulation second
    float timeStep = timeMultiplier / fps;

    OrbitalBody initialBodies[2] = {
        {"Sun", 1.989E30F, 6.9634E8F, YELLOW, {0, 0, 0}, {0, 0, 0}},
        {"Earth", 5.972E24F, 6.371E6F, BLUE, {1.496E11F, 0, 0}, {0, 0, 29780}}};

    OrbitalSim *sim = constructOrbitalSim(timeStep, 2, initialBodies);
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
