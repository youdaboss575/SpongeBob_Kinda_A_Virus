#include <allegro5/allegro_image.h> // image
#include <allegro5/allegro_audio.h> // audio
#include <allegro5/allegro_acodec.h>// codec
#include <allegro5/allegro.h> // allegro
#include <allegro5/allegro_windows.h> //Hide display
#include <time.h>
#include <random>
#include <windows.h>
#include <iostream>
#include "resource.h"
int main(){
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	//initializing
	srand((signed int) time(NULL));
	al_init();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	if (!al_init()) {
		std::cout << "Allegro Couldn't Be Initialized";
	}
	//Create Display
	ALLEGRO_DISPLAY* display = al_create_display(367, 370);;
	al_set_display_flag(display, ALLEGRO_FRAMELESS, true);
	//Create Bitmap
	ALLEGRO_BITMAP* image = al_load_bitmap("spung.png");
	if (!image) {
		std::cout << "VERY BAD";
	}
	//Audio
	al_reserve_samples(3);
	ALLEGRO_SAMPLE* vine_boom = al_load_sample("vine-boom.mp3");
	//Show/Hide
	HWND hwnd = al_get_win_window_handle(display);
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	while (true) {
		//Getting the time to wait and half your screen
		int amount = rand() % 600 + 60;
		int x = rand() % GetSystemMetrics(SM_CXFULLSCREEN) /2 + 1;
		int y = rand() % GetSystemMetrics(SM_CYFULLSCREEN) /2 + 1;
		//Draw image to back-buffer
		al_draw_bitmap(image, 0, 0, 0);
		//Flips back-buffer and play audio
		ShowWindow(hwnd, SW_SHOW);
		al_flip_display();
		al_set_window_position(display, x, y);
		al_play_sample(vine_boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		al_rest(1.5);
		//Hiding display
		ShowWindow(hwnd, SW_HIDE);
		al_rest(amount); //seconds
	}
	return 0;
}//main