//
// Created by Raye on 2017/7/7.
//

#ifndef MINIPHOTOSHOP_CONSTANTS_H
#define MINIPHOTOSHOP_CONSTANTS_H
#include <QColor>
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

    UPDATE_IMAGE,UPDATE_IMAGE_ADD,UPDATE_IMAGE_MINUS,ADD_IMAGE_FAILED,
    NEW_LAYOUT,DISPLAY_REFRESH,NO_LAYOUT_SELECTED,REFRESH_PREVIEW
};
}

//Command Type
namespace COMMAND {
    enum{
        UPDATE_PEN_COLOR,UPDATE_PEN_WIDTH,UPDATE_PEN_STYLE,UPDATE_BRUSH_COLOR,UPDATE_BRUSH_STYLE,
        LAYOUT_MOVE,LAYOUT_SCALE,LAYOUT_ROTATE
    };
}

//UI states
namespace STATE{
enum{
    INIT,DRAW_LINE_INIT,DRAW_LINE,DRAW_ELLIPSE_INIT,DRAW_ELLIPSE,
    DRAW_RECT_INIT,DRAW_RECT,MOVE_INIT,MOVE,ROTATE_INIT,ROTATE,SCALE_INIT,SCALE
};
}

namespace PIXMAP{
enum{
    FMT_NULL,FMT_RGB,FMT_YUV,FMT_GREY,FMT_BIN
};
enum {
    SELECT_R=1,SELECT_G=2,SELECT_B=4,SELECT_GREY=8
};	//标记需要计数的通道

}

namespace SETTINGS{
 static unsigned int   SELECTED_RECT_WIDTH=5,SELECTED_RECT_BORDER=10;
 static QColor SELETCED_RECT_COLOR=Qt::blue;
 static Qt::PenStyle SELECTED_RETC_STYLE=Qt::DashLine;
 static double SCALE_STEP=0.01,ROTATE_STEP=0.2;
 static unsigned int LIST_ICON_SIZE=150;

}

#endif //MINIPHOTOSHOP_CONSTANTS_H
