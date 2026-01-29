/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGB_to_pantone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:09:46 by marvin            #+#    #+#             */
/*   Updated: 2025/08/13 15:35:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

typedef struct {
    char name[32];
    double L, a, b;
} PantoneColor;

// Petite table Pantone fictive (valeurs Lab approximatives)
PantoneColor pantone_table[] = {
    {"Pantone 485 C", 53.23, 80.11, 67.22},
    {"Pantone 300 C", 32.30, 79.19, -107.86},
    {"Pantone 7406 C", 81.73, 3.67, 80.41},
    {"Pantone 100 C", 93.00, -8.00, 50.00},
    {"Pantone 101 C", 92.00, -9.00, 66.00},
    {"Pantone 102 C", 91.00, -7.00, 100.00},
    {"Pantone 103 C", 71.00, 0.00, 91.00},
    {"Pantone 104 C", 62.00, 0.00, 75.00},
    {"Pantone 105 C", 44.00, 0.00, 45.00},
    {"Pantone 7408 C", 84.00, 6.00, 83.00},
    {"Pantone 109 C", 88.00, 2.00, 95.00},
    {"Pantone 116 C", 83.00, 6.00, 93.00},
    {"Pantone 123 C", 84.00, 15.00, 74.00},
    {"Pantone 130 C", 74.00, 21.00, 74.00},
    {"Pantone 137 C", 74.00, 31.00, 69.00},
    {"Pantone 165 C", 64.00, 43.00, 65.00},
    {"Pantone 1795 C", 49.00, 65.00, 50.00},
    {"Pantone 186 C", 46.00, 68.00, 46.00},
    {"Pantone 187 C", 42.00, 60.00, 38.00},
    {"Pantone 199 C", 47.00, 66.00, 46.00},
    {"Pantone 200 C", 44.00, 58.00, 34.00},
    {"Pantone 202 C", 38.00, 45.00, 26.00},
    {"Pantone 3005 C", 27.00, 17.00, -44.00},
    {"Pantone 301 C", 20.00, 6.00, -31.00},
    {"Pantone 302 C", 15.00, -3.00, -19.00},
    {"Pantone 303 C", 13.00, -5.00, -12.00}
};

int pantone_count = sizeof(pantone_table) / sizeof(pantone_table[0]);

// Convert RGB [0-255] -> XYZ
void rgb_to_xyz(int r, int g, int b, double *x, double *y, double *z) {
    double R = r / 255.0;
    double G = g / 255.0;
    double B = b / 255.0;

    // Correction gamma
    R = (R > 0.04045) ? pow((R + 0.055) / 1.055, 2.4) : R / 12.92;
    G = (G > 0.04045) ? pow((G + 0.055) / 1.055, 2.4) : G / 12.92;
    B = (B > 0.04045) ? pow((B + 0.055) / 1.055, 2.4) : B / 12.92;

    // Transformation sRGB -> XYZ (D65)
    *x = (R * 0.4124 + G * 0.3576 + B * 0.1805) * 100.0;
    *y = (R * 0.2126 + G * 0.7152 + B * 0.0722) * 100.0;
    *z = (R * 0.0193 + G * 0.1192 + B * 0.9505) * 100.0;
}

// XYZ -> Lab
void xyz_to_lab(double x, double y, double z, double *L, double *a, double *b) {
    // D65 reference white
    double Xn = 95.047, Yn = 100.000, Zn = 108.883;

    double fx = x / Xn;
    double fy = y / Yn;
    double fz = z / Zn;

    double epsilon = 0.008856;
    double kappa = 903.3;

    fx = (fx > epsilon) ? cbrt(fx) : ((kappa * fx + 16) / 116.0);
    fy = (fy > epsilon) ? cbrt(fy) : ((kappa * fy + 16) / 116.0);
    fz = (fz > epsilon) ? cbrt(fz) : ((kappa * fz + 16) / 116.0);

    *L = (116 * fy) - 16;
    *a = 500 * (fx - fy);
    *b = 200 * (fy - fz);
}

// Distance Delta E (CIE76 simple)
double deltaE(double L1, double a1, double b1, double L2, double a2, double b2) {
    return sqrt(pow(L1 - L2, 2) + pow(a1 - a2, 2) + pow(b1 - b2, 2));
}

int main() {
    int r = 30, g = 64, b = 200; // Exemple couleur

    double X, Y, Z, L, a, b_;
    rgb_to_xyz(r, g, b, &X, &Y, &Z);
    xyz_to_lab(X, Y, Z, &L, &a, &b_);

    printf("RGB(%d,%d,%d) -> Lab(%.2f, %.2f, %.2f)\n", r, g, b, L, a, b_);

    // Recherche Pantone le plus proche
    double best_diff = 1e9;
    const char *best_name = NULL;
    for (int i = 0; i < pantone_count; i++) {
        double diff = deltaE(L, a, b_, pantone_table[i].L, pantone_table[i].a, pantone_table[i].b);
        if (diff < best_diff) {
            best_diff = diff;
            best_name = pantone_table[i].name;
        }
    }

    printf("Pantone le plus proche : %s (ΔE = %.2f)\n", best_name, best_diff);
    return 0;
}
