
namespace Vulture2D {
    class Event {
    public:
        Event(std:string name, EventType type, bool propogateUp = false) : event_name(name), type(type), propagateUp(propagateUp) {};
        ~Event();
        std::string getStringData();
        int getIntData();
        float getFloatData();
        std::string getName();
        
        void setData(std::string);
        void setData(int);
        void setData(float);
        void setName(std::string);

    private:
        void* payload;
        EventType type;
        std::string event_name;
        bool propagateUp;
        enum EventType {
            INT,
            FLOAT,
            STRING
        };
}   
