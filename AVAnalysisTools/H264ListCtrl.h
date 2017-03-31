#pragma once


// CH264ListCtrl
class CAVAnalysisToolsDlg; 
class CH264ListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CH264ListCtrl)

public:
	CH264ListCtrl(CAVAnalysisToolsDlg *pToolDlg);
	virtual ~CH264ListCtrl();
private:
	CAVAnalysisToolsDlg *m_pToolDlg;
protected:
	DECLARE_MESSAGE_MAP()
};


