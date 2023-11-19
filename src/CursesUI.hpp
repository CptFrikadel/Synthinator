/*
 * Curses based UI
 */



class CursesUI {

public:

    CursesUI() = default;

    /*
     * Initialize the curese ui. Calls initscr()
     */
    void Init();

    void Update();
    
    /*
     * End curses mode
     */
    void Exit();

    void NotifyMode(unsigned mode_number){ mMode = mode_number; }
    
    void NotifyLoad(float load){ mSynthLoad = load; }

private:

    unsigned mMode = 0;
    float mSynthLoad = 0;

};
