#include <iostream>
#include <string>

#include "3.3 directxrenderer.h"
#include "3.3 openglrenderer.h"
#include "3.3 mesarenderer.h"
#include "3.3 rendererfactory.h"

RenderFactory::CallbackMap RenderFactory::mRenderers;

void RenderFactory::RegisterRenderer(const std::string& type, CreateCallback cb)
{
	mRenderers[type] = cb;
}

void RenderFactory::UnregisterRenderer(const std::string& type, CreateCallback cb)
{
	mRenderers.erase(type);
}

IRender* RenderFactory::CreateRenderer(const std::string& type)
{
	/*
    if (type == "opengl")
        return new OpenGlRenderer();
    if (type == "directx")
        return new DirectXRenderer();
    if (type == "mesa")
        return new MesaRenderer();
	*/

	CallbackMap::iterator it = mRenderers.find(type);
	if (mRenderers.end() != it)
	{
		return (it->second)();
	}
    return nullptr;
}

class UserRenderer : public IRender
{
public:
	UserRenderer() { std::cout << "UserRenderer()" << std::endl; }
	~UserRenderer() {}
	virtual bool LoadScene(const std::string& filename) { return true; }
	virtual void SetViewportSize(int w, int h) {}
	virtual void setCameraPosition(double x, double y, double z) {}
	virtual void setLookAt(double x, double y, double z) {}
	virtual void Render() { std::cout << "User Render" << std::endl; }
	static IRender* Create() { return new UserRenderer(); }
};

int main(int argc, char* argv[])
{
	/*
    IRender* p_opengl = RenderFactory::CreateRenderer("opengl");
    IRender* p_directx = RenderFactory::CreateRenderer("directx");
    IRender* p_mesa = RenderFactory::CreateRenderer("mesa");
	*/

	//注册一个新的渲染器
	RenderFactory::RegisterRenderer("user", UserRenderer::Create);

	//为新渲染器创建一个实例
	IRender* r = RenderFactory::CreateRenderer("user");
	r->Render();
	delete r;

    return 0;
}