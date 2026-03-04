#pragma once

namespace gloop{
    struct Color{
        float x = 0.0F;
        float y = 0.0F;
        float z = 0.0F;
        float alpha = 1.0F;

        float* asArray(){
            float res[] = {x, y, z, alpha};
            return res;
        }
    }

}
