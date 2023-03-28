/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once


#include <GeUI/Panels/PanelWindow.h>
#include <GeUI/Widgets/Visual/Image.h>
#include <GeRendering/Buffers/UniformBuffer.h>
#include <GeRendering/Buffers/Framebuffer.h>
#include <GeRendering/LowRenderer/Camera.h>

namespace GeEditor::Core { class EditorRenderer; }

namespace GeEditor::Panels
{
	/**
	* Base class for any view
	*/
	class AView : public GeUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		AView
		(
			const std::string& p_title,
			bool p_opened,
			const GeUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Update the view
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime);

		/**
		* Custom implementation of the draw method
		*/
		void _Draw_Impl() override;

		/**
		* Custom implementation of the render method to define in dervied classes
		*/
		virtual void _Render_Impl() = 0;

		/**
		* Render the view
		*/
		void Render();

		/**
		* Defines the camera position
		* @param p_position
		*/
		void SetCameraPosition(const GeMaths::FVector3& p_position);

		/**
		* Defines the camera rotation
		* @param p_rotation
		*/
		void SetCameraRotation(const GeMaths::FQuaternion& p_rotation);

		/**
		* Returns the camera position
		*/
		const GeMaths::FVector3& GetCameraPosition() const;

		/**
		* Returns the camera rotation
		*/
		const GeMaths::FQuaternion& GetCameraRotation() const;

		/**
		* Returns the camera used by this view
		*/
		GeRendering::LowRenderer::Camera& GetCamera();

		/**
		* Returns the size of the panel ignoring its titlebar height
		*/
		std::pair<uint16_t, uint16_t> GetSafeSize() const;

		/**
		* Returns the grid color of the view
		*/
		const GeMaths::FVector3& GetGridColor() const;

		/**
		* Defines the grid color of the view
		* @param p_color
		*/
		void SetGridColor(const GeMaths::FVector3& p_color);

		/**
		* Fill the UBO using the view settings
		*/
		void FillEngineUBO();

	protected:
		/**
		* Update camera matrices
		*/
		void PrepareCamera();

	protected:
		GeEditor::Core::EditorRenderer& m_editorRenderer;
		GeRendering::LowRenderer::Camera m_camera;
		GeMaths::FVector3 m_cameraPosition;
		GeMaths::FQuaternion m_cameraRotation;
		GeUI::Widgets::Visual::Image* m_image;

        GeMaths::FVector3 m_gridColor = GeMaths::FVector3 { 0.176f, 0.176f, 0.176f };

		GeRendering::Buffers::Framebuffer m_fbo;
	};
}