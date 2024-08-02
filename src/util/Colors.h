//
// Created by lkapi on 26.02.2023.
//

#pragma once

#ifndef PROJECTSAFE_COLORS_H
#define PROJECTSAFE_COLORS_H

#include <iostream>

#define RESET_COLOR UI::setColor(Colors::RESET);
#define USE_COLOR(color) UI::setColor(Colors::color);

namespace UI {

    enum class Colors {
        // Reset all colors
        RESET = 0,

        // Regular colors
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        MAGENTA = 35,
        CYAN = 36,
        WHITE = 37,

        // Bold colors
        BOLD_BLACK = 90,
        BOLD_RED = 91,
        BOLD_GREEN = 92,
        BOLD_YELLOW = 93,
        BOLD_BLUE = 94,
        BOLD_MAGENTA = 95,
        BOLD_CYAN = 96,
        BOLD_WHITE = 97,

        // Underlined colors
        UNDERLINE_BLACK = 40,
        UNDERLINE_RED = 41,
        UNDERLINE_GREEN = 42,
        UNDERLINE_YELLOW = 43,
        UNDERLINE_BLUE = 44,
        UNDERLINE_MAGENTA = 45,
        UNDERLINE_CYAN = 46,
        UNDERLINE_WHITE = 47,

        // Background colors
        BACKGROUND_BLACK = 100,
        BACKGROUND_RED = 101,
        BACKGROUND_GREEN = 102,
        BACKGROUND_YELLOW = 103,
        BACKGROUND_BLUE = 104,
        BACKGROUND_MAGENTA = 105,
        BACKGROUND_CYAN = 106,
        BACKGROUND_WHITE = 107
    };

    static void setColor(Colors color) {
        std::cout << "\033[" << static_cast<int>(color) << "m";
    }

} // UI

#endif //PROJECTSAFE_COLORS_H
