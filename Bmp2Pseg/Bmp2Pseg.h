// Bmp2Pseg.h : main header file for the BMP2PSEG application
//

#if !defined(AFX_BMP2PSEG_H__7715CF45_FB03_11D6_88F9_0050BA798998__INCLUDED_)
#define AFX_BMP2PSEG_H__7715CF45_FB03_11D6_88F9_0050BA798998__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBmp2PsegApp:
// See Bmp2Pseg.cpp for the implementation of this class
//

class CBmp2PsegApp : public CWinApp
{
public:
	CBmp2PsegApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmp2PsegApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBmp2PsegApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMP2PSEG_H__7715CF45_FB03_11D6_88F9_0050BA798998__INCLUDED_)
