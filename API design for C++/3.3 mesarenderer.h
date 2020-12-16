#include <iostream>
#include <string>

#include "3.3 renderer.h"

class MesaRenderer : public IRenderer
{
public:
    MesaRenderer() { std::cout << "MesaRenderer()" << std::endl; }
    ~MesaRenderer() {}
    virtual bool LoadScene(const std::string& filename) { return true; }
    virtual void SetViewportSize(int w, int h) {}
    virtual void setCameraPosition(double x, double y, double z) {}
    virtual void setLookAt(double x, double y, double z) {}
    virtual void Render() {}
};
