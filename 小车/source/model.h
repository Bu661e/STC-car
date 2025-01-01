#ifndef __MODEL_H__
#define __MODEL_H__
;
enum model {
	bluetooth = 0,
	ir = 1,
	rs485 = 2
};

extern enum model my_model;

#endif