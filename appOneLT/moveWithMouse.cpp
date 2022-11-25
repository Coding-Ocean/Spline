#include<vector>
#include"VECTOR.h"
#include"input.h"
//マウスで点をつかむためのデータ
std::vector<VECTOR*> Points;
VECTOR* GrabPoint = nullptr;
float GrabDistanceSq = pow(9, 2);

void setGrabDistanceSq(float r)
{
    GrabDistanceSq = r;
}
void addPointToMoveWithMouse(VECTOR* p)
{
    Points.push_back(p);
}
//マウスで点をつかんで移動する
void movePointWithMouse()
{
    VECTOR mouse(mouseX, mouseY);
    if (isPress(MOUSE_LBUTTON)) {
        if (GrabPoint == nullptr) {
            //つかむ
            for (int i = 0; i < Points.size(); i++) {
                if ((*Points[i] - mouse).magSq() <= GrabDistanceSq) {
                    GrabPoint = Points[i];
                }
            }
        }
        else {
            //移動
            *GrabPoint = mouse;
        }
    }
    else {
        GrabPoint = nullptr;
    }
}
