#define _HERMITE
//#define _CATMULL_ROW
//#define _BEZIER
//#define _BSPLINE

#ifdef _HERMITE
#include<vector>
#include"libOne.h"
#include"moveWithMouse.h"
#include"hermite.h"
void gmain()
{
    window(1920, 1080, full);
    //Colors
    colorMode(HSV, 100);
    angleMode(DEGREES);
    COLOR black(0, 0, 0);
    COLOR white(0, 0, 100);
    COLOR gray(0, 0, 50);
    COLOR yellow(65, 100, 80);
    COLOR rainbow;
    //Hermite Spline Points
    std::vector<VECTOR> p;
    p.emplace_back(900, 300);//p0-p1がv1となる
    p.emplace_back(900, 540);//p1
    p.emplace_back(1200, 540);//p2
    p.emplace_back(1200, 300);//p2-p3がv2となる
    //Prepare for Mouse dragging
    for (size_t i = 0; i < p.size(); i++) {
        addPointToMoveWithMouse(&p[i]);
    }
    //for character motion
    int img = loadImage("car.png");
    float t = 0;
    float dt = 0.005f;
    int sw = 0;
    //Main Loop
    while (notQuit) {
        movePointWithMouse();
        clear(0, 0, 0);
        
        //Draw curve
        VECTOR v1 = p[0] - p[1];
        VECTOR v2 = p[3] - p[2];
        {
            VECTOR sp = p[1];
            float dt = 0.01f;
            for (float t = dt; t <= 1.000001f; t += dt) {
                VECTOR ep = hermite::interpolation(p[1], v1, p[2], v2, t);
                rainbow.set(360 * (t - dt), 50, 100);
                line(sp, ep, rainbow, 9);
                sp = ep;
            }
        }

        //Draw control points
        arrow(p[1], p[0], yellow, 3);
        arrow(p[2], p[3], yellow, 3);
        circle(p[1], 14, black, white, 6);
        circle(p[2], 14, black, white, 6);
        //Text
        fill(white);textMode(BCENTER); textSize(40);
        text((let)"p1", p[1].x, p[1].y + 30);
        text((let)"p2", p[2].x, p[2].y + 30);
        text((let)"v1", p[1].x + v1.x * 0.5f, p[1].y + v1.y * 0.5f - 25);
        text((let)"v2", p[2].x + v2.x * 0.5f, p[2].y + v2.y * 0.5f - 25);

        //Character motion
        //Control 't' value
        if (isTrigger(KEY_SPACE))++sw %= 4;
        //アニメーション tが1になったら0にもどす
        if (sw == 1) { t += dt;  if (t >= 1.0f) { t = 0; } }
        //スタート地点で固定
        else if (sw == 2) { t = 0; }
        //終点で固定
        else if (sw == 3) { t = 1; }
        //Draw character
        if (sw > 0) {
            VECTOR pos = hermite::interpolation(p[1], v1, p[2], v2, t);
            VECTOR v = hermite::derivative(p[1], v1, p[2], v2, t);
            float angle = Atan2(v.y, v.x);
            image(img, pos, angle, 1, CENTER);
        }
        //print 't' value
        fill(white); printPosX(50); printPosY(50);
        print((let)"t=" + t);
    }
}
#endif
#ifdef _CATMULL_ROW
#include<vector>
#include"libOne.h"
#include"moveWithMouse.h"
#include"hermite.h"
void gmain()
{
    window(1920, 1080, full);
    //Colors
    colorMode(HSV, 100);
    angleMode(DEGREES);
    COLOR black(0, 0, 0);
    COLOR white(0, 0, 100);
    COLOR gray(0, 0, 50);
    COLOR red(330, 100, 100);
    COLOR yellow(65, 100, 80);
    COLOR rainbow;
    //Hermite Spline Points
    std::vector<VECTOR> p;
    p.emplace_back(600, 540);//p0
    p.emplace_back(900, 540);//p1
    p.emplace_back(1200, 540);//p2
    p.emplace_back(1500, 540);//p3
    //Prepare for Mouse dragging
    for (size_t i = 0; i < p.size(); i++) {
        addPointToMoveWithMouse(&p[i]);
    }
    //for character motion
    int img = loadImage("car.png");
    float t = 0;
    float dt = 0.005f;
    int sw = 0;
    float tension = 0.5f;
    //Main Loop
    while (notQuit) {
        if (isTrigger(KEY_W))dt += 0.01f;
        if (isTrigger(KEY_S))dt -= 0.01f;
        movePointWithMouse();

        clear(90, 100, 0);
        //Draw curve
        if (isPress(KEY_D))tension += 0.01f;
        if (isPress(KEY_A))tension -= 0.01f;
        VECTOR v1 = tension * (p[2] - p[0]);
        VECTOR v2 = tension * (p[3] - p[1]);
        VECTOR sp = p[1];
        VECTOR ep;
        float d = 0.01f;
        for (float t = d; t <= 1.000001f; t += d) {
            ep = hermite::interpolation(p[1], v1, p[2], v2, t);
            rainbow.set(360 * (t - d), 50, 100);
            line(sp, ep, rainbow, 10);
            //point(sp, rainbow, 9);
            sp = ep;
        }
        //Draw tangent vector
        arrow(p[0], p[2], gray, 3);
        arrow(p[1], p[3], gray, 3);
        arrow(p[1], p[1] + v1, yellow, 3);
        arrow(p[2], p[2] + v2, yellow, 3);
        //Draw points and text
        for (size_t i = 0; i < p.size(); i++) {
            circle(p[i], 14, black, white, 6);
            fill(white); textMode(BCENTER); textSize(40);
            text((let)"p" + (int)i, p[i].x, p[i].y + 30);
        }
        fill(gray);
        text("v1", p[1].x + v1.x * 0.5f, p[1].y + v1.y * 0.5f + 30);
        text("v2", p[2].x + v2.x * 0.5f, p[2].y + v2.y * 0.5f + 30);


        //Character motion
        //Control 't' value
        if (isTrigger(KEY_SPACE))++sw %= 3;
        //アニメーション tが1になったら0にもどす
        if (sw == 1) { t += dt;  if (t >= 1.0f) { t = 0; } }
        //スタート地点で固定
        else if (sw == 2) { t = 0; }
        //終点で固定
        else if (sw == 3) { t = 1; }
        //Draw character
        if (sw > 0) {
            VECTOR pos = hermite::interpolation(p[1], v1, p[2], v2, t);
            VECTOR v = hermite::derivative(p[1], v1, p[2], v2, t);
            float angle = Atan2(v.y, v.x);
            image(img, pos, angle, 1, CENTER);
        }
        //print 't' value
        fill(white); printPosX(50); printPosY(50);
        print((let)"t=" + t);
    }
}
#endif
#ifdef _BEZIER
#include<vector>
#include"libOne.h"
#include"moveWithMouse.h"
#include"hermite::interpolation.h"
void gmain()
{
    window(1920, 1080, full);
    //Colors
    colorMode(HSV, 100);
    angleMode(DEGREES);
    COLOR black(0, 0, 0);
    COLOR white(0, 0, 100);
    COLOR gray(0, 0, 50);
    COLOR red(330, 100, 100);
    COLOR yellow(65, 100, 80);
    COLOR rainbow;
    //Bezier Spline Points
    std::vector<VECTOR> p;
    p.emplace_back(600, 540);
    p.emplace_back(900, 540);
    p.emplace_back(1200, 540);
    p.emplace_back(1500, 540);
    //Prepare for Mouse dragging
    for (size_t i = 0; i < p.size(); i++) {
        addPointToMoveWithMouse(&p[i]);
    }
    //for character motion
    int img = loadImage("car.png");
    float t = 0;
    float dt = 0.005f;
    int sw = 0;
    //Main Loop
    while (notQuit) {
        if (isTrigger(KEY_W))dt += 0.0025f;
        if (isTrigger(KEY_S))dt -= 0.0025f;
        movePointWithMouse();

        clear(90, 100, 0);
        //Draw curve
        VECTOR v1 = 3*(p[1] - p[0]);
        VECTOR v2 = 3*(p[3] - p[2]);
        VECTOR sp = p[0];
        float d = 0.01f;
        for (float t = d; t <= 1.000001f; t += d) {
            VECTOR ep = hermite::interpolation(p[0], v1, p[3], v2, t);
            rainbow.set(360 * (t - d), 50, 100);
            line(sp, ep, rainbow, 9);
            point(sp, rainbow, 9);
            sp = ep;
        }

        //Draw control points
        arrow(p[0], p[0] + v1, yellow, 6);
        arrow(p[0], p[1], gray, 3);
        arrow(p[3], p[3] + v2, yellow, 6);
        arrow(p[2], p[3], gray, 3);
        for (size_t i = 0; i < p.size(); i++) {
            fill(yellow);
            textMode(BCENTER);
            textSize(40);
            text((let)"p" + (int)i, p[i].x, p[i].y + 30);
            circle(p[i], 14, black, white, 6);
        }

        //Character motion
        //Control 't' value
        if (isTrigger(KEY_SPACE))++sw %= 3;
        //アニメーション tが1になったら0にもどす
        if (sw == 0) { t += dt;  if (t >= 1.0f) { t = 0; } }
        //スタート地点で固定
        else if (sw == 1) { t = 0; }
        //終点で固定
        else if (sw == 2) { t = 1; }
        //Draw character
        VECTOR pos = hermite::interpolation(p[0], v1, p[3], v2, t);
        VECTOR v = hermite::derivative(p[0], v1, p[3], v2, t);
        float angle = Atan2(v.y, v.x);
        image(img, pos, angle, 1, CENTER);

        //print 't' value
        fill(white); printPosX(50); printPosY(50);
        print((let)"t=" + t);
    }
}
#endif
#ifdef _BSPLINE
#include<vector>
#include"libOne.h"
#include"moveWithMouse.h"
#include"bspline.h"
void gmain()
{
    window(1920, 1080, full);
    //Colors
    colorMode(HSV, 100);
    angleMode(DEGREES);
    COLOR black(0, 0, 0);
    COLOR white(0, 0, 100);
    COLOR gray(0, 0, 50);
    COLOR red(330, 100, 100);
    COLOR yellow(65, 100, 80);
    COLOR rainbow;
    //Bezier Spline Points
    std::vector<VECTOR> p;
    p.emplace_back(600, 540);
    p.emplace_back(700, 540 + 200);
    p.emplace_back(800, 540 - 300);
    p.emplace_back(900, 540 + 100);
    p.emplace_back(1000, 540 + 100);
    p.emplace_back(1100, 540);
    p.emplace_back(1200, 540 + 100);
    p.emplace_back(1300, 540);
    //Prepare for Mouse dragging
    for (size_t i = 0; i < p.size(); i++) {
        addPointToMoveWithMouse(&p[i]);
    }
    //for character motion
    int img = loadImage("car.png");
    float t = 0;
    float dt = 0.05f;
    int sw = 0;
    size_t idx = 0;
    //Main Loop
    while (notQuit) {
        if (isTrigger(KEY_W))dt += 0.0025f;
        if (isTrigger(KEY_S))dt -= 0.0025f;
        movePointWithMouse();

        clear(90, 100, 0);
        //Draw curve
        for (size_t i = 0; i < p.size() - 3; i++) {
            VECTOR sp = bspline::interpolation(p[i], p[i + 1], p[i + 2], p[i + 3], 0);
            float d = 0.01f;
            for (float t = d; t <= 1.000001f; t += d) {
                VECTOR ep = bspline::interpolation(p[i], p[i + 1], p[i + 2], p[i + 3], t);
                rainbow.set(60 * (t - d), 50, 100);
                line(sp, ep, rainbow, 9);
                point(sp, rainbow, 9);
                sp = ep;
            }
        }
        //Draw control points
        for (size_t i = 0; i < p.size(); i++) {
            fill(yellow);
            textMode(BCENTER);
            textSize(40);
            text((let)"p" + (int)i, p[i].x, p[i].y + 30);
            circle(p[i], 14, black, white, 6);
        }

        //Character motion
        t += dt;
        if (t >= 1.0f) {
            t = 1 - t;
            idx += 1;
            if (idx >= p.size() - 3) {
                idx = 0;
            }
        }
        //Draw character
        VECTOR pos = bspline::interpolation(p[idx], p[idx + 1], p[idx + 2], p[idx + 3], t);
        VECTOR v = bspline::derivative(p[idx], p[idx + 1], p[idx + 2], p[idx + 3], t);
        float angle = Atan2(v.y, v.x);
        image(img, pos, angle, 1, CENTER);
    }
}
#endif