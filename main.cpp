#include <bits/stdc++.h>
#include <windows.h> //for the sleep function and the music
#include <mmsystem.h> // for the music
#include <fstream>      //for the music
#include <conio.h>      //for the music
#include <time.h>	//to keep track of time since start
#include <math.h>	//to keep track of choices
/*
play mp3: https://stackoverflow.com/questions/22253074/how-to-play-or-open-mp3-or-wav-sound-file-in-c-program
*/
// ADD LINKER LIBRARY http://forums.codeblocks.org/index.php?topic=15998.0 for exe to run on other computers

//a lifeless chatbot thinking about time
using namespace std;

//credits of sound portion: http://www.cplusplus.com/forum/beginner/88542/
class Sound {

public:
    Sound(char * filename);
    ~Sound();
    void play(bool async=true);
    bool isok();

private:
    char * buffer;
    bool ok;
    HINSTANCE HInstance;
};
Sound::Sound(char * filename){
    ok = false;
    buffer = 0;
    HInstance = GetModuleHandle(0);

    ifstream infile(filename, ios::binary);

    if (!infile)
    {
         cout << "Sound file error: "<< filename << " is not in the same directory" << endl;
        return;
    }

    infile.seekg (0, ios::end);   // get length of file
    int length = infile.tellg();
    buffer = new char[length];    // allocate memory
    infile.seekg (0, ios::beg);   // position to start of file
    infile.read (buffer,length);  // read entire file

    infile.close();
    ok = true;
}
Sound::~Sound(){
    PlaySound(NULL, 0, 0); // STOP ANY PLAYING SOUND
    delete [] buffer;      // before deleting buffer.
}
void Sound::play(bool async){
    if (!ok)
        return;

    if (async)
        PlaySound(buffer, HInstance, SND_MEMORY | SND_ASYNC | SND_LOOP);
    else
        PlaySound(buffer, HInstance, SND_MEMORY);
}
bool Sound::isok(){
    return ok;
}

//ALL VARIABLES
string name;
int uresp;		//universal response
char placeholder;
string placeholderS;
int gs = 1000; //gs stands for global speed or global delay
//unsigned long long chosto = 0; //for storing choices (choice store)
int qnNum = 0;					//to help store choices
int choice = 0;					//choice selection response
string comName,comNameLong;
int comGender; //1 is male 2 is female
vector<int> chosto; //for storing choices (choice store)
set<int> complete;
int creditStatus = 0;

//action functions
void choiceStore(int cho){
	chosto.push_back(cho);
}
int choiceRet(int location){
    if(location == 99)
        return chosto[chosto.size()-1];
	else
        return chosto[location-1];
}
void validSound(){
	//Note G6, C7
	Beep(1568,gs/13);
	Beep(2093,gs/5);
}
void invalidSound(){
	//Note C4
	Beep(261,gs/13);
	Beep(261,gs/5);
}
void checktime(double timestart){
	double timespent;
	timespent = difftime(time(0),timestart);
	int theSeconds = (int)timespent%60;
	int theMinutes = (int)timespent/60;
	cout << "Time passed in real life: " << theMinutes << " minute(s) and " <<theSeconds << " second(s)" << endl;
}
void setgs(int val){
	gs=val;
	if(gs<200)
		gs = 200;
	else if (gs > 10000)
		gs = 10000;
}
void flushScreen(){
	cout << string(100,'\n');
}
void checkinput(){
	while (!cin ){
    	cin.clear ();    // Restore input stream to working state
    	cin.ignore ( 100 , '\n' );    // Get rid of any garbage that user might have entered
   		Sleep(gs);
   		cout << endl;
   		cout << ">.<" << endl;
		cout << "Please do not enter other characters when not supposed to.";
    	cout << endl;
    	cout << endl;
		}
}
void invalid(){
	invalidSound();
	cout << "Invalid Response" << endl;
	cout << "Please Select Again" << endl;
}

//most common sounds
Sound silent("silent.wav");         //silent wav file
Sound transition("transition.wav"); //credits maplestory portal In sound effect
Sound timeTravel("timeTravel.wav"); //credits https://www.youtube.com/watch?v=8mLCaXvVPas&list=RD8mLCaXvVPas&t=110 interstellar no time for caution

