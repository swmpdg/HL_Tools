#ifndef CONTROLPANELS_CBASECONTROLPANEL_H
#define CONTROLPANELS_CBASECONTROLPANEL_H

#include "../wxHLMV.h"

#include <wx/sizer.h>

#include "../MouseOpFlag.h"

namespace studiomdl
{
class IStudioModelRenderer;
struct CModelRenderInfo;
}

namespace hlmv
{
class CModelViewerApp;

class CBaseControlPanel : public wxPanel
{
public:
	virtual ~CBaseControlPanel();

	const wxString& GetPanelName() const { return m_szName; }

	const CModelViewerApp* GetHLMV() const { return m_pHLMV; }
	CModelViewerApp* GetHLMV() { return m_pHLMV; }

	/**
	*	Returns a bit vector containing all of the allowed mouse operations.
	*	Implemented as a virtual to allow for dynamic changes to the allowed operations.
	*/
	virtual MouseOpFlags_t GetAllowedMouseOperations() const { return MOUSEOPF_ALL; }

	virtual void InitializeUI() {}

	//Called right before the 3D view is updated.
	virtual void ViewPreUpdate() {}

	//Called when the 3D view is drawing.
	virtual void Draw3D( const wxSize& size ) {}

	virtual void OnPostDraw( studiomdl::IStudioModelRenderer& renderer, const studiomdl::CModelRenderInfo& info ) {}

	//Called every time the 3D view is updated.
	virtual void ViewUpdated() {}

	//Called when the panel becomes the active panel.
	virtual void PanelActivated() {}

	//Called when the panel is no longer the active panel.
	virtual void PanelDeactivated() {}

protected:
	CBaseControlPanel( wxWindow* pParent, const wxString& szName, CModelViewerApp* const pHLMV );

	/**
	*	Gets the window to use as the direct parent for child elements.
	*/
	wxWindow* GetElementParent() { return this; }

	/**
	*	Gets the main sizer to add elements to.
	*/
	wxSizer* GetMainSizer() { return m_pMainSizer; }

protected:
	CModelViewerApp* const m_pHLMV;

private:
	const wxString m_szName;

	wxBoxSizer* m_pMainSizer;

private:
	CBaseControlPanel( const CBaseControlPanel& ) = delete;
	CBaseControlPanel& operator=( const CBaseControlPanel& ) = delete;
};
}

#endif //CONTROLPANELS_CBASECONTROLPANEL_H