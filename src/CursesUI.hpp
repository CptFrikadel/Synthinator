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

private:

    unsigned mMode = 0;
    // Some reference to the NoteBuilder
    // Some reference to the AudioThread

};
