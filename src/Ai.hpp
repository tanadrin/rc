class AI 
{
public:
    virtual void update(GameObject *owner)=0;
};

//Handles input for the player character only (GUI input handled seperately)
class PlayerAI: public AI
{
public:
    void update(GameObject *owner);
};
