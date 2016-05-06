/*
 VPDFDocument implementation
*/

#include "VPDFDocument.h"
#include "VPDFPage.h"
#include "VPDFOutline.h"
#include "VPDFEncoding.h"
#include "VPDFImage.h"
#include <stdio.h> //for NULL definition

using namespace XBOX;

VError  __stdcall ErrorHandlerFunc(HPDF_STATUS s1, HPDF_STATUS s2, void* e)
{
	return s1;
}

VPDFDocument::VPDFDocument()
{
	fDocHandle = HPDF_New((HPDF_Error_Handler)(NULL), NULL);
	fCurrentPage = nullptr;
}

VPDFDocument::~VPDFDocument()
{
	HPDF_Free(fDocHandle);
}

VPDFPage* VPDFDocument::AddPage(  VError& outError )
{
	VPDFPage* pdfPage = nullptr;
	
	HPDF_Page hPage =  HPDF_AddPage ( fDocHandle );
	outError = HPDF_GetError( fDocHandle );
	if (outError == VE_OK )
	{
		pdfPage = VPDFPage::CreatePage (hPage);

		if(pdfPage  != nullptr )
		{
			pdfPage->fDocParent = fDocHandle;
		}
	}
	
	return pdfPage;
}

VError VPDFDocument::AddPageLabel ( uLONG inPageNumber, ePDFPageNumStyle inPageNumStyle, uLONG inFirstPage , const uBYTE* inPrefix )
{
	VError error = VE_OK;
	
	error = HPDF_AddPageLabel (fDocHandle,inPageNumber,inPageNumStyle,inFirstPage,(const char*)inPrefix);	

	return error;
}

VPDFOutline* VPDFDocument::CreateOutline ( VPDFOutline* inParent, const uBYTE* inTitle, VPDFEncoder* inEncoder, XBOX::VError& outError )
{
	VPDFOutline* rOutLine = new VPDFOutline();
	rOutLine->fOutlineHandle = HPDF_CreateOutline(fDocHandle,inParent->fOutlineHandle,(const char*) inTitle,inEncoder->fEncoderHandle);
	outError = HPDF_GetError( fDocHandle );

	return rOutLine;
}

VPDFPage* VPDFDocument::CreatePage( XBOX::VError& outError )
{
	VPDFPage* pdfPage = AddPage( outError );
	return pdfPage;
}

VPDFEncoder* VPDFDocument::GetCurrentEncoder (VError& outError )
{

	VPDFEncoder* encoder = new VPDFEncoder();
	encoder->fEncoderHandle = HPDF_GetCurrentEncoder(fDocHandle );
	outError = HPDF_GetError( fDocHandle );
	if ( outError != VE_OK )
	{
		delete encoder;
	}

	return encoder;
}

VPDFPage* VPDFDocument::GetCurrentPage(  )
{
	return fCurrentPage;
}

VPDFEncoder* VPDFDocument::GetEncoder(const uBYTE* inEncodingName, VError& outError )
{
	VPDFEncoder* vEncoder = nullptr;
	HPDF_Encoder hEncoder = HPDF_GetEncoder(fDocHandle,(const char*)inEncodingName );
	outError = HPDF_GetError( fDocHandle );
	if (hEncoder == nullptr && outError == VE_OK )
	{
		vEncoder = new VPDFEncoder(hEncoder);
	}

	return vEncoder;
}

VPDFFont* VPDFDocument::GetFont (const uBYTE* inFontName , const uBYTE* inEncondingName, XBOX::VError& outError)
{
	VPDFFont* vFont = nullptr;
	HPDF_Font hFont =  HPDF_GetFont( fDocHandle,(const char*)inFontName, (const char*)inEncondingName );
	outError =  HPDF_GetError(fDocHandle);

	if (hFont && (outError == VE_OK) )
	{
		vFont = new VPDFFont(hFont);
	}

	return vFont;
}

VPDFPage* VPDFDocument::InsertPage( const VPDFPage& inTargetPage)
{
	VPDFPage* vPage =  nullptr;
	HPDF_Page hTargetPage = inTargetPage.fPageHandle;
	if (hTargetPage != nullptr)
	{
		HPDF_Page hPage =  HPDF_InsertPage ( fDocHandle, hTargetPage );
		VError err = HPDF_GetError ( fDocHandle ) ;
		if (!err && hPage )
		{
			vPage = VPDFPage::CreatePage(hPage);
		}

	}

	return vPage;
}

VPDFImage* VPDFDocument::LoadPngImage (const uBYTE* inImgFileName , VError& outError )
{
	VPDFImage* vImage = nullptr;
	HPDF_Image hImage = HPDF_LoadPngImageFromFile ( fDocHandle, (const char*)inImgFileName );
	outError = HPDF_GetError( fDocHandle );
	if (!outError && hImage )
	{
		vImage = new VPDFImage( hImage );
	}

	return vImage;
}

VError VPDFDocument::Save(uBYTE *inFileName)
{
	VError err = VE_OK;
	
	err = HPDF_SaveToFile ( fDocHandle , (const char*)inFileName );


	return err;
}

VError VPDFDocument::SetPassword ( const uBYTE* inOwnerPwd, const uBYTE* inUserPwd )
{
	return HPDF_SetPassword ( fDocHandle,(const char*)inOwnerPwd , (const char*)inUserPwd );
}
