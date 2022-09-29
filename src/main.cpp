#include <mgl/mglpch.hpp>
#include <mgl/mgl.hpp>
#include <imgui/imgui.h>

namespace mgl
{
    class ExLayer : public Layer
    {
    public:

        ExLayer() : Layer("test layer") {}

        void onImGuiRender() override
        {
            ImGui::ShowMetricsWindow();

            ImGui::Begin("Triangle Controller");

            ImGui::ColorPicker4("Triangle Color:", &m_color[0]);

            ImGui::Separator();

            ImGui::LabelText("Squere Tag", "%s", m_triangle.getComponent<Tag>().m_tag.c_str());
            ImGui::LabelText("Squere UUID", "%s", m_triangle.getComponent<UUID>().getUUID().c_str());
            if (ImGui::Button("Regen Squere UUID"))
            {
                m_triangle.getComponent<UUID>().regenerate();
            }

            ImGui::Separator();

            ImGui::DragFloat3("Squere Position", &pos[0], 0.1f);
            ImGui::DragFloat3("Squere Rotation", &rot[0], 0.01);
            ImGui::DragFloat3("Squere Scale", &scale[0], 0.01);

            ImGui::End();

            ImGui::Begin("Camera Controller");

            ImGui::LabelText("Camera Tag", "%s", m_camera.getComponent<Tag>().m_tag.c_str());
            ImGui::LabelText("Camera UUID", "%s", m_camera.getComponent<UUID>().getUUID().c_str());

            ImGui::Separator();

            ImGui::DragFloat3("Camera Pos", &m_camera.getComponent<Camera3D>().m_camPos[0], 1.0f);

            ImGui::Separator();

            ImGui::DragFloat3("Camera Front", &m_camera.getComponent<Camera3D>().m_front[0], 1.0f);
            ImGui::DragFloat3("Camera Up", &m_camera.getComponent<Camera3D>().m_up[0], 1.0f);
            ImGui::DragFloat3("Camera Right", &m_camera.getComponent<Camera3D>().m_right[0], 1.0f);
            ImGui::DragFloat3("Camera World Up", &m_camera.getComponent<Camera3D>().m_wordUp[0], 1.0f);

            ImGui::Separator();

            ImGui::DragFloat("Camera Pitch", &m_camera.getComponent<Camera3D>().m_pitch, 0.1f);
            ImGui::DragFloat("Camera Yaw", &m_camera.getComponent<Camera3D>().m_yaw, 0.1f);
            ImGui::DragFloat("Camera Move Speed", &m_camera.getComponent<Camera3D>().m_moveSpeed, 0.1f);
            ImGui::DragFloat("Camera Turn Speed", &m_camera.getComponent<Camera3D>().m_turnSpeed, 0.1f);

            ImGui::End();
        }

        void onUpdate() override
        {
            m_scene->onUpdate();

            m_triangle.getComponent<Color>().m_colors = {
                m_color,
                m_color,
                m_color,
                m_color,
            };

            m_triangle.getComponent<Transform>().setPosition(pos);
            m_triangle.getComponent<Transform>().setRotation(rot);
            m_triangle.getComponent<Transform>().setScale(scale);
            
            m_renderer1->pushEntity(m_triangle);
            m_renderer1->pushCamera(m_camera);

            m_renderer1->draw();
        }

        void onEvent(Event& e) override
        {
            EventDispatcher dispatcher(e);

            dispatcher.dispatch<KeyPressedEvent>(MGL_BIND_FN(ExLayer::onKeyPress));

            m_scene->onEvent(e);
        }

        bool onKeyPress(KeyPressedEvent &e)
        {
            if (e.getKeyCode() == MGL_KEY_X)
            {
                m_renderer1->setWireframe(!m_renderer1->isWireframe());
            }

            return false;
        }

