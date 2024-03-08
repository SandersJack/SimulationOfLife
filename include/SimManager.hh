#ifndef SimManager_H
#define SimManager_H 

class SimManager {
    public:
        SimManager();
        ~SimManager();

        static SimManager *GetInstance();

    private:
        static SimManager *fInstance;
};

#endif