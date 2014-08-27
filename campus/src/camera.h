#ifndef CAMERA_H
#define CAMERA_H

extern int width, height;

void init_camera();
void close_camera();
void aim_camera();
void move_camera(unsigned char key);

void free_camera(int e);
void circle_camera(int e);
void bezier_camera(int e);

#endif
