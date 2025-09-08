/**
 * @brief Implements an orbital simulation view
 * @author Marc S. Ressl
 * *TP 1 EDA
 * Grupo 4: Agustin Montoto, Maria Sol Vigilante y Sofia Tarantino
 * Archivo.cpp del modulo view que se encarga de la vista de la simulacion
 * @copyright Copyright (c) 2022-2023
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <raylib.h>
#include "raymath.h"
#include "View.h"

#define TIME_ACCELERATION 1000000.0f
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
OrbitalBody* selectedBody = NULL;

void Draw_time(OrbitalSim * sim);
void Draw_Names (OrbitalBody * bodys, int bodynum, Camera3D camera);

/**
 * @brief Converts a timestamp (number of seconds since 1/1/2022)
 *        to an ISO date ("YYYY-MM-DD")
 *
 * @param timestamp the timestamp
 * @return The ISO date (a raylib string)
 */
const char *getISODate(float timestamp)
{
    // Timestamp epoch: 1/1/2022
    struct tm unichEpochTM = {0, 0, 0, 1, 0, 122};

    // Convert timestamp to UNIX timestamp (number of seconds since 1/1/1970)
    time_t unixEpoch = mktime(&unichEpochTM);
    time_t unixTimestamp = unixEpoch + (time_t)timestamp;

    // Returns ISO date
    struct tm *localTM = localtime(&unixTimestamp);
    return TextFormat("%04d-%02d-%02d",
                      1900 + localTM->tm_year, localTM->tm_mon + 1, localTM->tm_mday);
}

/**
 * @brief Constructs an orbital simulation view
 *
 * @param fps Frames per second for the view
 * @return The view
 */
View *constructView(int fps)
{
    View *view = new View();

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "EDA Orbital Simulation");
    SetTargetFPS(fps);
    DisableCursor();

    view->camera.position = {10.0f, 10.0f, 10.0f};
    view->camera.target = {0.0f, 0.0f, 0.0f};
    view->camera.up = {0.0f, 1.0f, 0.0f};
    view->camera.fovy = 45.0f;
    view->camera.projection = CAMERA_PERSPECTIVE;

    return view;
}

/**
 * @brief Destroys an orbital simulation view
 *
 * @param view The view
 */
void destroyView(View *view)
{
    CloseWindow();

    delete view;
}

/**
 * @brief Should the view still render?
 *
 * @return Should rendering continue?
 */
bool isViewRendering(View *view)
{
    return !WindowShouldClose();
}

/**
 * Renders an orbital simulation
 *
 * @param view The view
 * @param sim The orbital sim
 */
void renderView(View* view, OrbitalSim* sim)
{
    UpdateCamera(&view->camera, CAMERA_FREE);

    BeginDrawing();

    ClearBackground(BLACK);
    BeginMode3D(view->camera);

    // Fill in your 3D drawing code here:
    // Planetas y asterodies
    for (int i = 0; i < sim->bodynum; i++) {
        double scaledRadius = 0.015f * logf(sim->bodys[i].radius);
        Vector3 posEscalada = Vector3Scale(sim->bodys[i].position, 1e-11f);

        if (!(sim->bodys[i].asteroid)) {
            float distance = Vector3Distance(view->camera.position, posEscalada);

            if (distance < 30.0f) {
                // Dibujamos la esfera escalada
                float scaledRadius = 0.005f * logf(sim->bodys[i].radius);
                DrawSphere(posEscalada, scaledRadius, sim->bodys[i].color);
            }
            else {
				// Dibujamos un punto 3D si estamos lejos para optimizar
                DrawPoint3D(posEscalada, sim->bodys[i].color);
            }
            // Guardamos la posición proyectada en la struct
            sim->bodys[i].screenPos = GetWorldToScreen(posEscalada, view->camera);
        }
        else {// Asteroides
            scaledRadius *= 0.1f;
            DrawSphereWires(posEscalada, scaledRadius, 8, 8, sim->bodys[i].color);
        }
        // Guardamos la posición proyectada en la struct
        sim->bodys[i].screenPos = GetWorldToScreen(posEscalada, view->camera);
    }

    DrawGrid(10, 10.0f);
    EndMode3D();

    // Fill in your 2D drawing code here:

    SetTargetFPS(60); // Opcional: limitar a 60 FPS
    DrawFPS(10, 10);  // Muestra FPS en la esquina superior izquierda

    Draw_time(sim);

    Draw_Names(sim->bodys, sim->bodynum, view->camera);

    EndDrawing();
}
/**
 * Renders the simulation time
 * @param sim The orbital sim
 */
void Draw_time(OrbitalSim * sim){
    char timeText[64];

    // Calcular tiempo transcurrido (asumiendo que timeStart es el tiempo inicial)
    float simulationTime = (GetTime() - sim->timestart) * TIME_ACCELERATION;

    // Convertir a formato ISO usando la función provista
    const char* isoDate = getISODate(simulationTime);

    // Mostrar el tiempo de simulación
    if (isoDate != NULL) {
        sprintf(timeText, "Simulation Time: %s", isoDate);
    }
    else {
        // Fallback si getISODate no está disponible
        sprintf(timeText, "Time: %.1f seconds", simulationTime);
    }
    DrawText(timeText, 10, 40, 20, WHITE);

    // Mostrar también el tiempo en años para referencia astronómica
    float years = simulationTime / (365.25f * 24.0f * 3600.0f);
    sprintf(timeText, "Years: %.3f", years);
    DrawText(timeText, 10, 70, 20, WHITE);
}
/**
 * Renders the planetts names
 *
 * @param bodys The orbital bodys
 * @param bodynum Number of bodys
 * @param camera The current camera
 */
void Draw_Names (OrbitalBody * bodys, int bodynum, Camera3D camera){
    for (int i = 0; i < bodynum; i++) {
        if (!(bodys[i].asteroid)) {
            //SI no es un asteroide
            Vector2 sp = bodys[i].screenPos;
            if ((sp.x >= 0 && sp.x <= GetScreenWidth()) &&
                (sp.y >= 0 && sp.y <= GetScreenHeight())) {
                if((camera.target.y <= 3 && camera.position.y >= 5) || 
                   (camera.position.y < 5 && camera.target.y <= -5.0f + camera.position.y)){
                    //Solo dibuja el nombre si la camara esta suficientemente baja y se ve el planeta desde arriba
                    DrawText(bodys[i].name, (int)sp.x, (int)sp.y - 20, 16, RAYWHITE);
                }
            }
            
        }
    }
}
