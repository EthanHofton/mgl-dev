#include <mgl/mglpch.hpp>
#include <mgl/mgl.hpp>
#include <imgui/imgui.h>

namespace mgl
{
    class DebugLayer : public ImGuiLayer
    {
    public:

        DebugLayer() : ImGuiLayer() {}

        void draw() override
        {
            ImGui::Begin("TEST WOOO");

            static bool checkBox = false;
            ImGui::Text("IT WORKS LES GOOOOOO");
            ImGui::Checkbox("Check this", &checkBox);

            ImGui::ShowMetricsWindow();

            ImGui::End();
        }
    };

    struct v
    {
        glm::vec3 pos;
        glm::vec4 col;
    };

    class ExLayer : public Layer
    {
    public:

        ExLayer() : Layer("test layer") {}

        void onUpdate() override
        {
            m_renderer1->pushData((void*)&m_triangle[0], m_triangle.size() * sizeof(v), (void*)&m_indices[0], m_indices.size() * sizeof(unsigned int));
            m_renderer1->draw();
        }

        void onEvent(Event& e) override
        {
            EventDispatcher dispatcher(e);
        }

        void onAttach() override
        {
            MGL_INFO("attached to layer stack");

            rendererProps renderer1Props("shaders/dev/base.vert", "shaders/dev/base.frag", MGL_TRIANGLES);
            renderer1Props.m_layout.push<3, MGL_FLOAT>();
            renderer1Props.m_layout.push<4, MGL_FLOAT>();

            m_triangle = {
                { {-0.5f+0.5f, 0.5f+0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
                { {-0.5f+0.5f,-0.5f+0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
                { { 0.5f+0.5f, 0.5f+0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
            };

            m_indices = {
                0,1,2,
            };

            m_renderer1 = Renderer::create(renderer1Props);
        }

        void onDetach() override
        {
            MGL_INFO("Detached from layer stack");

            delete m_renderer1;
        }

    private:

        Renderer* m_renderer1;
        std::vector<v> m_triangle;
        std::vector<unsigned int> m_indices;
    };

    class ExLayer2 : public Layer
    {
    public:

        ExLayer2() : Layer("test layer 2") {}

        void onUpdate() override
        {
            m_renderer2->pushData((void*)&m_triangle2[0], m_triangle2.size() * sizeof(v), (void*)&m_indices2[0], m_indices2.size() * sizeof(unsigned int));
            m_renderer2->draw();
        }

        void onEvent(Event& e) override
        {
            EventDispatcher dispatcher(e);
        }

        void onAttach() override
        {
            MGL_INFO("attached to layer stack");

            rendererProps renderer2Props("shaders/dev/base.vert", "shaders/dev/base.frag", MGL_TRIANGLES);
            renderer2Props.m_layout.push<3, MGL_FLOAT>();
            renderer2Props.m_layout.push<4, MGL_FLOAT>();

            m_triangle2 = {
                { {-0.5f-0.5f, 0.5f-0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
                { {-0.5f-0.5f,-0.5f-0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
                { { 0.5f-0.5f, 0.5f-0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
                { { 0.5f-0.5f,-0.5f-0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
            };

            m_indices2 = {
                0,1,2,
                1,2,3
            };

            m_renderer2 = Renderer::create(renderer2Props);
        }

        void onDetach() override
        {
            MGL_INFO("Detached from layer stack");

            delete m_renderer2;
        }

    private:

        Renderer* m_renderer2;
        std::vector<v> m_triangle2;
        std::vector<unsigned int> m_indices2;
    };

    class Sandbox : public Application
    {
    public:

        Sandbox()
        {
            pushLayer(new ExLayer());
            pushLayer(new ExLayer2());
            pushOverlay(new DebugLayer());
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