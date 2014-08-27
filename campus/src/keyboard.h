#ifndef KEYBOARD_H
#define KEYBOARD_H


void keyboardCallback(unsigned char k, void (*f)());
void keyboardSpecialCallback(int k, void (*f)());
void keyboardCallbackv(unsigned char* k, void (*f)());
void keyboardSpecialCallbackv(int* k, void (*f)());
void keyboardCallbackvf(unsigned char* k, void (**f)());
void keyboardSpecialCallbackvf(int* k, void (**f)());



#endif
