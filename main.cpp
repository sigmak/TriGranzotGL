/*
	Author: sigmak(dwfree74@gmail.com)
	Date: 01-12-15 02:34
	Description: Mp3 library example
*/

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <Mmsystem.h>
#include "audiere.h"

#define SND_FILENAME 0x20000
#define SND_LOOP 8
#define SND_ASYNC 1 

//#pragma comment(lib, "winmm.lib")
// [Linker error] undefined reference to `PlaySoundA@12'
// 해결: http://www.cplusplus.com/forum/beginner/733/
//project > project options > parameters and type "-lwinmm" in the LINKER section.

//#pragma comment(lib, "audiere.lib")
//project > project options > parameters and type "audiere.lib" in the LINKER section.


using namespace std;
using namespace audiere;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//http://sourceforge.net/projects/audiere/
int main(int argc, char** argv) {
  // 예제 출처 : http://d.hatena.ne.jp/rinsyan0518/20111218/1324226234
   AudioDevicePtr device(OpenDevice());
        if (!device) {
                cerr << "Could not open audiere device" << endl;
                exit(1);
        }
        //SampleSourcePtr source = OpenSampleSource(argv[1]);
        SampleSourcePtr source = OpenSampleSource("test.mp3");
        OutputStreamPtr sound = OpenSound(device, source);
        if (!sound) {
                cerr << "Failed to open sound" << endl;
                exit(1);
        }
        sound->setRepeat(true);

        sound->play();
        while (sound->isPlaying()) {
                device->update();
                Sleep(1);
        }   
    system("PAUSE");	
	return 0;
}
