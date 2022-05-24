#include <mgl/mglpch.hpp>
#include <mgl/mgl.hpp>

namespace mgl
{
    class ExLayer : public Layer
    {
    public:

        ExLayer() : Layer("test layer") {}

        void onUpdate() override
        {
        }

        void onEvent(Event& e) override
        {
        }

        void onAttach() override
        {
            MGL_INFO("attached to layer stack");
        }

        void onDetach() override
        {
            MGL_INFO("Detached from layer stack");
        }
    };

    class Sandbox : public Application
    {
    public:

        Sandbox()
        {
            pushLayer(new ExLayer());
            pushOverlay(new ImGuiLayer());
        }

        ~Sandbox()
        {

        }
    };

    Application* createApplication()
    {
        return new Sandbox();
    }
}