        void onAttach() override
        {
            MGL_INFO("attached to layer stack");

            rendererProps renderer1Props("shaders/dev/base.vert", "shaders/dev/base.frag", MGL_TRIANGLES);
            renderer1Props.m_layout.push<3, MGL_FLOAT>();
            renderer1Props.m_layout.push<4, MGL_FLOAT>();

            m_renderer1 = Renderer::create(renderer1Props);

            m_scene = new Scene();

            m_camera = m_scene->createEntity();
            m_camera.addComponent<Camera3D>();
            m_camera.addComponent<Tag>("m_camera");

            m_triangle = m_scene->createEntity();

            std::vector<glm::vec3> triangleVertices = {
                {-1.0f, 1.0f, 0.0f},
                {-1.0f,-1.0f, 0.0f},
                { 1.0f, 1.0f, 0.0f},
                { 1.0f,-1.0f, 0.0f},
            };

            std::vector<glm::vec4> triangleColors = {
                m_color,
                m_color,
                m_color,
                m_color,
            };

            std::vector<unsigned int> triangleIndices = {
                0,1,2,
                1,2,3
            };

            m_triangle.addComponent<Transform>();
            m_triangle.addComponent<Tag>("m_triangle");
            m_triangle.addComponent<ModelIndices>(triangleIndices);
            m_triangle.addDrawableComponent<ModelPoints>(&ModelPoints::getData, &ModelPoints::getSize, &ModelPoints::getStep, triangleVertices);
            m_triangle.addDrawableComponent<Color>(&Color::getData, &Color::getSize, &Color::getStep, triangleColors);
        }

        void onDetach() override
        {
            MGL_INFO("Detached from layer stack");

            delete m_renderer1;
        }

    private:

        Renderer* m_renderer1;
        glm::vec4 m_color = {1,1,1,1};
        glm::vec3 pos = {0,0,5};
        glm::vec3 scale = {1,1,1};
        glm::vec3 rot = {0,0,0};

        Scene *m_scene;
        Entity m_triangle;
        Entity m_camera;
    };

    class XWingLayer : public Layer
    {
    public:

        XWingLayer() : Layer("xwing layer") {}

        void onImGuiRender()
        {
            ImGui::ShowMetricsWindow();

            ImGui::Begin("XWing 1 Controller");

            ImGui::LabelText("Tag", "%s", m_xwing.getComponent<Tag>().m_tag.c_str());
            ImGui::LabelText("UUID", "%s", m_xwing.getComponent<UUID>().getUUID().c_str());
            if (ImGui::Button("Regen UUID"))
            {
                m_xwing.getComponent<UUID>().regenerate();
            }

            ImGui::Separator();

            ImGui::DragFloat3("Position", &m_xwing1_pos[0], 0.1f);
            ImGui::DragFloat3("Rotation", &m_xwing1_rot[0], 0.01);
            ImGui::DragFloat3("Scale", &m_xwing1_scale[0], 0.01);

            ImGui::End();

            ImGui::Begin("XWing 2 Controller");

            ImGui::LabelText("Tag", "%s", m_xwing2.getComponent<Tag>().m_tag.c_str());
            ImGui::LabelText("UUID", "%s", m_xwing2.getComponent<UUID>().getUUID().c_str());
            if (ImGui::Button("Regen UUID"))
            {
                m_xwing.getComponent<UUID>().regenerate();
            }

            ImGui::Separator();

            ImGui::DragFloat3("Position", &m_xwing2_pos[0], 0.1f);
            ImGui::DragFloat3("Rotation", &m_xwing2_rot[0], 0.01);
            ImGui::DragFloat3("Scale", &m_xwing2_scale[0], 0.01);

            ImGui::End();

            ImGui::Begin("Camera Controller");

            ImGui::LabelText("Camera Tag", "%s", m_camera.getComponent<Tag>().m_tag.c_str());
            ImGui::LabelText("Camera UUID", "%s", m_camera.getComponent<UUID>().getUUID().c_str());

            ImGui::Separator();

            ImGui::DragFloat3("Camera Pos", &m_camera.getComponent<Camera3D>().m_camPos[0], 1.0f);

            ImGui::Separator();

            ImGui::DragFloat3("Camera Front", &m_camera.getComponent<Camera3D>().m_front[0], 1.0f);
            ImGui::DragFloat3("Camera Up", &m_camera.getComponent<Camera3D>().m_up[0], 1.0f);
            ImGui::DragFloat3("Camera Right", &m_camera.getComponent<Camera3D>().m_right[0], 1.0f);
            ImGui::DragFloat3("Camera World Up", &m_camera.getComponent<Camera3D>().m_wordUp[0], 1.0f);

            ImGui::Separator();

            ImGui::DragFloat("Camera Pitch", &m_camera.getComponent<Camera3D>().m_pitch, 0.1f);
            ImGui::DragFloat("Camera Yaw", &m_camera.getComponent<Camera3D>().m_yaw, 0.1f);
            ImGui::DragFloat("Camera Move Speed", &m_camera.getComponent<Camera3D>().m_moveSpeed, 0.1f);
            ImGui::DragFloat("Camera Turn Speed", &m_camera.getComponent<Camera3D>().m_turnSpeed, 0.1f);

            ImGui::End();

            ImGui::Begin("Renderer");

            static bool faceCulling = m_renderer->isFaceCulling();
            if (ImGui::Checkbox("Face Culling", &faceCulling))
            {
                m_renderer->setFaceCulling(faceCulling);
            }

            static bool wireframe = m_renderer->isWireframe();
            if (ImGui::Checkbox("Wireframe", &wireframe))
            {
                m_renderer->setWireframe(wireframe);
            }

            ImGui::End();
        }

