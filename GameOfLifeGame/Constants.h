#pragma once

const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
const int MAX_PHYSICS_STEPS = 6; // Max number of physics steps per frame
const float MS_PER_SECOND = 1000; // Number of milliseconds in a second
const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime, max time over which a physics step is calculated


// both in pixels at zoom == 1.0f
const int BLOCK_WIDTH = 10;
const int BLOCK_HEIGTH = 10;

const int NR_BLOCKS_WIDTH = 50;
const int NR_BLOCKS_HEIGTH = 50;

const int PIXEL_WIDTH = BLOCK_WIDTH * NR_BLOCKS_WIDTH;
const int PIXEL_HEIGTH = BLOCK_HEIGTH * NR_BLOCKS_HEIGTH;

const float DEFAULT_ZOOM = 1.0f;
const float MAX_ZOOM = 16.0f;
const float MIN_ZOOM = 1.0f;
const float CAMERA_SPEEDX = 5.0f;
const float CAMERA_SPEEDY = 5.0f;

const float GRAVITATIONAL_PULL = 0.5f;
const float MAX_GAS_RISE_SPED = -1.0f;

const float MIN_TEMPERATURE = -278.0f;

const float MIN_TEMP_COLOR = MIN_TEMPERATURE;
const float MAX_TEMP_COLOR = 1000.0f;

const float MIN_PRESSURE_COLOR = 0.0f;
const float MAX_PRESSURE_COLOR = 10.0f;
