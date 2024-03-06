#include "stdafx.h"
#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "time.h"

const unsigned char asc2ebc[128] = {                //ASCII to EBCDIC  
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,	//00 - 07
		0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,	//08 - 0f
		0x10,0x11,0x12,0x13,0x14,0x0A,0x16,0x17,	//10 - 17
		0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,	//18 - 1f
		0x40,0x5a,0x7f,0x7b,0x5b,0x6c,0x50,0x7d,	//20 - 27
		0x4d,0x5d,0x5c,0x4e,0x6b,0x60,0x4b,0x61,	//28 - 2f	( ) * + , - . /
		0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,	//30 - 37	0 1 2 3 4 5 6 7  
		0xf8,0xf9,0x7a,0x5e,0x4c,0x7e,0x6e,0x6f,	//38 - 3f	8 9 : ; < = > ?	
		0x7c,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,	//40 - 47	& A B C D E F G
		0xc8,0xc9,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,	//48 - 4f	H I J K L M N O
		0xd7,0xd8,0xd9,0xe2,0xe3,0xe4,0xe5,0xe6,	//50 - 57	P Q R S T U V W
		0xe7,0xe8,0xe9,0x41,0x42,0x43,0x44,0x6d,	//58 - 5f	X Y Z         _
		0x47,0x81,0x82,0x83,0x84,0x85,0x86,0x87,	//60 - 67     a b c d e f g 
		0x88,0x89,0x91,0x92,0x93,0x94,0x95,0x96,	//68 - 6f	h i j k l m n o
		0x97,0x98,0x99,0xa2,0xa3,0xa4,0xa5,0xa6,	//70 - 77	p q r s t u v w
		0xa7,0xa8,0xa9,0x45,0x4f,0x46,0x48,0x07 } ;	//78 - 7f	x y z

const unsigned char Image_Comment[3]		 = {0xd3,0xee,0xee};
const unsigned char Begin_Page_Segment[3]	 = {0xd3,0xa8,0x5f};
const unsigned char Begin_Image[3]			 = {0xd3,0xa8,0x7b};
const unsigned char Image_Output_Control[3]  = {0xd3,0xa7,0x7b};
const unsigned char IOC_data[24]			 = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
												0x2d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	
												0x00,0x00,0x03,0xe8,0x03,0xe8,0xff,0xff};
const unsigned char Image_Input_Desc[3]		 = {0xd3,0xa6,0x7b};
const unsigned char IID_data_1[18]			 = {0x00,0x00,0x09,0x60,0x00,0x00,0x00,0x00,
												0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x60,
												0x09,0x60};
const unsigned char IID_data_2[14]			 = {0x00,0x00,0x00,0x00,0x2d,0x00,0x00,0x00,
												0x00,0x00,0x00,0x01,0xff,0xff}; 
const unsigned char Image_Raster_Data[3]     = {0xd3,0xee,0x7b}; 
const unsigned char End_Image[3]	         = {0xd3,0xa9,0x7b};
const unsigned char End_Page_Segment[3]		 = {0xd3,0xa9,0x5f};

const unsigned char lowvalue[4] = {0x00,0x00,0x00,0x00};

#pragma pack(push,1)					// Save previous alignment then set as Byte Alignment
		struct BMPhdr					// BMP file's standard header
		{							
			unsigned short int bm;		// CL2   identifier : 'BM' 
			unsigned int filesize;		// CL4   file size in bytes
			unsigned int rsvr;			// CL4   reserved
			unsigned int bmpofst;		// CL4   offset from beginning of file to the beginning of the bitmap data 
			unsigned int bmphdsz;		// CL4   length of the bitmap info header
			unsigned int width;			// CL4   horizontal width of bitmap in pixels 
			unsigned int height;		// CL4   vertical height of bitmap in pixels	
			unsigned short int planes;	// CL2   number of planes in this bitmap
			unsigned short int bitpix;	// CL2   24-bit or 32-bit or other color types 
			unsigned int comprs;		// CL4   compression spec.
			unsigned int bmpsize;		// CL4   bitmap size in bytes
			unsigned int hres;			// CL4   horizontal resolution in pixels per meter
			unsigned int vres;			// CL4   vertical resolution in pixels per meter
			unsigned int color;			// CL4   number of colors used
			unsigned int impcolor;		// CL4   number of important colors  
		};
#pragma pack(pop)				// Restore previous alignment
// Bmp2PsegDlg.h : header file
//

#if !defined(AFX_BMP2PSEGDLG_H__7715CF47_FB03_11D6_88F9_0050BA798998__INCLUDED_)
#define AFX_BMP2PSEGDLG_H__7715CF47_FB03_11D6_88F9_0050BA798998__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBmp2PsegDlg dialog

class CBmp2PsegDlg : public CDialog
{
// Construction
public:
	CBmp2PsegDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBmp2PsegDlg)
	enum { IDD = IDD_BMP2PSEG_DIALOG };
	CEdit	m_WHO;
	CEdit	m_PSEG;
	CEdit	m_BMP;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmp2PsegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBmp2PsegDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	afx_msg void OnXlat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMP2PSEGDLG_H__7715CF47_FB03_11D6_88F9_0050BA798998__INCLUDED_)
