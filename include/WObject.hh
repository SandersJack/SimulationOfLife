#ifndef WObject_H
#define WObject_H

class WObject {

    public:
        WObject();
        virtual ~WObject() {}

        virtual const char* className() const {return "WObject";}

        
        
        bool operator==(const WObject& other) const {return this == &other;}

    private:
    
};

#endif