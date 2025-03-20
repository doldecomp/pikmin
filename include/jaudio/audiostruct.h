#ifndef _JAUDIO_AUDIOSTRUCT_H
#define _JAUDIO_AUDIOSTRUCT_H

#include "types.h"
#include "Dolphin/os.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

///////////////// JAUDIO STRUCTURES /////////////////
// Members and names from AC Decomp with gratitude.

/**
 * @brief Audio heap.
 *
 * @note Size: 0x14.
 */
typedef struct ALHeap {
	u8* base;    // _00
	u8* current; // _04
	int length;  // _08
	u32 count;   // _0C
	u8* last;    // _10
} ALHeap;

/**
 * @brief TODO.
 */
typedef struct dspch_ {
	// TODO
} DSPChannel;

/**
 * @brief TODO.
 */
typedef struct jc_ {
	// TODO
} JC;

/**
 * @brief TODO.
 */
typedef struct jcs_ {
	// TODO
} JCS;

/**
 * @brief TODO.
 */
typedef struct Wave_ {
	u8 _00;                // _00
	u8 compBlockIdx;       // _01
	u8 _02;                // _02
	s8 _04[12];            // _04
	s32 isLooping;         // _10
	s32 loopAddress;       // _14
	s32 loopStartPosition; // _18
	s32 _1C;               // _1C
	s16 loopYN1;           // _20
	s16 loopYN2;           // _22
} Wave;

/////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
