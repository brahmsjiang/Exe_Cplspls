#include <string>
#include <map>
#include "3.3 renderer.h"

class RenderFactory
{
public:
    static IRender* CreateRenderer(const std::string& type);
};
