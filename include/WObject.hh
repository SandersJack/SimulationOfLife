#ifndef WObject_H
#define WObject_H

class WObject {

    public:
        WObject();
        ~WObject();

        virtual const char* className() const {return "WObject";}

    private:
    
};

#endif