#include <Cents/Application.h>

class Pong : public Application
{
protected:
    void Init() override;
    void Load() override;
    void UnLoad() override;

    void UpdateFrame() override;
    void RenderFrame() override;
};

CREATE_APPLICATION(Pong);