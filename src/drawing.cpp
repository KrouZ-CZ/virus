#include "drawing.hpp"

Virus::Virus(RenderWindow &window) : window(window) {
    std::string text = "A problem has been detected and Windows has been shut down to prevent damage to your computer. \n\nThe problem seems to be caused by the following file: NotAVirus.exe \n\nSYSTEM_THREAD_EXCEPTION_NOT_HANDLED If this is the first time you've seen this stop error screen, restart your computer. If \nthis screen appears again, follow these steps: \n\nCheck to make sure any new hardware or software is properly installed. If this is a new installation, ask your hardware \nor software manufacturer for any Windows updates you might need. \n\nIf problems continue, disable or remove any newly installed hardware or software. Disable BIOS memory options such as caching or \nshadowing. If you need to use safe mode to remove or disable components, restart your computer, press F8 to select Advanced \nStartup Options, and then select Safe Mode. \n\nTechnical Information: \n\n*** STOP: 0x1000007e (0xffffffffc0000005, 0xfffff80002e55151, 0xfffff880009a99d8, 0xfffff880009a9230) \n\n*** NotAVirus.exe - Address 0xfffff80002e55151 base at 0xfffff80002e0d000 DateStamp 0x4ce7951a";

    ft.loadFromFile("D:\\c++\\virus\\build\\arial.ttf");

    tx.setFont(ft);
    tx.setString(text);
    tx.setFillColor(Color::White);
    tx.setPosition(Vector2(88.f, 64.f));

    bar.setPosition(Vector2(250.f, 900.f));
    bar.setSize(Vector2(0.f, 30.f));
    bar.setFillColor(Color::White);

    proc.setFont(ft);
    proc.setString("0%");
    proc.setPosition(Vector2(185.f, 896.f));

    rest.setFont(ft);
    rest.setString("Restoring computer");
    rest.setPosition(Vector2(802.f, 849.f));

    prep.setFont(ft);
    prep.setString("Preparing to restore");
    prep.setPosition(Vector2(802.f, 864.f));

    disp_count.setFont(ft);
    disp_count.setString("0");
    disp_count.setPosition(Vector2(898.f, 896.f));

    ybh.setFont(ft);
    ybh.setCharacterSize(128);
    ybh.setString("You been Hacked!!!");
    ybh.setPosition(Vector2(364.f, 465.f));
    ybh.setFillColor(Color::Black);
}

void Virus::loop() {
    if (state == 0) {
        this->preparing();
    } else if (state == 1) {
        this->encrypting();
    } else if (state == 2) {
        this->end_screen();
    }
}

void Virus::preparing() {
    for( char drive = 'A'; drive <= 'Z'; ++drive ) {
        fs::path p = std::string(1, drive) + ":\\";
        if (fs::exists(p)) {
            for (auto it : fs::directory_iterator(p.string())) {
                this->start_rec(it);
            }
        }
    }
    state = 1;
}

void Virus::start_rec(fs::directory_entry it) {
    if (!checking(it)) {
        try
        {
            for (auto it : fs::directory_iterator(it)) {
                this->start_rec(it);
            }
        }
        catch(const fs::filesystem_error& e)
        {
            // Some error
        }
    }
}

bool Virus::checking(fs::directory_entry entry) {
    if (!entry.is_directory()) {        
        files.push_back(entry.path().string());
        this->event();
        disp_count.setString(std::to_string(count));

        window.clear(Color(0, 0, 128));
        window.draw(tx);
        window.draw(prep);
        window.draw(disp_count);
        window.display();

        count++;
        // std::cout << entry.path().string() << "\n";
        return true;
    } 

    return false;
}

void Virus::encrypting() {
    for (int i = 0; i < files.size(); i++) { 
        /* 
            Encryption here
        */

        tick = i/float(files.size());
        float x_pos = 1420*tick;

        bar.setSize(Vector2(x_pos, 30.f));
        proc.setString(std::to_string(int(tick*100))+"%");

        this->event();

        window.clear(Color(0, 0, 128));
        window.draw(tx);
        window.draw(bar);
        window.draw(proc);
        window.draw(rest);
        window.display();
    }
    state = 2;
}

void Virus::end_screen() {
    if (is_red) {
        window.clear(Color::Red);
    } else {
        window.clear(Color::White);
    }
    is_red = !is_red;

    window.draw(ybh);
    window.display();
}

void Virus::event() {
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
    }
    if (!window.isOpen())
        exit(0);
}
