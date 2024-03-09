#ifndef WObject_H
#define WObject_H

class WObject {

    public:
        WObject();
        virtual ~WObject() {}

        virtual const char* className() const {return "WObject";}

        int GetX(){return x;}
        int GetY(){return y;}

        void SetPosition(int val_x, int val_y){x = val_x; y=val_y;}
        
        bool operator==(const WObject& other) const {return this == &other;}

        virtual int step() = 0;

    protected:

        int x, y;
    
};

#endif