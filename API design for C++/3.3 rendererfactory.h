#include <string>
#include <map>
#include "3.3 renderer.h"

class RenderFactory
{
public:
	typedef IRender* (*CreateCallback)();
	static void RegisterRenderer(const std::string& type, CreateCallback cb);
	static void UnregisterRenderer(const std::string& type, CreateCallback cb);
    static IRender* CreateRenderer(const std::string& type);

private:
	typedef std::map<std::string, CreateCallback> CallbackMap;
	static CallbackMap mRenderers;
};
