
#ifndef _VPDF_ENCODING_
#define _VPDF_ENCODING_

#include "VPDFDocument.h"

class VPDFFont {
	friend class VPDFDocument;
	friend class VPDFPage;
private:
	VPDFFont(){};
	VPDFFont(HPDF_Font hFont): fFontHandle(hFont){};

	HPDF_Font fFontHandle;
};

class VPDFEncoder {

	
	friend class VPDFDocument;
private:

	VPDFEncoder(){};
	VPDFEncoder(HPDF_Encoder inHEncoder):fEncoderHandle(inHEncoder){};

	HPDF_Encoder fEncoderHandle;
	
};
#endif