#include "utils.h"

int caractereDunMot(unsigned char c) {
    // Lettres minuscules
    if ((c >= 'a' && c <= 'z') ||
        // Lettres majuscules
        (c >= 'A' && c <= 'Z') ||
        // Lettres accentuées
        (c >= 192 && c <= 255) ||
        // Chiffres
        (c >= '0' && c <= '9') ||
        // Apostrophe
        (c == '\'') ||
        // Tiret
        (c == '-')) {
        return 1;
    }
    return 0;
}

int caractereFinDePhrase(unsigned char c) {
    // Point, point d'exclamation, ou point d'interrogation
    if (c == '.' || c == '!' || c == '?') {
        return 1;
    }
    return 0;
}
