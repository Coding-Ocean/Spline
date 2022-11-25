#include<vector>
#include"VECTOR.h"
#include"input.h"
//�}�E�X�œ_�����ނ��߂̃f�[�^
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
//�}�E�X�œ_������ňړ�����
void movePointWithMouse()
{
    VECTOR mouse(mouseX, mouseY);
    if (isPress(MOUSE_LBUTTON)) {
        if (GrabPoint == nullptr) {
            //����
            for (int i = 0; i < Points.size(); i++) {
                if ((*Points[i] - mouse).magSq() <= GrabDistanceSq) {
                    GrabPoint = Points[i];
                }
            }
        }
        else {
            //�ړ�
            *GrabPoint = mouse;
        }
    }
    else {
        GrabPoint = nullptr;
    }
}
