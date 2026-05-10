#pragma once

namespace gloop{
    // Simple data struct storing a color
    // Mainly used by lights and materials
    struct Color {
        // Red component of the color
        float r = 0.0F;
        // Green component of the color
        float g = 0.0F;
        // Blue component of the color
        float b = 0.0F;
        // Transparency of the color
        float alpha = 1.0F;
    };

}
