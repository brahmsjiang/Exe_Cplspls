#include <string>

using namespace std;

class IRender
{
public:
    virtual ~IRender() {}
    virtual bool LoadScene(const std::string& filename) = 0;
    virtual void SetViewportSize(int w, int h) = 0;
    virtual void setCameraPosition(double x, double y, double z) = 0;
    virtual void setLookAt(double x, double y, double z) = 0;
    virtual void Render() = 0;
};
