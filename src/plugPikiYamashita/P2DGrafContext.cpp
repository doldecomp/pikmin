#include "P2D/Graph.h"
#include "PUT/Geometry.h"
#include "Colour.h"
#include "Dolphin/gx.h"
#include "DebugLog.h"

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
DEFINE_ERROR();

/*
 * --INFO--
 * Address:	........
 * Size:	0000F4
 */
DEFINE_PRINT("P2DGrafContext");

/*
 * --INFO--
 * Address:	........
 * Size:	00009C
 */
P2DGrafContext::P2DGrafContext(const PUTRect&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	801AF7AC
 * Size:	0000B4
 */
P2DGrafContext::P2DGrafContext(int x0, int y0, int width, int height)
    : _08(x0, y0, x0 + width, y0 + height)
    , _10(x0, y0, x0 + width, y0 + height)
{
	_2A = 0;
	_2C = 0;
	Colour colour(255, 255, 255, 255);
	setColor(colour, colour, colour, colour);
	setLineWidth(6);
}

/*
 * --INFO--
 * Address:	801AF860
 * Size:	0000CC
 */
void P2DGrafContext::setPort()
{
	GXSetViewport(_08.mMin.x, _08.mMin.y, _08.getWidth(), _08.getHeight(), 0.0f, 1.0f);
	setScissor();
	setup2D();
}

/*
 * --INFO--
 * Address:	801AF92C
 * Size:	000174
 */
void P2DGrafContext::setup2D()
{
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_NONE);
	GXLoadPosMtxImm(_70.mMtx, 0);
	GXSetNumChans(1);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);

	Matrix4f mtx;
	mtx.makeIdentity();
	GXLoadTexMtxImm(mtx.mMtx, GX_IDENTITY, GX_MTX3x4);
	GXSetCurrentMtx(GX_TEXMTX_NULL);
	GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_POS_XYZ, GX_RGBA8, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_U16, 15);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_POS_XYZ, GX_U16, 15);
	GXSetLineWidth(mLineWidth, GX_TO_ZERO);
	GXSetCullMode(GX_CULL_NONE);
}

/*
 * --INFO--
 * Address:	801AFAA0
 * Size:	0000A0
 */
void P2DGrafContext::setScissor()
{
	PUTRect bounds(0, 0, 1000, 1000);
	PUTRect scissor = _10;
	_10.intersect(bounds);
	scissor.normalize();
	scissor.add(0, -1);
	if (scissor.intersect(bounds)) {
		GXSetScissor(scissor.mMin.x, scissor.mMin.y, scissor.getWidth(), scissor.getHeight());
	}
}

/*
 * --INFO--
 * Address:	801AFB40
 * Size:	000014
 */
void P2DGrafContext::scissor(const PUTRect& rect)
{
	_10 = rect;
}

/*
 * --INFO--
 * Address:	801AFB54
 * Size:	000024
 */
void P2DGrafContext::place(const PUTRect& position)
{
	_08 = position;
	_10 = position;
}

/*
 * --INFO--
 * Address:	801AFB78
 * Size:	0000AC
 */
void P2DGrafContext::setColor(Colour& p1, Colour& p2, Colour& p3, Colour& p4)
{
	_18 = p1;
	_1C = p2;
	_20 = p3;
	_24 = p4;

	_B0 = 1;
	_B4 = 4;
	_B8 = 5;

	_BC = 1;
	_C0 = 4;
	_C4 = 5;

	_C8 = 1;
	_CC = 4;
	_D0 = 5;

	if (_18.a != 255) {
		return;
	}
	_B0 = 0;
	_B4 = 1;
	_B8 = 0;

	if (_20.a != 255) {
		return;
	}

	_BC = 0;
	_C0 = 1;
	_C4 = 0;

	if (_1C.a == 255 && _24.a == 255) {
		_C8 = 0;
		_CC = 1;
		_D0 = 0;
	}
}

/*
 * --INFO--
 * Address:	801AFC24
 * Size:	00002C
 */
void P2DGrafContext::setLineWidth(u8 width)
{
	mLineWidth = width;
	GXSetLineWidth(mLineWidth, GX_TO_ZERO);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00016C
 */
void P2DGrafContext::fillBox(const PUTRect&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000DC
 */
void P2DGrafContext::drawFrame(const PUTRect&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000B0
 */
void P2DGrafContext::line(PUTPoint, PUTPoint)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A4
 */
void P2DGrafContext::lineTo(PUTPoint)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0001D0
 */
void P2DGrafContext::polyline(PUTPoint*, int)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0001E4
 */
void P2DGrafContext::polyline(int*, int)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0001F8
 */
void P2DGrafContext::polylineTo(PUTPoint*, int)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000218
 */
void P2DGrafContext::polylineTo(int*, int)
{
	// UNUSED FUNCTION
}
