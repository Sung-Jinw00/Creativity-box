#ifndef METRICS_HPP
#define METRICS_HPP

// Styles et couleurs ANSI
#define RESET       "\033[0m"
#define BOLD       "\033[1m"

#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define GRAY        "\033[90m"

// Styles et couleurs ANSI bright
#define RESET       "\033[0m"
#define BRIGHT_RED    "\033[91m"
#define BRIGHT_GREEN  "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE   "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN   "\033[96m"
#define BRIGHT_WHITE  "\033[97m"
#define BRIGHT_GRAY   "\033[90m"

// --- Diamètre en km ---
#define DIAMETER_SUN       1391016
#define DIAMETER_MERCURY   4879
#define DIAMETER_VENUS     12104
#define DIAMETER_EARTH     12742
#define DIAMETER_MARS      6779
#define DIAMETER_JUPITER   139820
#define DIAMETER_SATURN    116460
#define DIAMETER_URANUS    50724
#define DIAMETER_NEPTUNE   49244

// --- Masse en kg ---
#define MASS_SUN       1.989e30
#define MASS_MERCURY   3.3011e23
#define MASS_VENUS     4.8675e24
#define MASS_EARTH     5.97237e24
#define MASS_MARS      6.4171e23
#define MASS_JUPITER   1.8982e27
#define MASS_SATURN    5.6834e26
#define MASS_URANUS    8.6810e25
#define MASS_NEPTUNE   1.02413e26

// --- Gravité surface (G) ---
#define GRAVITY_SUN       27.93
#define GRAVITY_MERCURY   0.38
#define GRAVITY_VENUS     0.90
#define GRAVITY_EARTH     1.00
#define GRAVITY_MARS      0.38
#define GRAVITY_JUPITER   2.53
#define GRAVITY_SATURN    1.06
#define GRAVITY_URANUS    0.89
#define GRAVITY_NEPTUNE   1.14

// --- Nombre de lunes ---
#define MOON_SUN       0
#define MOON_MERCURY   0
#define MOON_VENUS     0
#define MOON_EARTH     1
#define MOON_MARS      2
#define MOON_JUPITER   95
#define MOON_SATURN    83
#define MOON_URANUS    27
#define MOON_NEPTUNE   14

// --- Vitesse moyenne du vent (km/h) ---
#define WIND_SUN       0
#define WIND_MERCURY   0
#define WIND_VENUS     360
#define WIND_EARTH     100
#define WIND_MARS      60
#define WIND_JUPITER   620
#define WIND_SATURN    1800
#define WIND_URANUS    900
#define WIND_NEPTUNE   1600

// --- Température moyenne (°C) ---
#define TEMP_SUN       5505
#define TEMP_MERCURY   167
#define TEMP_VENUS     464
#define TEMP_EARTH     15
#define TEMP_MARS     -65
#define TEMP_JUPITER  -110
#define TEMP_SATURN   -140
#define TEMP_URANUS  -195
#define TEMP_NEPTUNE -200
#define ABSOLUTE_ZERO -273.15

// --- Vitesse orbitale autour du Soleil (km/s) ---
#define ORBITAL_SPEED_MERCURY   47.87
#define ORBITAL_SPEED_VENUS     35.02
#define ORBITAL_SPEED_EARTH     29.78
#define ORBITAL_SPEED_MARS      24.07
#define ORBITAL_SPEED_JUPITER   13.07
#define ORBITAL_SPEED_SATURN     9.69
#define ORBITAL_SPEED_URANUS     6.81
#define ORBITAL_SPEED_NEPTUNE    5.43

// --- Vitesse de rotation (durée du jour) en heures ---
#define ROTATION_SUN       609.12   // environ 25.38 jours
#define ROTATION_MERCURY   1407.6
#define ROTATION_VENUS    -5832.5  // rotation rétrograde
#define ROTATION_EARTH      24.0
#define ROTATION_MARS       24.6
#define ROTATION_JUPITER    9.93
#define ROTATION_SATURN    10.7
#define ROTATION_URANUS    -17.2
#define ROTATION_NEPTUNE    16.1

// --- Couleurs personnalisées pour chaque astre ---
#define COLOR_SUN       BOLD YELLOW
#define COLOR_MERCURY   GRAY
#define COLOR_VENUS     MAGENTA
#define COLOR_EARTH     GREEN
#define COLOR_MARS      RED
#define COLOR_JUPITER   BRIGHT_GREEN
#define COLOR_SATURN    BRIGHT_YELLOW
#define COLOR_URANUS    BRIGHT_CYAN
#define COLOR_NEPTUNE   BLUE

#endif
