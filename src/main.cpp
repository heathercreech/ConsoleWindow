#include "scapplication.h"
#include "console.h"

int main(int argc, char* argv[]){
	Application app;
	app.init();
	
	
	//create and add the console object to the app
	ConsolePosition pos;
	ConsoleRenderer con_ren(&app, pos);
	ConsoleLogic con_logic(&app, &con_ren);
	ApplicationObject con_object(&app, &con_ren, &con_logic);
	app.addObject(&con_object);
	
	
	app.loop();
	return 0;
}