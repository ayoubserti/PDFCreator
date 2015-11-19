
#ifndef _VPDF_IMAGE_
#define _VPDF_IMAGE_
#include "VPDFDocument.h"
class VPDFImage
{
	friend class VPDFDocument;

private:
	VPDFImage();
	VPDFImage (HPDF_Image hImage) : fImageHandle(hImage){};

	HPDF_Image fImageHandle;
};

#endif