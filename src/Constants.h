//
// Created by Raye on 2017/7/7.
//

#ifndef MINIPHOTOSHOP_CONSTANTS_H
#define MINIPHOTOSHOP_CONSTANTS_H

//Shape
namespace SHAPE {
    enum {
        LINE, ELLIPSE, RECT, PIXMAP
    };
}

namespace PENSTYLE {
    enum {
        NOPEN,SOLID,DASH,DOT,DASH_DOT,DASH_DOT_DOT
    };
}

namespace BRUSHSTYLE {
enum{
    NOBRUSH,SOLIDPATTERN,DENSE1PATTERN,DENSE2PATTERN,DENSE3PATTERN, DENSE4PATTERN,
    DENSE5PATTERN, DENSE6PATTERN,DENSE7PATTERN,HORPATTERN,VERPATTERN,
    CROSSPATTERN, BDIAGPATTERN,FDIAGPATTERN,DIAGCROSSPATTERN
};
}

//Notify Type
namespace NOTIFY{
enum{

    UPDATE_IMAGE,UPDATE_IMAGE_ADD,UPDATE_IMAGE_MINUS
};
}

//Command Type
namespace COMMAND {
    enum{
        UPDATE_PEN_COLOR,UPDATE_PEN_WIDTH,UPDATE_PEN_STYLE,UPDATE_BRUSH_COLOR,UPDATE_BRUSH_STYLE
    };
}

//UI states
namespace STATE{
enum{
    INIT,DRAW_LINE_INIT,DRAW_LINE,DRAW_ELLIPSE_INIT,DRAW_ELLIPSE,
    DRAW_RECT_INIT,DRAW_RECT
};
}

namespace PIXMAP{
enum{
    FMT_NULL,FMT_RGB,FMT_YUV,FMT_GREY,FMT_BIN
};
}

#endif //MINIPHOTOSHOP_CONSTANTS_H
