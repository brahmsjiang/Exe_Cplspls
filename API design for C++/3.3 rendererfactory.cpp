#include <iostream>
#include <string>

#include "3.3 directxrenderer.h"
#include "3.3 openglrenderer.h"
#include "3.3 mesarenderer.h"

#include "3.3 rendererfactory.h"

IRender* RenderFactory::CreateRenderer(const std::string& type)
{
    if (type == "opengl")
        return new OpenGlRenderer();
    if (type == "directx")
        return new DirectXRenderer();
    if (type == "mesa")
        return new MesaRenderer();

    return nullptr;
}

int main(int argc, char* argv[])
{
    IRender* p_opengl = RenderFactory::CreateRenderer("opengl");
    IRender* p_directx = RenderFactory::CreateRenderer("directx");
    IRender* p_mesa = RenderFactory::CreateRenderer("mesa");

    return 0;
}