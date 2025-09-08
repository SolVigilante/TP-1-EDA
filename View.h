/**
 * @brief Implements an orbital simulation view
 * @author Marc S. Ressl
 * *TP 1 EDA
 * Grupo 4: Agustin Montoto, Maria Sol Vigilante y Sofia Tarantino
 * Archivo.h del modulo view que se encarga de la vista de la simulacion
 * @copyright Copyright (c) 2022-2023
 */

#ifndef ORBITALSIMVIEW_H
#define ORBITALSIMVIEW_H

#include <raylib.h>

#include "OrbitalSim.h"

/**
 * The view data
 */
struct View
{
    Camera3D camera;
};

View *constructView(int fps);
void destroyView(View *view);

bool isViewRendering(View *view);
void renderView(View *view, OrbitalSim *sim);

#endif
