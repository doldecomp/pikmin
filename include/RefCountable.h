#ifndef _REFCOUNTABLE_H
#define _REFCOUNTABLE_H

#include "types.h"

/**
 * @brief Basic struct for countable objects (creatures etc).
 *
 * @note Size: 0x8.
 */
struct RefCountable {
	RefCountable();

	virtual void addCntCallback() { } // _08 (weak)
	virtual void subCntCallback() { } // _0C (weak)

	void clearCnt(); // sets count to 0
	void addCnt();   // adds one to count
	void subCnt();   // subtracts one from count (with floor of 0)

	int getCnt() { return mCount; }

	// DLL inlines to do:
	bool removable() { return mCount == 0; }

	// _00 = VTBL
	int mCount; // _04, count
};

#endif
