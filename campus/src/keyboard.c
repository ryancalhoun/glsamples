#include<GL/glut.h>
#define MAX_KEYS 500


// map keys to functions
struct keymap
{
	char key;
	void (*callback)();
} _keymap[MAX_KEYS] = {0};

int _keyboard_loop_enter;
int _keyboard_loop_timer;


/*
 *
 *
 */
void _keyboard_loop(int m)
{
	int i;
	int count = 0;

	// ascii keys
	for(i = 0; i < 256; ++i)
	{
		if(_keymap[i].key && _keymap[i].callback)
		{
			_keymap[i].callback((unsigned char)i);
			++count;
		}
	}

	// function keys
	for(; i < MAX_KEYS; ++i)
	{
		if(_keymap[i].key && _keymap[i].callback)
		{
			_keymap[i].callback((int)(i - 256));
			++count;
		}
	}

	// re-enter loop
	if(count)
		glutTimerFunc(m, _keyboard_loop, m);
	else _keyboard_loop_enter = 0;

	glutPostRedisplay();
}


/*
 *  key press
 *
 */
void _keydown(unsigned char k, int x, int y)
{
	_keymap[k].key = 1;
	if(!_keyboard_loop_enter)
	{
		_keyboard_loop_enter = 1;
		_keyboard_loop(_keyboard_loop_timer);
	}
}

/*
 *  key press
 *
 */
void _keyup(unsigned char k, int x, int y)
{
	_keymap[k].key = 0;
}


/*
 *  key release
 *
 */
void _spdown(int k, int x, int y)
{
	if(_keymap[k+256].callback)
		_keymap[k+256].callback(k);

	return;
	_keymap[k+256].key = 1;
	if(!_keyboard_loop_enter)
	{
		_keyboard_loop_enter = 1;
		_keyboard_loop(_keyboard_loop_timer);
	}
}


/*
 *  key release
 *
 */
void _spup(int k, int x, int y)
{
	_keymap[k+256].key = 0;
}


/*
 *  initialize keyboard read loop
 *
 */
void initKeyboard(int m)
{
	glutKeyboardFunc(_keydown);
	glutKeyboardUpFunc(_keyup);

	glutSpecialFunc(_spdown);
	glutSpecialUpFunc(_spup);
	_keyboard_loop_timer = m;
	_keyboard_loop_enter = 0;
}


/*
 *  map character to function
 *
 */
void keyboardCallback(unsigned char k, void (*f)())
{
	_keymap[k].callback = f;
}


/*
 *  map character to function
 *
 */
void keyboardSpecialCallback(int k, void (*f)())
{
	_keymap[k+256].callback = f;
}


/*
 *  map each character to function
 *
 */
void keyboardCallbackv(unsigned char* k, void (*f)())
{
	while(*k && *f)
		keyboardCallback(*k++, f);
}


/*
 *  map each character to function
 *
 */
void keyboardSpecialCallbackv(int* k, void (*f)())
{
	while(*k && *f)
		keyboardSpecialCallback(*k++, f);
}


/*
 *  map each character to each function
 *
 */
void keyboardCallbackvf(unsigned char* k, void (**f)())
{
	while(*k && *f)
		keyboardCallback(*k++, *f++);
}


/*
 *  map each character to each function
 *
 */
void keyboardSpecialCallbackvf(int* k, void (**f)())
{
	while(*k && *f)
		keyboardSpecialCallback(*k++, *f++);
}