        void onUpdate()
        {
            m_scene->onUpdate();

            m_xwing.getComponent<Transform>().setPosition(m_xwing1_pos);
            m_xwing.getComponent<Transform>().setRotation(m_xwing1_rot);
            m_xwing.getComponent<Transform>().setScale(m_xwing1_scale);

            m_xwing2.getComponent<Transform>().setPosition(m_xwing2_pos);
            m_xwing2.getComponent<Transform>().setRotation(m_xwing2_rot);
            m_xwing2.getComponent<Transform>().setScale(m_xwing2_scale);

            m_renderer->pushEntity(m_xwing);
            m_renderer->pushEntity(m_xwing2);
            m_renderer->pushCamera(m_camera);
            m_renderer->draw();
        }

        void onEvent(Event& e)
        {
            EventDispatcher dispatcher(e);
            dispatcher.dispatch<KeyPressedEvent>(MGL_BIND_FN(XWingLayer::onKeyPress));

            m_scene->onEvent(e);
        }

        bool onKeyPress(KeyPressedEvent &e)
        {
            if (e.getKeyCode() == MGL_KEY_X)
            {
                m_renderer->setWireframe(!m_renderer->isWireframe());
            }

            return false;
        }

        void onAttach()
        {
            rendererProps rendererProps("shaders/dev/base2.vert", "shaders/dev/base2.frag", MGL_TRIANGLES);
            rendererProps.m_layout.push<3, MGL_FLOAT>();

            m_renderer = Renderer::create(rendererProps);
            m_renderer->setFaceCulling(true);
            m_renderer->addUniform("u_color");
            m_renderer->setUniform4f("u_color", {1,1,1,1});

            m_scene = new Scene();

            m_camera = m_scene->createEntity();
            m_camera.addComponent<Tag>("Camera");
            m_camera.addComponent<Camera3D>();

            m_xwing = loadObjAsync(m_scene, "models/xwing.obj");
            m_xwing.addComponent<Tag>("XWing");
            m_xwing.addComponent<Transform>();

            m_xwing2 = loadObjAsync(m_scene, "models/xwing.obj");
            m_xwing2.addComponent<Tag>("XWing2");
            m_xwing2.addComponent<Transform>();
            m_xwing2.getComponent<Transform>().setTransformParent(m_xwing);
        }

        void onDetach()
        {
            delete m_scene;
            delete m_renderer;
        }


    private:

        Renderer* m_renderer;
        Scene *m_scene;
        Entity m_camera;
        Entity m_xwing;
        Entity m_xwing2;

        glm::vec3 m_xwing1_pos = {0,0,5};
        glm::vec3 m_xwing1_scale = {1,1,1};
        glm::vec3 m_xwing1_rot = {0,0,0};

        glm::vec3 m_xwing2_pos = {0,0,5};
        glm::vec3 m_xwing2_scale = {1,1,1};
        glm::vec3 m_xwing2_rot = {0,0,0};

    };

    class Sandbox : public Application
    {
    public:

        Sandbox() : Application(ProjectionType::PERSPECTIVE)
        {
            // pushLayer(new ExLayer());
            pushLayer(new XWingLayer());
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