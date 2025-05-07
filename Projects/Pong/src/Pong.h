#include <Cents/Application.h>
#include <Cents/Shader.h>
#include <Cents/Model.h>

class Pong : public Application
{
protected:
    void Init() override;
    void Load() override;
    void UnLoad() override;

    void UpdateFrame() override;
    void RenderFrame() override;

private:
    Shader* m_shader;
    Model* m_model;
};

CREATE_APPLICATION(Pong);