
namespace Vulture2D {
    class Event {
    public:
        enum EventType {
            INT,
            FLOAT,
            STRING
        };
        
        Event(std:string name, EventType type, bool propogateUp = false) : event_name(name), 
                                                                           type(type),
                                                                           propagateUp(propagateUp) {};
        ~Event();
        std::string getStringData();
        int getIntData();
        float getFloatData();
        std::string getName();
        EnumType getDataType();

        void setData(std::string);
        void setData(int);
        void setData(float);
        void setName(std::string);
        
    private:
        int intData;
        float floatData;
        std::string stringData;

        EventType type;
        std::string event_name;
        bool propagateUp;
}   
