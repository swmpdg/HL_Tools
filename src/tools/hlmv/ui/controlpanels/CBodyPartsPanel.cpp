#include <wx/gbsizer.h>

#include "../CHLMV.h"
#include "../../CHLMVState.h"

#include "studiomodel/StudioModel.h"

#include "CBodyPartsPanel.h"

namespace hlmv
{
wxBEGIN_EVENT_TABLE( CBodyPartsPanel, CBaseControlPanel )
	EVT_COMBOBOX( wxID_BODY_BODYPARTS, CBodyPartsPanel::BodypartChanged )
	EVT_COMBOBOX( wxID_BODY_SUBMODELS, CBodyPartsPanel::SubmodelChanged )
	EVT_COMBOBOX( wxID_BODY_SKIN, CBodyPartsPanel::SkinChanged )
	EVT_COMBOBOX( wxID_BODY_CONTROLLER, CBodyPartsPanel::ControllerChanged )
	EVT_SLIDER( wxID_BODY_CONTROLLER_SLIDER, CBodyPartsPanel::ControllerSliderChanged )
wxEND_EVENT_TABLE()

CBodyPartsPanel::CBodyPartsPanel( wxWindow* pParent, CHLMV* const pHLMV )
	: CBaseControlPanel( pParent, "Body Parts", pHLMV )
{
	wxWindow* const pElemParent = GetBox();

	m_pBodypart = new wxComboBox( pElemParent, wxID_BODY_BODYPARTS, "", wxDefaultPosition, wxSize( COMBOBOX_WIDTH, wxDefaultSize.GetY() ) );
	m_pBodypart->SetEditable( false );

	wxStaticText* pBodypart = new wxStaticText( pElemParent, wxID_ANY, "Part" );

	m_pSubmodel = new wxComboBox( pElemParent, wxID_BODY_SUBMODELS, "", wxDefaultPosition, wxSize( COMBOBOX_WIDTH, wxDefaultSize.GetY() ) );
	m_pSubmodel->SetEditable( false );

	wxStaticText* pSubmodel = new wxStaticText( pElemParent, wxID_ANY, "Sub-model" );

	m_pSkin = new wxComboBox( pElemParent, wxID_BODY_SKIN, "", wxDefaultPosition, wxSize( COMBOBOX_WIDTH, wxDefaultSize.GetY() ) );
	m_pSkin->SetEditable( false );

	wxStaticText* pSkin = new wxStaticText( pElemParent, wxID_ANY, "Skin" );

	m_pController = new wxComboBox( pElemParent, wxID_BODY_CONTROLLER, "", wxDefaultPosition, wxSize( COMBOBOX_WIDTH, wxDefaultSize.GetY() ) );
	m_pController->SetEditable( false );

	wxStaticText* pController = new wxStaticText( pElemParent, wxID_ANY, "Controller" );

	m_pControllerSlider = new wxSlider( pElemParent, wxID_BODY_CONTROLLER_SLIDER, CONTROLLER_SLIDER_DEFAULT, CONTROLLER_SLIDER_MIN, CONTROLLER_SLIDER_MAX );

	wxStaticText* pControllerSlider = new wxStaticText( pElemParent, wxID_ANY, "Value" );

	m_pModelInfo = new wxPanel( pElemParent );

	m_pBones = new wxStaticText( m_pModelInfo, wxID_ANY, "Bones: Undefined" );
	m_pBoneControllers = new wxStaticText( m_pModelInfo, wxID_ANY, "Bone Controllers: Undefined" );
	m_pHitBoxes = new wxStaticText( m_pModelInfo, wxID_ANY, "Hit Boxes: Undefined" );
	m_pSequences = new wxStaticText( m_pModelInfo, wxID_ANY, "Sequences: Undefined" );
	m_pSequenceGroups = new wxStaticText( m_pModelInfo, wxID_ANY, "Sequence Groups: Undefined" );

	m_pTextures = new wxStaticText( m_pModelInfo, wxID_ANY, "Textures: Undefined" );
	m_pSkinFamilies = new wxStaticText( m_pModelInfo, wxID_ANY, "Skin Families: Undefined" );
	m_pBodyparts = new wxStaticText( m_pModelInfo, wxID_ANY, "Bodyparts: Undefined" );
	m_pAttachments = new wxStaticText( m_pModelInfo, wxID_ANY, "Attachments: Undefined" );
	m_pTransitions = new wxStaticText( m_pModelInfo, wxID_ANY, "Transitions: Undefined" );

	//Layout
	wxGridBagSizer* pSizer = new wxGridBagSizer( 5, 5 );

	pSizer->Add( m_pBodypart, wxGBPosition( 0, 0 ), wxDefaultSpan, wxCENTER );
	pSizer->Add( pBodypart, wxGBPosition( 0, 1 ), wxDefaultSpan, wxCENTER | wxALIGN_LEFT );

	pSizer->Add( m_pSubmodel, wxGBPosition( 1, 0 ), wxDefaultSpan, wxCENTER );
	pSizer->Add( pSubmodel, wxGBPosition( 1, 1 ), wxDefaultSpan, wxCENTER | wxALIGN_LEFT );

	pSizer->Add( m_pSkin, wxGBPosition( 2, 0 ), wxDefaultSpan, wxCENTER );
	pSizer->Add( pSkin, wxGBPosition( 2, 1 ), wxDefaultSpan, wxCENTER | wxALIGN_LEFT );

	pSizer->Add( m_pController, wxGBPosition( 0, 2 ), wxDefaultSpan, wxCENTER );
	pSizer->Add( pController, wxGBPosition( 0, 3 ), wxDefaultSpan, wxCENTER | wxALIGN_LEFT );

	pSizer->Add( m_pControllerSlider, wxGBPosition( 1, 2 ), wxDefaultSpan, wxCENTER );
	pSizer->Add( pControllerSlider, wxGBPosition( 1, 3 ), wxDefaultSpan, wxCENTER | wxALIGN_LEFT );

	//Info text
	wxGridBagSizer* pInfoSizer = new wxGridBagSizer( 5, 5 );

	pInfoSizer->Add( m_pBones, wxGBPosition( 0, 0 ), wxDefaultSpan, wxEXPAND );
	pInfoSizer->Add( m_pBoneControllers, wxGBPosition( 1, 0 ), wxDefaultSpan, wxEXPAND );
	pInfoSizer->Add( m_pHitBoxes, wxGBPosition( 2, 0 ), wxDefaultSpan, wxEXPAND );
	pInfoSizer->Add( m_pSequences, wxGBPosition( 3, 0 ), wxDefaultSpan, wxEXPAND );
	pInfoSizer->Add( m_pSequenceGroups, wxGBPosition( 4, 0 ), wxDefaultSpan, wxEXPAND );

	pInfoSizer->Add( m_pTextures, wxGBPosition( 0, 1 ), wxDefaultSpan, wxEXPAND );
	pInfoSizer->Add( m_pSkinFamilies, wxGBPosition( 1, 1 ), wxDefaultSpan, wxEXPAND );
	pInfoSizer->Add( m_pBodyparts, wxGBPosition( 2, 1 ), wxDefaultSpan, wxEXPAND );
	pInfoSizer->Add( m_pAttachments, wxGBPosition( 3, 1 ), wxDefaultSpan, wxEXPAND );
	pInfoSizer->Add( m_pTransitions, wxGBPosition( 4, 1 ), wxDefaultSpan, wxEXPAND );

	m_pModelInfo->SetSizer( pInfoSizer );

	pSizer->Add( m_pModelInfo, wxGBPosition( 0, 4 ), wxGBSpan( 3, 2 ), wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN );

	GetBoxSizer()->Add( pSizer );
}

CBodyPartsPanel::~CBodyPartsPanel()
{
}

void CBodyPartsPanel::InitializeUI()
{
	m_pBodypart->Clear();
	m_pSubmodel->Clear();
	m_pSkin->Clear();
	m_pController->Clear();

	bool bSuccess = false;

	if( auto pModel = m_pHLMV->GetState()->GetStudioModel() )
	{
		const studiohdr_t* const pHdr = pModel->getStudioHeader();

		if( pHdr )
		{
			const mstudiobodyparts_t* const pbodyparts = ( mstudiobodyparts_t* ) ( ( byte* ) pHdr + pHdr->bodypartindex );

			wxArrayString names;

			if( pHdr->numbodyparts > 0 )
			{
				m_pBodypart->Enable( true );

				for( int i = 0; i < pHdr->numbodyparts; ++i )
					names.Add( pbodyparts[ i ].name );

				m_pBodypart->Append( names );

				m_pBodypart->Select( 0 );

				SetBodypart( 0 );

				names.Clear();
			}
			else
			{
				m_pBodypart->Enable( false );
				m_pSubmodel->Enable( false );
			}

			m_pSkin->Enable( pHdr->numskinfamilies > 0 );

			for( int i = 0; i < pHdr->numskinfamilies; ++i )
			{
				names.Add( wxString::Format( "Skin %d", i + 1 ) );
			}

			m_pSkin->Append( names );

			SetSkin( 0 );

			names.Clear();

			m_pController->Enable( pHdr->numbonecontrollers > 0 );
			m_pControllerSlider->Enable( pHdr->numbonecontrollers > 0 );

			const mstudiobonecontroller_t* const pbonecontrollers = ( mstudiobonecontroller_t* ) ( ( byte* ) pHdr + pHdr->bonecontrollerindex );

			for( int i = 0; i < pHdr->numbonecontrollers; i++ )
			{
				if( pbonecontrollers[ i ].index == CONTROLLER_MOUTH_INDEX )
				{
					names.Add( "Mouth" );
				}
				else
				{
					names.Add( wxString::Format( "Controller %d", pbonecontrollers[ i ].index ) );
				}
			}

			m_pController->Append( names );

			const studiohdr_t* const pTexHdr = pModel->getTextureHeader();

			SetModelInfo( *pHdr, *pTexHdr );

			m_pModelInfo->Show( true );

			bSuccess = true;
		}
	}

	if( !bSuccess )
	{
		m_pBodypart->Enable( false );
		m_pSubmodel->Enable( false );
		m_pSkin->Enable( false );
		m_pController->Enable( false );

		studiohdr_t dummyHdr;

		memset( &dummyHdr, 0, sizeof( dummyHdr ) );

		SetModelInfo( dummyHdr, dummyHdr );
		m_pModelInfo->Show( false );
	}

	SetController( 0 );
}

void CBodyPartsPanel::BodypartChanged( wxCommandEvent& event )
{
	SetBodypart( m_pBodypart->GetSelection() );
}

void CBodyPartsPanel::SubmodelChanged( wxCommandEvent& event )
{
	SetSubmodel( m_pSubmodel->GetSelection() );
}

void CBodyPartsPanel::SkinChanged( wxCommandEvent& event )
{
	SetSkin( m_pSkin->GetSelection() );
}

void CBodyPartsPanel::ControllerChanged( wxCommandEvent& event )
{
	SetController( m_pController->GetSelection() );
}

void CBodyPartsPanel::ControllerSliderChanged( wxCommandEvent& event )
{
	SetControllerValue( m_pController->GetSelection(), m_pControllerSlider->GetValue() );
}

void CBodyPartsPanel::SetBodypart( int iIndex )
{
	const studiohdr_t* const pHdr = m_pHLMV->GetState()->GetStudioModel()->getStudioHeader();

	if( !pHdr )
	{
		m_pBodypart->Select( 0 );
		return;
	}

	if( iIndex < 0 || iIndex >= pHdr->numbodyparts )
		iIndex = 0;

	m_pBodypart->Select( iIndex );

	if( iIndex < pHdr->numbodyparts )
	{
		const mstudiobodyparts_t* const pbodyparts = ( mstudiobodyparts_t* ) ( ( byte* ) pHdr + pHdr->bodypartindex );

		UpdateSubmodels( iIndex );
	}
}

void CBodyPartsPanel::SetSubmodel( int iIndex )
{
	m_pSubmodel->Select( iIndex );
	m_pHLMV->GetState()->GetStudioModel()->SetBodygroup( m_pBodypart->GetSelection(), iIndex );
}

void CBodyPartsPanel::SetSkin( int iIndex )
{
	m_pSkin->Select( iIndex );
	m_pHLMV->GetState()->GetStudioModel()->SetSkin( iIndex );
}

void CBodyPartsPanel::UpdateSubmodels( const int iIndex )
{
	m_pSubmodel->Clear();

	const studiohdr_t* const pHdr = m_pHLMV->GetState()->GetStudioModel()->getStudioHeader();

	if( !pHdr )
	{
		m_pSubmodel->Enable( false );
		return;
	}

	m_pSubmodel->Enable( true );

	if( iIndex < pHdr->numbodyparts )
	{
		const mstudiobodyparts_t* const pbodyparts = ( mstudiobodyparts_t* ) ( ( byte* ) pHdr + pHdr->bodypartindex );

		char szBuffer[ 64 ];

		for( int i = 0; i < pbodyparts[ iIndex ].nummodels; i++ )
		{
			snprintf( szBuffer, sizeof( szBuffer ), "Submodel %d", i + 1 );
			m_pSubmodel->Append( szBuffer );
		}

		m_pSubmodel->Select( 0 );
	}
}

void CBodyPartsPanel::SetModelInfo( const studiohdr_t& hdr, const studiohdr_t& texHdr )
{
	m_pBones			->SetLabelText( wxString::Format( "Bones: %d", hdr.numbones ) );
	m_pBoneControllers	->SetLabelText( wxString::Format( "Bone Controllers: %d", hdr.numbonecontrollers ) );
	m_pHitBoxes			->SetLabelText( wxString::Format( "Hit Boxes: %d", hdr.numhitboxes ) );
	m_pSequences		->SetLabelText( wxString::Format( "Sequences: %d", hdr.numseq ) );
	m_pSequenceGroups	->SetLabelText( wxString::Format( "Sequence Groups: %d", hdr.numseqgroups ) );

	m_pTextures			->SetLabelText( wxString::Format( "Textures: %d", texHdr.numtextures ) );
	m_pSkinFamilies		->SetLabelText( wxString::Format( "Skin Families: %d", hdr.numskinfamilies ) );
	m_pBodyparts		->SetLabelText( wxString::Format( "Bodyparts: %d", hdr.numbodyparts ) );
	m_pAttachments		->SetLabelText( wxString::Format( "Attachments: %d", hdr.numattachments ) );
	m_pTransitions		->SetLabelText( wxString::Format( "Transitions: %d", hdr.numtransitions ) );
}

void CBodyPartsPanel::SetController( int iIndex )
{
	auto pModel = m_pHLMV->GetState()->GetStudioModel();

	if( !pModel || !pModel->getStudioHeader() || pModel->getStudioHeader()->numbonecontrollers == 0 )
	{
		//Disable and center it.
		m_pControllerSlider->Enable( false );
		m_pControllerSlider->SetRange( 0, 2 );
		m_pControllerSlider->SetValue( 1 );
		return;
	}

	const studiohdr_t* const pHdr = pModel->getStudioHeader();

	if( iIndex < 0 || iIndex >= pHdr->numbonecontrollers )
		iIndex = 0;

	const mstudiobonecontroller_t* const pbonecontrollers = ( mstudiobonecontroller_t* ) ( ( byte* ) pHdr + pHdr->bonecontrollerindex );

	m_pController->Select( iIndex );
	m_pControllerSlider->SetRange( ( int ) pbonecontrollers[ iIndex ].start, ( int ) pbonecontrollers[ iIndex ].end );
	m_pControllerSlider->SetValue( m_pHLMV->GetState()->GetStudioModel()->GetController( iIndex ) );
	m_pControllerSlider->Enable( true );
}

void CBodyPartsPanel::SetControllerValue( int iIndex, int iValue )
{
	auto pModel = m_pHLMV->GetState()->GetStudioModel();

	if( !pModel )
		return;

	const studiohdr_t* const pHdr = pModel->getStudioHeader();

	if( pHdr )
	{
		if( iIndex < 0 || iIndex >= pHdr->numbonecontrollers )
			return;

		const mstudiobonecontroller_t* const pbonecontrollers = ( mstudiobonecontroller_t* ) ( ( byte* ) pHdr + pHdr->bonecontrollerindex );

		if( pbonecontrollers[ iIndex ].index == CONTROLLER_MOUTH_INDEX )
			m_pHLMV->GetState()->GetStudioModel()->SetMouth( iValue );
		else
			m_pHLMV->GetState()->GetStudioModel()->SetController( pbonecontrollers[ iIndex ].index, iValue );
	}
}
}