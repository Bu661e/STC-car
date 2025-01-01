#ifndef __DIRECT_H__
#define __DIRECT_H__

enum direct {
	forward = 0x1,
	left = 0x2,
	right = 0x3,
	back = 0x4,
};

extern enum direct my_direct;


#endif