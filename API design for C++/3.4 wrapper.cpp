#include <iostream>
#include <time.h>

class IOriginal
{
public:
    virtual bool DoSomething(int value) = 0;
};

class Original : public IOriginal
{
public:
    bool DoSomething(int value) 
    {
        std::cout << "Original::DoSomething" << value << std::endl;
        return true;
    }
private:

};

class Proxy : public IOriginal
{
public:
    Proxy() : mOrig(new Original()) {}
    ~Proxy()
    {
        delete mOrig;
    }
    bool DoSomething(int value)
    {
        return mOrig->DoSomething(value);
    }
private:
    Proxy(const Proxy&);
    const Proxy& operator=(const Proxy&);

    Original* mOrig;
};

class Rectangle
{
public:
    void setDimensions(float cx, float cy, float w, float h)
    {
        std::cout << "Rectangle::setDimensions" << std::endl;
    }
};

class RectangleAdapter
{
public:
    RectangleAdapter()
    : mRect(new Rectangle()) {}

    ~RectangleAdapter()
    {
        delete mRect;
    }

    void Set(float x1, float y1, float x2, float y2)
    {
        float w = x2 - x1;
        float h = y2 - y1;
        float cx = w / 2.0f + x1;
        float cy = h / 2.0f + y1;
        mRect->setDimensions(cx, cy, w, h);
    }
private:
    RectangleAdapter(const RectangleAdapter&);
    const RectangleAdapter& operator=(const RectangleAdapter&);

    Rectangle* mRect;
};

class Taxi
{
public:
    static bool BookTaxi(int npeople, time_t pickup_time)
    {
        std::cout << "Taxi::BookTaxi" << std::endl;
        return true;
    }
};

class Restaurant
{
public:
    static bool ReserveTable(int npeople, time_t arrival_time)
    {
        std::cout << "Restaurant::ReserveTable" << std::endl;
        return true;
    }
};

class Theater
{
public:
    time_t GetShowTime() {} //time_t: seconds from 1970
    static bool Reserve(int npeople, int tier)
    {
        std::cout << "Theater::Reserve" << std::endl;
        return true;
    }
};

class ConciergeFacade
{
public:
    enum ERestaurant {
        RESTAURANT_YES,
        RESTAURANT_NO,
    };
    enum ETaxi {
        TAXI_YES,
        TAXI_NO,
    };

    static time_t BookShow(int npeople, ERestaurant addRestaurant, ETaxi addTaxi)
    {
        time_t timep;
        time(&timep);

        Taxi::BookTaxi(npeople, timep);
        Restaurant::ReserveTable(npeople, timep);
        Theater::Reserve(npeople, 2);

        return timep;
    }
};


int main(int argc, char* argv[])
{
    Proxy proxy;
    proxy.DoSomething(4);

    RectangleAdapter rectangleAdapter;
    rectangleAdapter.Set(1.0, 1.0, 2.0, 2.0);

    ConciergeFacade::BookShow(2, ConciergeFacade::RESTAURANT_YES, ConciergeFacade::TAXI_YES);

    return 0;
}