//story functions
void preintro(){
	Sound preintroSound("start.wav");
	preintroSound.play(1);
	start:
	cout << "Proceed with tutorial?    Type \'y\' for YES, \'n\' for NO" << endl;
	cin >> placeholder;
	if (placeholder == 'y' || placeholder == 'Y');
	else if(placeholder == 'n' || placeholder == 'N')
		goto endtut;
	else{
		invalid();
		checkinput();
		cout << "..." << endl;
		goto start;
	}

	cout << "Welcome to the tutorial!" << endl;
	Sleep(gs);
	tut1:
	cout << "Whenever you see an \" --- OPTION --- \" line," << endl;
	Sleep(gs);
	cout << "Type 1 or 2 into the prompt to state your response" << endl;
	Sleep(gs);
	cout << endl;
	cout << "Tutorial question 1:" << endl;
	cout << "What school are you in?" << endl;
	Sleep(gs);
	cout << "--- OPTION ---" << endl;
	cout << "1. NUS" << endl;
	cout << "2. NTU" << endl;
	cout << "Enter your option:";
	cin >> uresp;
	if(uresp == 1){
        Sleep(gs);
		cout << "YAY! This is a valid response" << endl;
		validSound();
	}
	else if (uresp == 2){
	    Sleep(gs);
		cout << "YAY! This is a valid response" << endl;
		validSound();
	}
	else{
	    Sleep(gs);
		invalid();
		checkinput();
		cout << "..." << endl;
		goto tut1;
	}
	endtut:
	cout << endl;
	cout << "Let's move on!" << endl;
	cout << endl;
	Sleep(gs*3);
	flushScreen();

	gender:
	//enter your name
	cout << "Are you a boy or are you a girl?" << endl;
	Sleep(gs/2);
	cout << "--- OPTION ---" << endl;
	cout << "1. Boy" << endl;
	cout << "2. Girl" << endl;
	cout << "3. Other" << endl;
	cout << "Enter your option:";
	cin >> uresp;
	if(uresp == 1 || uresp == 3){
		comNameLong = "Nicole Tyler";
		comName = "Nicole";
		comGender = 2;
		validSound();
	}
	else if (uresp == 2){
		comNameLong = "Mark Blythe";
		comName = "Mark";
		comGender = 1;
		validSound();
	}
	else{
		invalid();
		checkinput();
		cout << "..." << endl;
		goto gender;
	}
	getchar();
	cout << endl;
	cout << "Enter your name:" << endl;
	getline(cin,name);
	if(name[0]>= 'a' && name[0] <= 'z'){
        name[0]-=32;
	}
	sec0:
    cout << endl;
    cout << "So, your name is " << name << "?" << endl;
	cout << "Press 1 to Confirm, 2 to type again" << endl;
	cout << "--- OPTION ---" << endl;
	cout << "1. Confirm and continue" << endl;
	cout << "2. Type again" << endl;
	cout << "Enter your option:";
	cin >> uresp;
	getchar();
	if(uresp == 1)
		cout << endl;
	else if(uresp == 2){
		validSound();
		getchar();
		cout << endl;
		goto gender;
	}
	else{
		invalid();
		checkinput();
		cout << endl;
		goto sec0;
	}
	validSound();
	cout << "Please note that this program will not store any of your responses to the questions" << endl;
	Sleep(gs*4);
	transition.play(0);
	flushScreen();
}
void intromsg(){
    //start welcome: https://www.youtube.com/watch?v=Q5RwmrKRm2Y (Pokemon sun and moon welcome)
    Sound welcome("welcome.wav");
    welcome.play(1);
	introMsg:
	Sleep(gs);
	cout << "Welcome to the world of Time and Life" << endl;
	Sleep(gs*3);
	cout << "..." << endl;
	Sleep(gs);
	cout << "In this parallel universe, a robot from the future decides to visit our current reality" << endl;
	Sleep(gs*3);
	cout << "... " << endl;
	Sleep(gs);
	cout << "Will you like to continue?                                                                     ******" << endl;
	cout << "--- OPTION ---" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	cout << "99. Skip to main menu" << endl;
	cout << "Enter your option:";
	setgs(1000);
	cin >> uresp;
	if (uresp == 1){
		validSound();
		flushScreen();
	}
	else if (uresp == 99){
        cout << "Select storyline mode" << endl;
        return;
	}
	else{
        setgs(300);
		invalid();
		checkinput();
		cout << endl;
		goto introMsg;
	}

	Sleep(gs);
	transition.play(0);
}
void section1(){    //the present day
    //section 1 depicts the way time flows in present day
    //music credits: https://www.youtube.com/watch?v=7maJOI3QMu0 (Yiruma river flows in you)
    Sound section1("RFIY.wav");
    section1.play(1);

	cout << "Scenario 1: PRESENT DAY\n\n" << endl;
    Sleep(gs*2);

	sec1:
	getchar();
	//section 1, the introduction of the computer
	cout << "Hi " << name << endl;
	Sleep(gs/2);
	cout << "..." << endl;
	Sleep(gs);
	cout << "I'm " << comName << endl;
	Sleep(gs);
	cout << "..." << endl;
	cout << comNameLong << endl;
	Sleep(gs);
	cout << "..." << endl;
	Sleep(gs);
	cout << "How are you today? :)" << endl;
	Sleep(gs);
	sec11:
	cout << "..." << endl;
	Sleep(gs);

	cout << "--- OPTION ---" << endl;
	cout << "1. I'm doing great! How are you? :)" << endl;
	cout << "2. Not really, finals are coming and things are getting tough :( How about you?" << endl;
	cout << "3. Enter your personal response" << endl;
	cout << "Enter your option:";
	cin >> choice;
	choiceStore(choice);
	if(choice == 1){
		validSound();
		Sleep(gs);
		cout << "..." << endl;
		Sleep(gs);
	}
	else if (choice == 2){
		validSound();
		Sleep(gs);
		cout << "...";
		Sleep(gs*2);
		cout << "..." << endl;
		Sleep(gs*2);
		cout << "Well, as an immortal ";
		if (comGender == 1){
            cout << "man" << endl;
		}
		else cout << "woman" << endl;
		cout << " from the future who has lived through centuries, I had my share of tough times." << endl;
		Sleep(gs*2);
		cout << "I understand how you feel, but" << endl;
		Sleep(gs*2);
		cout << "it's already the last lap of the semester! so... Keep it up!" << endl;
		Sleep(gs);
		cout << "Tough times don't last, ";
		Sleep(gs);
		cout << "but tough people do!" << endl;
	}

	else if (choice == 3){
		validSound();
		cout << "Type here: ";
		getchar();
		getline(cin,placeholderS);
		Sleep(gs);
		cout << "..." << endl;
		Sleep(gs*2);
		cout << "I feel you." << endl;
		Sleep(gs*2);
		cout << "Well, as an immortal ";
		if (comGender == 1){
            cout << "man";
		}
		else cout << "woman";
		cout << " from the future who has lived through centuries, I had my share of tough times." << endl;
		Sleep(gs*3);
		cout << "Anyway..." << endl;
		Sleep(gs*2);
		cout << "It's the last lap of the semester! so... Keep it up!" << endl;
		Sleep(gs);
		cout << "Tough times don't last, ";
		Sleep(gs*2);
		cout << "but tough people do!" << endl;
	}
	else{
		cout << "..." << endl;
		Sleep (gs);
		cout << ":(" << endl;
		Sleep (gs/2);
		invalid();
		checkinput();
		cout << endl;
		goto sec11;
	}
	Sleep(gs*2);

    cout << endl;
    ///////////////////////////////////DELAY SET//////////////////////////////
    setgs(2000);
    ///////////////////////////////////DELAY SET//////////////////////////////
    int retrev = choiceRet(99);
    if (retrev == 1){
        cout << "I'm doing great too! I'm so happy to be here talking to Tembusians today :D" << endl;
        Sleep(gs*2);
        cout << "Anyway " << name << ", I haven't mentioned, but..."<< endl;
        Sleep(gs);
        cout << "I'm an immortal ";
        if (comGender == 1){
            cout << "man";
		}
		else cout << "woman";
		cout << " who has lived through centuries, and had my share of tough times throughout the years...";
		Sleep(gs/2);
		cout << "..." << endl;
		Sleep(gs*2);
		cout << "Being here today, talking to you, makes me feel "; Sleep(gs); cout << "honoured" << endl;
    }
    else if (retrev == 2){
        cout << "Oh yes, yes, I'm doing great! I'm so happy to be here talking to Tembusians today :D" << endl;
    }
    else if (retrev == 3){
        sec12:
        cout << "--- OPTION ---" << endl;
        cout << "1. How about you? How are you doing today?" << endl;
        cout << "Enter your option:";
        cin >> choice;
        getchar();
        if (choice == 1){
            cout << "..." << endl;
            Sleep(gs*2);
            cout << "I'm doing great! I'm so happy to be here talking to Tembusians today :D" << endl;
            goto sec120;
        }
        else{
            cout << "..." << endl;
            Sleep (gs);
            cout << ":(" << endl;
            Sleep (gs/2);
            invalid();
            checkinput();
            cout << endl;
            goto sec12;
        }
    }

	getchar();
	sec120:
    cout << "..." << endl;
    Sleep(gs*2);
    cout << "I'm here today to share my experience with you,";
    Sleep(gs*2);
    cout <<" about how people experience time in different time periods I've been to" << endl;
    Sleep(gs/2);
    cout << "..." << endl;
    Sleep(gs*2);
    cout << endl;
    sec13:
    cout <<"Speaking of which, when was the last time you had to google something?" << endl;
    cout << endl;
    cout << "--- OPTION ---" << endl;
	cout << "1. Just Now" << endl;
	cout << "2. Earlier Today" << endl;
	cout << "3. Yesterday" << endl;
	cout << "4. Before yesterday" << endl;
	cout << "5. I don't use Google" << endl;
	cout << "Enter your option:";
	cin >> choice;
	getchar();
	choiceStore(choice);
	if(choice == 1 || choice == 2 || choice == 3){
        cout << "..." << endl;
        Sleep(gs);
        cout << "cool :)" << endl;
        Sleep(gs*2);
	}
	else if (choice == 4){
        cout << "..." << endl;
        Sleep(gs*2);
        cout << "Hmm.. you don't really use it for your schoolwork huh..." << endl;
        Sleep(gs*2);

	}
	else if (choice == 5){
        cout << "..." << endl;
        Sleep(gs*2);
        cout << "Wow, that's a first. Haven't met someone like you in a long while." << endl;
        Sleep(gs*2);
        cout << "Based on your best guess if you've used it," << endl;
        Sleep(gs*2);
	}
	else{
		cout << "..." << endl;
		Sleep (gs);
		cout << ":(" << endl;
		Sleep (gs/2);
		invalid();
		checkinput();
		cout << endl;
		goto sec13;
	}
    sec14:
    cout << "..." << endl;
    Sleep(gs);
    cout << "How fast did you get the search results?" << endl;
    cout << "--- OPTION ---" << endl;
	cout << "1. Almost immediately!" << endl;
    cout << "Enter your option:";
	cin >> choice;
	getchar();
	choiceStore(choice);
    if(choice == 1){
        cout << "..." << endl;
        Sleep(gs);
        cout << "Yup!" << endl;
        Sleep(gs*2.5);
	}
	else{
		cout << "..." << endl;
		Sleep (gs);
		cout << ":(" << endl;
		Sleep (gs/2);
		invalid();
		checkinput();
		cout << endl;
		goto sec14;
	}
	cout << "That's the speed of life today, which allows me to communicate almost instantly with you." << endl;
	Sleep(gs/2);
	cout << "..." << endl;
	Sleep(gs*2);
	cout << "We have also been shaped by our way of life to desire immediate results." << endl;
	Sleep(gs/2);
	cout << "..." << endl;
    Sleep(gs*2);
    cout << "Sometimes, even instant gratification takes too long" << endl;
    Sleep(gs*2);
    cout << "..." << endl;
    Sleep(gs);
    cout << "Today, I have a Time Shuriken with me,";
    Sleep(gs*2);
    cout <<" and I can take you back to the distant past, or the mystifying future" << endl;
    Sleep(gs*2);
    cout <<"There's only one limitation though" << endl;
    Sleep(gs);
    cout << "You can only use the Time Shuriken by being in contact with me through this window." << endl;
    Sleep(gs);
    cout << "This..."; Sleep(gs/2); cout << "microsoft window ";
    Sleep(gs/2);
    cout << ";)" << endl;

    Sleep(gs*3);
    sec15:
    cout << "..." << endl;
    Sleep(gs);
    //////////////////////////////////////////////////DELAY SET//////////////////////////////////
    setgs(1000);
    cout << "Shall we proceed?" << endl;
    cout << "--- OPTION ---" << endl;
	cout << "1. YES!" << endl;
    cout << "Enter your option:";
	cin >> choice;
	getchar();
	choiceStore(choice);
    if(choice == 1){
        cout << "..." << endl;
        Sleep(gs);
        cout << "let's go!" << endl;
        Sleep(gs*2.5);
	}
	else{
		cout << "..." << endl;
		Sleep (gs);
		cout << ":(" << endl;
		Sleep (gs/2);
		invalid();
		checkinput();
		cout << endl;
		goto sec15;
	}

    transition.play(0);

}
void section2(){    //the 1950s
    cout << "Scenario 2: The 1950s\n\n" << endl;
    sec2:
    Sound spring("vSpring.wav"); //credits https://www.youtube.com/watch?v=l-dYNttdgl0
    spring.play(1);
    setgs(1000);
    cout << "Hi " << name << "!" << endl;
    Sleep(gs);
    cout << "..." << endl;
    Sleep(gs);
    cout << "Welcome to New York City, Year 1951!" << endl;
    Sleep(gs*2);
    cout << "I shall now teleport you to Singapore while I'll stay here" << endl;
    Sleep(gs*3);
    cout << "Beep Beep Boop!" << endl;
    Beep(1568,gs);
    Beep(1568,gs);
    Beep(261,gs);

    Sound SOTN("INSOTN.wav"); //credits https://www.youtube.com/watch?v=MRb1-SAAIzs&index=1&list=PL40C8D7843B0ADB17
    SOTN.play(1);

    for (int i = 0; i <= 20; i++){
        cout << "time: 0 min " << i << " sec..." << endl;
        Sleep(gs);
    }
    sec21:
    cout << endl;
    cout << "Hello "<< name << ", are you still there?" << endl;
    cout << "--- OPTION ---" << endl;
    cout << "1. Yes!" << endl;
    cout << "Enter your option:";
    cin >> choice;
    getchar();
    choiceStore(choice);
    if(choice == 1){
        validSound();
        cout << "...speeding up time..." << endl;
        Sleep(gs);
        setgs(200);
        for (int i = 0; i <= 20; i++){
            cout << "time: 0 min " << i<< " sec..." << endl;
            Sleep(gs);
        }
        setgs(1000);
        cout << endl;
        cout << endl;
        cout << "Sorry I took so long..." << endl;
        Sleep(gs*2);
    }
    else{
        cout << "..." << endl;
        Sleep (gs);
        cout << ":(" << endl;
        Sleep (gs/2);
        invalid();
        checkinput();
        cout << endl;
        goto sec21;
    }

    cout << "In fact, the actual time taken for me to communicate with you" << endl;
    Sleep(gs*2);
    cout << "by Air Mail, (long distance calls were not within reach of the general population because of the price)" << endl;
    Sleep(gs*3);
    cout << endl;
    cout << endl;
    cout << "...speeding up time..." << endl;
    Sleep(gs);
    cout << endl;
    cout << endl;
    setgs(200);
    for (int i = 0; i <= 20; i+=2){
        cout << "time: 0 min " << i<< " sec..." << endl;
        Sleep(gs);
    }
    setgs(1000);
    cout << "..." << endl;
    cout << endl;
    cout << endl;
    Sleep(gs);
    cout << "Would have taken at least 8640 times more than the time you've waited" << endl;
    Sleep(gs*4);
    cout << endl;
    cout << endl;
    cout << "...speeding up time..." << endl;
    Sleep(gs);
    setgs(200);
    for (int i = 0; i <= 20; i+=2){
        cout << "time: 0 min " << i<< " sec..." << endl;
        Sleep(gs);
    }
    setgs(1000);
    cout << endl;
    cout << endl;
    cout << "Well..." << endl;
    Sleep(gs);
    cout << "Do you feel the annoyance of the wait, or perhaps, the joyful slow moments of the good old days?" << endl;
    Sleep(gs*3);
    cout << endl;
    sec22:
    cout << "Shall we appreciate this moment of slowness together, or shall we skip ahead?" << endl;
    cout << "--- OPTION ---" << endl;
    cout << "1. Skip Ahead:" << endl;
    cout << "2. Stay and appreciate the slowness of the music and wait" << endl;
    cout << "Enter your option:";
    cin >> choice;
    getchar();
    choiceStore(choice);
    if(choice == 1){
        validSound();
        goto sec23;
    }
    else if(choice == 2){
        validSound();
        cout<< "Select Song" << endl;
        cout << "--- OPTION ---" << endl;
        cout << "1. Vivaldi Spring:" << endl;
        cout << "2. Still of the Night" << endl;
        cout << "Enter your option:";
        cin >> choice;
        getchar();
        choiceStore(choice);
        if (choice == 1)
        spring.play(1);
        else
        SOTN.play(1);
        cout << "Press 1 to skip" << endl;
        cin >> placeholder;
    }
    else{
        cout << "..." << endl;
        Sleep (gs);
        cout << ":(" << endl;
        Sleep (gs/2);
        invalid();
        checkinput();
        cout << endl;
        goto sec22;
    }
    sec23:
    cout << "Okay that's all for the 1950s" << endl;
    Sleep(gs*2);
    cout << "Let me take you back to the warp zone" << endl;
    Sleep(gs);
    transition.play(0);
}
void section3(){    //the early 2000s
    cout << "Scenario 3: The early 2000s\n\n" << endl;
    setgs(1000);
    cout << "Awaiting connection" << endl;
    Sleep(gs*2);
    cout << "Performing computer handshake" << endl;

    Sound dialUp("dialUp.wav"); //credits https://www.youtube.com/watch?v=gsNaR6FRuO0
    dialUp.play(0);
    cout << "Connection complete" << endl;
    Sleep(gs*2);
    Sleep(gs);
    cout << "Hello " << name << ", welcome to the early 2000s" << endl;
    Sound SOMH("SOMH.wav"); //credits https://www.youtube.com/watch?v=OT5msu-dap8
    SOMH.play(1);
    Sleep(gs*2);
    cout << endl;
    cout << "Error. File download incomplete" << endl;
    SOMH.play(1);
    Sleep(gs*3);
    cout << endl;
    cout << "Seems like the internet isn't fast enough to play music directly" << endl;
    Sleep(gs*3);
    cout << endl;
    SOMH.play(1);
    Sleep(5);
    cout << "Error. File download incomplete" << endl;
    silent.play(1);
    invalidSound();

    cout << endl;
    cout << endl;

    cout << "...speeding up time..." << endl;
    Sleep(gs);
    setgs(200);
    for (int i = 0; i <= 60; i+=3){
        cout << "time: 0 min " << i<< " sec..." << endl;
        Sleep(gs);
    }
    setgs(1000);
    cout << "Download complete" << endl;
    SOMH.play(1);
    cout << endl;
    cout << endl;
    Sleep(gs*2);
    cout << "The internet allowed speed to improve over time, as compared to the 1950s, allowing time to pass more \'quickly\'" << endl;
    cout << "as we focus on completing more things throughout the day." << endl;
    Sleep(gs*3.5);
    cout << "As society progresses and as time passes, well...";
    Sleep(gs*2);
    cout << " do you feel that time passes more quickly?" << endl;
    Sleep(gs*2);
    sec31:
    cout << "--- OPTION ---" << endl;
    cout << "1. Yes" << endl;
    cout << "2. Not really." << endl;
    cout << "Enter your option:";
    cin >> choice;
    getchar();
    choiceStore(choice);
    if(choice == 1){
        validSound();
        cout << "..." << endl;
        Sleep(gs*2);
        cout << "I feel that way too, as people appreciate their moments in time less" << endl;
        Sleep(gs*2.5);
        cout << "In a society thats gradually speeding up" << endl;
        Sleep(gs);
        cout << "..." << endl;
        Sleep(gs*2.5);
        cout << "Moments of time starts to pass in the flash of an eye as the speed of society increases..." << endl;
        Sleep(gs*3);
        cout << endl;
    }
    else if (choice == 2){
        validSound();
        cout << "Hmm" << endl;
        Sleep(gs);
        cout << "For me, I feel that overall, people appreciate their moments in time less" << endl;
        Sleep(gs);
        cout << "..." << endl;
        Sleep(gs*2);
        cout << "Causing time to pass much more quickly" << endl;
        Sleep(gs*1.5);
        cout << "By having an increasing number of things on our schedule as the speed of society increases" << endl;
        Sleep (gs);
        cout << "..." << endl;
        Sleep(gs*3);
        cout << "Time starts to pass in the flash of an eye" << endl;
        cout << endl;
    }
    else{
        cout << "..." << endl;
        Sleep (gs);
        cout << ":(" << endl;
        Sleep (gs/2);
        invalid();
        checkinput();
        cout << endl;
        goto sec31;
    }

    Sleep(gs*2);
    cout << "This brings me to the end of the early 2000s" << endl;
    Sleep(gs*2);

    cout << "Shall we head back to the warp zone?" << endl;
    cout << "Press 1 to continue" << endl;
    cin >> placeholder;
    validSound();
    Sleep(gs);
    transition.play(0);
}
void fastStory(){   //section 4 subfunction
    setgs(600);
    if(uresp == 77)
    setgs(800);
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    Once   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    upon   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |     a     |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    time   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    there  |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    were   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    three  |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   little  |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    pigs   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    One    |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   built   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |     a     |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   straw   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   house   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    ,      |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    the    |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   other   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |     a     |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    stick   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    house  |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    and    |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    the    |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    last   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |     a     |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   brick   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   house   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |     .     |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    When   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |     the   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    wolf   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    came   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    and    |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   huffed  |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    and    |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   puffed  |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |     he    |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    blew   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    all    |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   except  |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    the    |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   brick   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |   house   |"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/4);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |    down   |"<< endl;
    cout << endl;
    cout << endl;


    setgs(1000);
}
void section4(){    //the FUTURE
    cout << "Scenario 4: The Future\n\n" << endl;
    Sound future("future.wav");
    future.play(1);

    setgs(200);
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands!" << endl;
    Sleep(gs);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands!" << endl;
    Sleep(gs);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands!" << endl;
    Sleep(gs);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands!" << endl;
    Sleep(gs);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands!" << endl;
    Sleep(gs);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands!" << endl;
    Sleep(gs);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands!" << endl;
    Sleep(gs);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands!" << endl;
    Sleep(gs);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Lorem Ipsum dolor sit amet Lorem Ipsum dolor sit amet!" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands!" << endl;
    Sleep(gs);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands!" << endl;
    Sleep(gs);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    setgs(1000);
    cout << endl;
    cout << "..." << endl;
    cout << "Oops" << endl;
    Sleep(gs/5);
    cout << "Oops" << endl;
    Sleep(gs/5);
    cout << "Oops" << endl;
    Sleep(gs/5);
    cout << "Oops" << endl;
    Sleep(gs/5);
    cout << "Oops" << endl;
    Sleep(gs/5);
    cout << "Oops" << endl;
    Sleep(gs/5);
    cout << "Oops" << endl;
    Sleep(gs*2);
    cout << endl;
    cout << "pardon me, let me slow down the time for you to catch up" << endl;
    Sleep(gs/5);
    cout << "pardon me, let me slow down the time for you to catch up" << endl;
    Sleep(gs/5);
    cout << "pardon me, let me slow down the time for you to catch up" << endl;
    Sleep(gs/5);
    cout << "pardon me, let me slow down the time for you to catch up" << endl;
    Sleep(gs/5);
    cout << "pardon me, let me slow down the time for you to catch up" << endl;
    Sleep(gs/5);
    cout << "pardon me, let me slow down the time for you to catch up" << endl;
    Sleep(gs/5);
    cout << "pardon me, let me slow down the time for you to catch up" << endl;
    Sleep(gs/5);
    cout << "pardon me, let me slow down the time for you to catch up" << endl;
    Sleep(gs/5);
    cout << "pardon me, let me slow down the time for you to catch up" << endl;
    Sleep(gs*2);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Time set: 1 second current time -> 10 seconds your time" << endl;
    cout << "..." << endl;
    Sleep(gs*5);

    Sound futureSlow("futureSlow.wav");
    futureSlow.play(1);

    cout << "Phew. Let's restart" << endl;
    Sleep(gs*2);
    cout << "Hey " << name << ", welcome to the year 2073" << endl;
    Sleep(gs*2);
    cout << endl;
    cout << "Scientists have already invented telepathic headbands" << endl;
    Sleep(gs*2);
    cout << "Waiting for someone to type/read is a thing of the past!" << endl;
    Sleep(gs);
    cout << "..." << endl;
    Sleep(gs*2);
    cout << "Many many more things can now be accomplished in just a flash" << endl;
    Sleep(gs*2);
    cout << "And society is more productive than ever" << endl;
    Sleep(gs);
    cout << "..." << endl;
    Sleep(gs*2);
    cout << "However, this speed brought about some side effects" << endl;
    Sleep(gs);
    cout << "..." << endl;
    Sleep(gs*2);
    cout << "Because of instant telepathic communication that is blazingly fast, voice communications are becoming a thing of the past" << endl;
    Sleep(gs*3);
    cout << endl;
    cout << "..." << endl;
    cout << "Here, I'll let you experience the speed of communication that is implemented in the future." << endl;
    cout << endl;
    Sleep(gs*3);
    cout << "Read the story that will be displayed word by word," << endl;
    cout << "                                ___________" << endl;
    cout << "by looking at this exact spot->|___________|" << endl;
    cout << endl;
    cout << "Press 1 to continue" << endl;
    cin >> placeholder;

    future.play(1);

    sec40:

    Sleep(gs*2);
    cout << "                                ___________" << endl;
    cout << "Ready?         5               |___________|"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs);
    cout << "                                ___________" << endl;
    cout << "Ready?         4               |___________|"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs);
    cout << "                                ___________" << endl;
    cout << "Ready?         3               |___________|"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs);
    cout << "                                ___________" << endl;
    cout << "Ready?         2               |___________|"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs);
    cout << "                                ___________" << endl;
    cout << "Ready?         1               |___________|"<< endl;
    cout << endl;
    cout << endl;
    Sleep(gs/2);
    cout << "                                            " << endl;
    cout << "Ready?         START ->        |           |"<< endl;
    cout << endl;
    cout << endl;

    fastStory();

    sec41:
    cout << "Did you catch all of that?" << endl;
    cout << "--- OPTION ---" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No, let's slow it down and do it again" << endl;
    cout << "Enter your option:";
    cin >> choice;
    getchar();
    choiceStore(choice);
    if(choice == 1){
        validSound();

    }
    else if(choice == 2){
        uresp = 77;
        validSound();
        goto sec40;
    }
    else{
        cout << "..." << endl;
        Sleep (gs);
        cout << ":(" << endl;
        Sleep (gs/2);
        invalid();
        checkinput();
        cout << endl;
        goto sec41;
    }

    futureSlow.play(1);
    cout << "Amazing isn't it, being able to read so quickly." << endl;
    Sleep(gs);
    cout << "..." << endl;
    Sleep(gs*2);
    cout << "Even though you are able to accomplish this, do you feel that..." << endl;
    Sleep(gs*2);
    cout << "doing so for extended periods of time tires you out?" << endl;
    Sleep(gs*2);
    cout << "What if bedtime stories, lunchtime conversations, and late night heart to heart talks," << endl;
    Sleep(gs*3);
    cout << "are done at this speed?" << endl;
    Sleep(gs);
    cout << "..." << endl;
    Sleep(gs);
    cout << "Even though tasks can be completed, things can be done, doesn't this..." << endl;
    Sleep(gs*2);
    cout << "lower the quality of time spent?" << endl;
    cout << "..." << endl;
    Sleep(gs*2);
    cout << "Which makes time go even \'faster\' as we remember less about our days with hectic speeds?" << endl;
    Sleep(gs);
    cout << "..." << endl;
    Sleep(gs);
    cout << "..." << endl;

    sec42:
    cout << "Shall we head back to the warp zone?" << endl;
    cout << "--- OPTION ---" << endl;
    cout << "1. Yes" << endl;
    cout << "Enter your option:";
    cin >> choice;
    getchar();
    choiceStore(choice);
    if(choice == 1){
        validSound();
        cout << "..." << endl;
        Sleep(gs);
        cout << "let's go!" << endl;
        Sleep(gs*2.5);
    }
    else{
        cout << "..." << endl;
        Sleep (gs);
        cout << ":(" << endl;
        Sleep (gs/2);
        invalid();
        checkinput();
        cout << endl;
        goto sec42;
    }

    transition.play(0);

}
void credits(){     //to state references and sources
    Sound credits("credits.wav");
    credits.play(1);
    cre1:
    cout << "Skip Credits?" << endl;
    cout << "--- OPTION ---" << endl;
    cout << "1. No" << endl;
    cout << "2. No" << endl;
    cout << "3. No" << endl;
    cout << "4. Okay you can skip it" << endl;
    cout << "Enter your option:";
    cin >> choice;
    getchar();
    choiceStore(choice);
    if(choice == 4){
        cout << "..." << endl;
        Sleep(gs);
        cout << "..." << endl;
        Sleep(gs*2.5);
        goto endCre;
    }
    else if(choice == 1 || choice == 2 || choice == 3){

    }
    else{
        cout << "..." << endl;
        Sleep (gs);
        cout << ":(" << endl;
        Sleep (gs/2);
        invalid();
        checkinput();
        cout << endl;
        goto cre1;
    }
    cout << endl;
    cout << "Project Done By: Chun Hong Wei" << endl;
    cout << "Time and Life Semester 2 AY17/18" << endl;
    cout << "Full code on https://github.com/driedmelon" << endl;
    cout << endl;
    Sleep(gs*3);

    cout << "Copyright Disclaimer Under Section 107 of the Copyright Act 1976, allowance is made for -fair use-" << endl;
    cout << "for purposes such as criticism, comment, news reporting, teaching, scholarship, and research. Fair " << endl;
    cout << "use is a use permitted by copyright statute that might otherwise be infringing. Non-profit, " << endl;
    cout << "educational or personal use tips the balance in favor of fair use." << endl;
    cout << endl;
    cout << endl;
    Sleep(gs*3);

    cout << "Project Inspiration: Seen game on Google Playstore" << endl;
    cout << endl;
    Sleep(gs);
    cout << "Music Credits: start.wav (LittleRoot Town Pokemon Omega Ruby https://www.youtube.com/watch?v=3sXqypTqUKY)" << endl;
    cout << endl;
    Sleep(gs);
    cout << "Music Credits: welcome.wav (Pokemon UltraSun Welcome music https://www.youtube.com/watch?v=Q5RwmrKRm2Y)" << endl;
    cout << endl;
    Sleep(gs);
    cout << "Music Credits: RFIY.wav (Yiruma River flows in you https://www.youtube.com/watch?v=7maJOI3QMu0)" << endl;
    cout << endl;
    Sleep(gs);
    cout << "Music Credits: vSpring.wav (Vivaldi Spring https://www.youtube.com/watch?v=l-dYNttdgl0)" << endl;
    cout << endl;
    Sleep(gs);
    cout << "Music Credits: INSOTH.wav (In still of the night - The five satins https://www.youtube.com/watch?v=MRb1-SAAIzs)" << endl;
    cout << endl;
    Sleep(gs);
    cout << "Music Credits: dailUp.wav (dialup modem sound https://www.youtube.com/watch?v=gsNaR6FRuO0)" << endl;
    cout << endl;
    Sleep(gs);
    cout << "Music Credits: SOMH.wav (Backstreet boys - Shape of my heart https://www.youtube.com/watch?v=OT5msu-dap8)" << endl;
    cout << endl;
    Sleep(gs);
    cout << "Music Credits: future.wav & credits.wav (Russian Electrohouse Mix 70 https://www.youtube.com/watch?v=T5A8RTGnAmA)" << endl;
    cout << endl;
    Sleep(gs);
    cout << "Music Credits: futureSlow.wav (Maplestory HallofFame Happyville http://www.thejasoneffect.net/maple-story-ost/)" << endl;
    cout << endl;
    Sleep(gs);
    cout << "I will like to thank:" << endl;
    cout << endl;
    Sleep(gs);
    cout << "I will like to thank: Dr Celine for her guidance and pointers" << endl;
    cout << endl;
    Sleep(gs);
    cout << "I will like to thank: Boston Cheong for his time for testing out the app and giving feedback" << endl;
    cout << endl;
    Sleep(gs);
    cout << "I will like to thank: Tembusu College for being the home of possibilities" << endl;
    cout << endl;
    Sleep(gs);
    cout << "I will like to thank: My time and life classmates" << endl;
    endCre:
    cout << endl;
    Sleep(gs*2.5);
    cout << "     TTTTTTTTTTTTT  H         H  EEEEEEEEEE      EEEEEEEEEE   N       N   DDDDDD             " << endl;
    cout << "          TT        H         H  E               E            NN      N   D     DD           " << endl;
    cout << "          TT        H         H  E               E            N N     N   D      DD          " << endl;
    cout << "          TT        H         H  E               E            N  N    N   D       DD         " << endl;
    cout << "          TT        HHHHHHHHHHH  EEEEEE          EEEEEE       N   N   N   D        D         " << endl;
    cout << "          TT        H         H  E               E            N    N  N   D        D         " << endl;
    cout << "          TT        H         H  E               E            N     N N   D       D          " << endl;
    cout << "          TT        H         H  E               E            N      NN   D      D           " << endl;
    cout << "          TT        H         H  EEEEEEEEEEE     EEEEEEEEEEE  N       N   DDDDDDD            " << endl;
    Sleep(gs*3);
    cout << endl;
    cout << "Fin. Exit Simulation?" << endl;
	cout << "--- OPTION ---" << endl;
	cout << "1. No, Head back to the Warp Zone" << endl;
	cout << "2. Yes" << endl;
	cout << "Enter your option:";
	cin >> uresp;
	if (uresp == 1){
		validSound();
		flushScreen();
	}
}

