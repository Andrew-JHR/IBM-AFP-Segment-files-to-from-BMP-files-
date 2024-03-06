// ShowSegmentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShowSegment.h"
#include "ShowSegmentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowSegmentDlg dialog

CShowSegmentDlg::CShowSegmentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowSegmentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowSegmentDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowSegmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowSegmentDlg)
	DDX_Control(pDX, IDC_OFILE, m_oFile);
	DDX_Control(pDX, IDC_FILE, m_File);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShowSegmentDlg, CDialog)
	//{{AFX_MSG_MAP(CShowSegmentDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOW, OnShow)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowSegmentDlg message handlers

BOOL CShowSegmentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
////Andrewj/////////////////////////////////////////////////////////////
	
	m_File.SetWindowText("d:\\s1cobtpe");	// display the default input file name
	m_oFile.SetWindowText("d:\\s1cobtpe.bmp"); // display the default output file name

////Andrewj/////////////////////////////////////////////////////////////
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShowSegmentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShowSegmentDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShowSegmentDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShowSegmentDlg::OnShow() 
{
	void xcode(unsigned char *,int);


	CString infile = "D:\\s1cobtpe.bin";

	CString outfile = "d:\\s1cobtpe.bmp";

	m_File.GetWindowText(infile);	// get the segment (image) file name input by the user
	m_oFile.GetWindowText(outfile); // get the bmp file name

	
	ifstream input;
	ofstream output;
    unsigned char ch[4];
	union                                      // input image file maps
	{
		unsigned char buffer[5006];
		struct
		{
			char        structure[3];
			unsigned char rec_seq[3];
			union
			{
				struct      //Image Input Descriptor
				{
					char IID_skip[18];
					unsigned char IID_width[2];
					unsigned char IID_height[2];
				};
				unsigned char IRD[5000];    // Image Raster Data
			};
		};
		
	};
	
	unsigned short int  RecLen;					// field to keep every record's length
	int ImageWidth, ImageHeight ;				// The width & height of the image in this page segment file
//	unsigned char ImageBfr[20000];				// buffer to contain all bytes for the image
//	unsigned char * ImageBfr_P = ImageBfr ;     // pointer to the image buffer
	unsigned char * ImageBfr_P, * ImageBfr_S ;
	unsigned char * IRD_P ;						// pointer to the Image Raster Data record

    input.open(infile,ios::binary | ios::nocreate);		// open the page segment file
	if (!input)
	{
		AfxMessageBox(" Open Input File Error ! ") ;	// error message
		return;
	}

	for ( ; ; )
	{
		input.read(ch,3);								// read in the record length and the control byte
		if ( ch[0] != 'Z' )
		{
			AfxMessageBox(" Invalid file format ! ") ;	// error message
			return;
		}

		RecLen = ch[1] * 0x100 + ch[2] ;				// calculate the record length

		input.read(buffer,RecLen-2);					// read in a record

 
		if (strncmp(structure,(const char *)Image_Input_Desc,sizeof(structure)) == 0)
		{

		    ImageWidth  = IID_width[0]  * 0x100 + IID_width[1] ;
			ImageHeight = IID_height[0] * 0x100 + IID_height[1];
			ImageBfr_S = new unsigned char [ImageWidth*ImageHeight/8];
			ImageBfr_P = ImageBfr_S;
		}

		if (strncmp(structure,(const char *)Image_Raster_Data,sizeof(structure)) == 0)
		{
 			IRD_P = IRD;
			for (int i=0 ; i < (RecLen - 8) ; i++, ImageBfr_P++, IRD_P++)
				*ImageBfr_P = *IRD_P;

		}

	
		if (strncmp(structure,(const char *)End_Image,sizeof(structure)) == 0)	// End of Image is reached
			break;
			
	}		// end of the input record reading loop 
	


	output.open(outfile,ios::binary);
	if (!output)
	{
		AfxMessageBox(" Please End the last MSPAINT Window first !") ;
		return;
	}  

	BMPhdr * BMPP = new BMPhdr[1];
	BMPP->bm = 0x4d42;   // 'BM' 
	BMPP->filesize = sizeof(BMPhdr) + ImageWidth * ImageHeight * 3 ;
	BMPP->color = BMPP->impcolor = BMPP->comprs = BMPP->rsvr =0; 
	BMPP->bmpofst = sizeof(BMPhdr); 
	BMPP->bmphdsz = 0x28;      //Windows 95, NT
	BMPP->height = ImageHeight;
	BMPP->width =  ImageWidth;
	BMPP->planes = 1;
	BMPP->bitpix = 24;
	BMPP->bmpsize = ImageWidth * ImageHeight * 3 ;
	BMPP->hres = BMPP->vres = 0xb6d;
	BMPP->hres = BMPP->vres = 0;

	output.write((const char *)BMPP, sizeof(BMPhdr));

	delete[] BMPP;  

	int i,j,k;
	const unsigned char lowvalue[4] = {0x00,0x00,0x00,0x00};
	const unsigned char highvalue[4] = {0xff,0xff,0xff,0xff};

	
//	ImageBfr_P = ImageBfr + (ImageHeight-1)*ImageWidth/8 ;
	ImageBfr_P = ImageBfr_S + (ImageHeight-1)*ImageWidth/8;

	for (i = 0 ; i < ImageHeight ; i++)
	{
		unsigned char * ImageBfr_Q = ImageBfr_P;
		for (j = 0 ; j < ImageWidth/8 ; j++)
		{
			for (k = 0 ; k < 8 ; k++)
			{
				if ( *ImageBfr_Q & (0x80 >> k))
					output.write(lowvalue,3);
				else
					output.write(highvalue,3);
			}
			ImageBfr_Q ++ ;
		}
		ImageBfr_P -= ImageWidth/8;
	} 
	
	delete [] ImageBfr_S ; 
    
	output.close() ;
	input.close();

	spawnlp(P_NOWAIT,"Mspaint.exe","Mspaint.exe",outfile,NULL);
	
}

void xcode(unsigned char* bufptr, int len)
{
	for (int i=0 ; i < len ; i++)
	{
		*bufptr = b2a[(*bufptr)];
		bufptr++ ;
	}
	*bufptr = '\0';
}

void CShowSegmentDlg::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}
