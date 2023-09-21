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


private:

    // Some reference to the NoteBuilder
    // Some reference to the AudioThread

};