//MAIN FUNCTION
int main(void){
	time_t timestart = time(0);

	start:
	preintro();

	introMsg:
	intromsg();

    if (uresp == 99){
        warpZoneStart:
        flushScreen();
        timeTravel.play(1);
        warpZone:
        flushScreen();
        if (complete.size() == 4){
            goto theEnd;
        }
        cout << "Welcome to the warp zone!" << endl;
        cout << "--- OPTION ---" << endl;
        cout << "Select story section:" << endl;
        cout << endl;
        if(complete.find(1)== complete.end()){
        cout << "    1                  " << endl;
        cout << "    1                  " << endl;
        cout << "    1       Present Day" << endl;
        cout << "    1                  " << endl;
        cout << "    1                  " << endl;
        cout << endl;
        }
        if(complete.find(2)== complete.end()){
        cout << "  22222                " << endl;
        cout << "      22               " << endl;
        cout << "     22       The 1950s" << endl;
        cout << "   22                  " << endl;
        cout << "  2222222              " << endl;
        cout << endl;
        }
        if(complete.find(3)== complete.end()){
        cout << "  33333                " << endl;
        cout << "      33               " << endl;
        cout << "    333     Early 2000s" << endl;
        cout << "      33               " << endl;
        cout << "  33333                " << endl;
        cout << endl;
        }
        if(complete.find(4)== complete.end()){
        cout << "     4                 " << endl;
        cout << "    44                 " << endl;
        cout << "   4 4       The Future" << endl;
        cout << "  4444444              " << endl;
        cout << "     4                 " << endl;
        cout << endl;
        }
        cout << endl;
        cout << "5. Return to Welcome Message" << endl;
        cout << "6. View Credits and end" << endl;
        if(creditStatus == 1)
        cout << "88. End Program" << endl;
        cout << endl;

        cout << "Enter your option:";
        cin >> uresp;
        if(uresp == 1){
            Sleep(gs);
            validSound();
            flushScreen();
            transition.play(0);
            goto sec1;
        }
        else if (uresp == 2){
            Sleep(gs);
            validSound();
            flushScreen();
            transition.play(0);
            goto sec2;
        }
        else if (uresp == 3){
            Sleep(gs);
            validSound();
            flushScreen();
            transition.play(0);
            goto sec3;
        }
        else if (uresp == 4){
            Sleep(gs);
            validSound();
            flushScreen();
            transition.play(0);
            goto sec4;
        }
        else if (uresp == 5){
            Sleep(gs);
            validSound();
            flushScreen();
            transition.play(0);
            goto introMsg;
        }
        else if (uresp == 6){
            Sleep(gs);
            validSound();
            flushScreen();
            transition.play(0);
            goto theEnd;
        }
        else if (uresp == 88){
            Sleep(gs);
            validSound();
            flushScreen();
            transition.play(0);
            goto theEndEnd;
        }
        else{
            Sleep(gs);
            invalid();
            checkinput();
            cout << "..." << endl;
            goto warpZone;
        }
    }

	sec1:
    //present day
	section1();
	complete.insert(1);
	goto warpZoneStart;

	sec2:
    //the1950s
    section2();
    complete.insert(2);
    goto warpZoneStart;

    sec3:
    //the early 2000s
    section3();
    complete.insert(3);
    goto warpZoneStart;

    sec4:
    //the future
    section4();
    complete.insert(4);
    goto warpZoneStart;

    theEnd:
    credits();
    if (uresp == 1){
    complete.erase(1);
    complete.erase(2);
    complete.erase(3);
    complete.erase(4);
    goto warpZoneStart;
    }
    theEndEnd:
    transition.play(1);
    cout << endl;
    cout << "Back to reality:" << endl;
    cout << endl;
    checktime(timestart);
    Sleep(gs/2);
    checktime(timestart);
    Sleep(gs/2);
    checktime(timestart);
    Sleep(gs/2);
    checktime(timestart);
    Sleep(gs/2);
    cout << endl;
    cout << "Goodbye " << name << ", have a nice day" << endl;
    Sleep(gs*5);

	return 0;
}

