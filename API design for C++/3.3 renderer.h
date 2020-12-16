#ifndef  __IRenderer__
#define __IRenderer__

#include <string>

using namespace std;

class IRenderer
{
public:
    virtual ~IRenderer() {}
    virtual bool LoadScene(const std::string& filename) = 0;
    virtual void SetViewportSize(int w, int h) = 0;
    virtual void setCameraPosition(double x, double y, double z) = 0;
    virtual void setLookAt(double x, double y, double z) = 0;
    virtual void Render() = 0;
};

#endif // ! __IRenderer__
