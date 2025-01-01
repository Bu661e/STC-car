#include "direct.h"

#ifndef __MOTOR_H__
#define __MOTOR_H__


void init_motor(); //初始化电机，设置推挽模式

void go_forward(); // 两个轮子同时正转，向前运动

void go_back();

void go_left(); // 左轮不动，右轮动，差速向左转弯

void go_right();

void stop(); // 电机停止

void pwm();

void set_compare(int cmp);

void set_mydirect(enum direct new_direct);


#endif