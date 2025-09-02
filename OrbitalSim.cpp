/**
 * @brief Orbital simulation
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 */

// Enables M_PI #define in Windows
#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>
#include <raylib.h>

#include "OrbitalSim.h"
#include "ephemerides.h"

#define GRAVITATIONAL_CONSTANT 6.6743E-11F
#define ASTEROIDS_MEAN_RADIUS 4E11F

/**
 * @brief Gets a uniform random value in a range
 *
 * @param min Minimum value
 * @param max Maximum value
 * @return The random value
 */
float getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

/**
 * @brief Configures an asteroid
 *
 * @param body An orbital body
 * @param centerMass The mass of the most massive object in the star system
 */
void configureAsteroid(OrbitalBody *body, float centerMass)
{
    // Logit distribution
    float x = getRandomFloat(0, 1);
    float l = logf(x) - logf(1 - x) + 1;

    // https://mathworld.wolfram.com/DiskPointPicking.html
    float r = ASTEROIDS_MEAN_RADIUS * sqrtf(fabsf(l));
    float phi = getRandomFloat(0, 2.0F * (float)M_PI);

    // Surprise!
    // phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    // body->mass = 1E12F;  // Typical asteroid weight: 1 billion tons
    // body->radius = 2E3F; // Typical asteroid radius: 2km
    // body->color = GRAY;
    // body->position = {r * cosf(phi), 0, r * sinf(phi)};
    // body->velocity = {-v * sinf(phi), vy, v * cosf(phi)};
}

/**
 * @brief Constructs an orbital simulation
 *
 * @param float The time step
 * @return The orbital simulation
 */
OrbitalSim *constructOrbitalSim(float timeStep, int bodynum, OrbitalBody *initialBodies)
{
    // Your code goes here...
    OrbitalSim * Sim = new OrbitalSim;
    if(Sim != NULL)
    {
        Sim->timestep = timeStep; 
        Sim->bodynum = bodynum;
        Sim->timestart = 0.0f;
        Sim->bodys = new OrbitalBody[bodynum];
        if(Sim->bodys != NULL)
        {
            for(int i = 0; i<bodynum; i++)
            {
                (Sim->bodys+i)->name = (initialBodies+i)->name;
                (Sim->bodys+i)->mass = (initialBodies+i)->mass;
                (Sim->bodys+i)->radius = (initialBodies+i)->radius;
                (Sim->bodys+i)->color = (initialBodies+i)->color;
                (Sim->bodys+i)->position = (initialBodies+i)->position;
                (Sim->bodys+i)->velocity = (initialBodies+i)->velocity;
                (Sim->bodys+i)->acceleration = {0.0f, 0.0f, 0.0f};
                (Sim->bodys+i)->FGravity = {0.0f, 0.0f, 0.0f};
            }
        }
    }
    return Sim;
}

/**
 * @brief Destroys an orbital simulation
 */
void destroyOrbitalSim(OrbitalSim *sim)
{
    free(sim->bodys);
    free(sim);

}

/**
 * @brief Simulates a timestep
 *
 * @param sim The orbital simulation
 */
void updateOrbitalSim2(OrbitalSim *sim)
{
    (sim->bodys+1)->position = Vector3Add((sim->bodys+1)->position, Vector3Scale((sim->bodys+1)->velocity, sim->timestep));
}

void updateOrbitalSim(OrbitalSim *sim)
{
    for(int i = 0; i < sim->bodynum; i++) {
        sim->bodys[i].FGravity = (Vector3){0, 0, 0};
    }

    // Actualizar la Fuerza Graviatoria
    for(int i = 0; i<sim->bodynum; i++)
    {
        for(int j=0; j < sim->bodynum; j++)
        {
            if(j!=i)
            {
                if((sim->bodys+j)->mass / (sim->bodys+i)->mass > 0.001)
                {
                    Vector3 direccion = Vector3Subtract(sim->bodys[i].position, sim->bodys[j].position);
    
                    double distancia = Vector3Length(direccion);
                    
                    double magnitud = GRAVITATIONAL_CONSTANT * sim->bodys[i].mass * sim->bodys[j].mass / (distancia * distancia);
                    
                    Vector3 fuerza = Vector3Scale(Vector3Normalize(direccion), magnitud);
                }
            }
        }
    }
    for(int i = 0; i<sim->bodynum; i++)
    {
        //Actualizar aceleracion 
        (sim->bodys+i)->acceleration = Vector3Scale((sim->bodys+i)->FGravity, 1.0f/((sim->bodys+i)->mass));
    }

    for(int i = 0; i<sim->bodynum; i++)
    {
        //Actualizar velocidad
        (sim->bodys+i)->velocity = Vector3Add((sim->bodys+i)->velocity, Vector3Scale((sim->bodys+i)->acceleration, sim->timestep));
    }

    for(int i = 0; i<sim->bodynum; i++)
    {
        //Actualizar posicion
        (sim->bodys+i)->position = Vector3Add((sim->bodys+i)->position, Vector3Scale((sim->bodys+i)->velocity, sim->timestep));
    }

}
