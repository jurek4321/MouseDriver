//============================================================================
// Name        : MouseControl.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <gtk/gtk.h>
#include "config.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <usb.h>
using namespace std;
bool logEn = false;
config c;

uint16_t supportedVidPid[2][2] = {
		{0x04d9, 0xfc02},
		{0x04d9, 0xfc55},
};

uint8_t btn_codesH[] = {0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x57, 0x56};

GtkEntry        *t1_Text  ;
GtkEntry        *t2_Text  ;
GtkEntry        *t3_Text  ;
GtkEntry        *t4_Text  ;
GtkEntry        *t5_Text  ;
GtkEntry        *t6_Text  ;
GtkEntry        *t7_Text  ;
GtkEntry        *t8_Text  ;
GtkEntry        *t9_Text  ;
GtkEntry        *t10_Text  ;
GtkEntry        *t11_Text  ;
GtkEntry        *t12_Text  ;

GtkBuilder      *builder;

void load() {
	gtk_entry_set_text( t1_Text,c.readmouse(0));
	gtk_entry_set_text( t2_Text,c.readmouse(1));
	gtk_entry_set_text( t3_Text,c.readmouse(2));
	gtk_entry_set_text( t4_Text,c.readmouse(3));
	gtk_entry_set_text( t5_Text,c.readmouse(4));
	gtk_entry_set_text( t6_Text,c.readmouse(5));
	gtk_entry_set_text( t7_Text,c.readmouse(6));
	gtk_entry_set_text( t8_Text,c.readmouse(7));
	gtk_entry_set_text( t9_Text,c.readmouse(8));
	gtk_entry_set_text( t10_Text,c.readmouse(9));
	gtk_entry_set_text( t11_Text,c.readmouse(10));
	gtk_entry_set_text( t12_Text,c.readmouse(11));
}

bool save() {
	int e = 0;

	e += (int)c.writemouse(0,( char*)gtk_entry_get_text (t1_Text));
	e += (int)c.writemouse(1,( char*)gtk_entry_get_text (t2_Text));
	e += (int)c.writemouse(2,( char*)gtk_entry_get_text (t3_Text));
	e += (int)c.writemouse(3,( char*)gtk_entry_get_text (t4_Text));
	e += (int)c.writemouse(4,( char*)gtk_entry_get_text (t5_Text));
	e += (int)c.writemouse(5,( char*)gtk_entry_get_text (t6_Text));
	e += (int)c.writemouse(6,( char*)gtk_entry_get_text (t7_Text));
	e += (int)c.writemouse(7,( char*)gtk_entry_get_text (t8_Text));
	e += (int)c.writemouse(8,( char*)gtk_entry_get_text (t9_Text));
	e += (int)c.writemouse(9,( char*)gtk_entry_get_text (t10_Text));
	e += (int)c.writemouse(10,( char*)gtk_entry_get_text (t11_Text));
	e += (int)c.writemouse(11,( char*)gtk_entry_get_text (t12_Text));
	if (e == 12) {
		return true;
	} else {
		return false;
	}
}

void Cancel_clicked_cb() {
	 gtk_main_quit();
}

void Save_clicked_cb() {
   if  (!save()) {
	   g_print("błąd zapisu");
	   gtk_main_quit();
   }
}

void on_window_main_destroy(GtkWidget *widget, gpointer   data ){
	 gtk_main_quit();
}

void gtksettings(int argc, char* argv[]){
	GtkWidget *buttonCancel,*buttonSave;
	GtkWidget       *window;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();

	char *homedir1;
	if ((homedir1 = getenv("HOME")) == NULL) {
		homedir1 = getpwuid(getuid())->pw_dir;
	}
	string homedir = homedir1;
	string view_file_name_std = homedir + "/.config/MouseControl_view.glade";
	gtk_builder_add_from_file (builder, view_file_name_std.c_str(), NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	buttonCancel = GTK_WIDGET(gtk_builder_get_object (builder, "Cancel"));
	buttonSave = GTK_WIDGET(gtk_builder_get_object (builder, "Save"));

	t1_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t1"));
	t2_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t2"));
	t3_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t3"));
	t4_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t4"));
	t5_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t5"));
	t6_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t6"));
	t7_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t7"));
	t8_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t8"));
	t9_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t9"));
	t10_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t10"));
	t11_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t11"));
	t12_Text = GTK_ENTRY(gtk_builder_get_object(builder, "t12"));

	c.init();

	g_signal_connect (buttonCancel, "clicked", G_CALLBACK(Cancel_clicked_cb), NULL);
	g_signal_connect (buttonSave, "clicked", G_CALLBACK(Save_clicked_cb), NULL);
	g_signal_connect (window, "destroy", G_CALLBACK(on_window_main_destroy), NULL);

	g_object_unref(builder);

	gtk_widget_show(window);

	load();

	gtk_main();
}

bool matchUsbVidPid(uint16_t vid, uint16_t pid) {
	int elems = sizeof(supportedVidPid)/sizeof(supportedVidPid[0]);
	for (int i =0; i < elems; i++) {
		if (vid == supportedVidPid[i][0] && pid == supportedVidPid[i][1])
			return true;
	}
	return false;
}


void deamon2() {
	c.init();
	while (true) {
		struct usb_bus *busses;
	    struct usb_bus *bus;
	    struct usb_device *dev;
	    char data[8];

	    usb_init();
	    usb_find_busses();
	    usb_find_devices();
	    busses = usb_get_busses();
		if (logEn) printf("Szukanie urządenia ....");

	    for (bus = busses; bus; bus = bus->next) {
	    	for (dev = bus->devices; dev; dev = dev->next) {
	    		if (matchUsbVidPid(dev->descriptor.idVendor, dev->descriptor.idProduct)) {
	    			usb_dev_handle *l_Handle = usb_open( dev);
	    			if( NULL == l_Handle ){
	    				exit(0);
	    			}
	    			usb_detach_kernel_driver_np(l_Handle,1);
	    			int res = usb_claim_interface(l_Handle, 1);
	    			if (logEn) {
	    				if(res  == -16) {printf("Device interface not available to be claimed! \n"); }
	    				if(res == -12) {printf("Insufficient Memory! \n"); }
	    				printf("usb_claim_interface rsp: %d\n", res);
	    			}
	    			bool work = true;
	    			while (work) {
	    				memset(data, 0x00, 8);
	    				int readRsp = usb_interrupt_read(l_Handle, 0x82, data, 8, 1500);
	    				if (readRsp < 0 && readRsp != -110) {
	    					work = false;
	    					break;
	    				}
	    				for (int i = 0; i <8; i++) {
	    					if (data[i] && data[i] != 1) {
	    						for (int n=0; n<12; n++) {
	    							if (btn_codesH[n] == data[i]) {
	    								system(c.readmouse(n));
	    							}
	    						}
	    					}
	    				}
	    			}
	    			usb_release_interface(l_Handle, 0);
	    			usb_close(l_Handle);
	    		}
	    	}
	    }
	}
}

void info(char* argv[]) {
	cerr << "Użycie: " << argv[0] << " -G Ustawienia w okienku gtk" << endl;
	cerr << "Użycie: " << argv[0] << " -D Uruchomienie Deamona" << endl;
	cerr << "Użycie: " << argv[0] << " -DL Uruchomienie Deamona i wyświetlanie Logów" << endl;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		info(argv);
		return 1;
	}
	if (!(string(argv[1]) == "-D" || string(argv[1]) == "-G" || string(argv[1]) == "-DL" )) {
		info(argv);
		return 1;
	}
	if (string(argv[1]) == "-G") {
		gtksettings(argc,argv);
	}

	if (string(argv[1]) == "-D") {
		deamon2();
	}
	if (string(argv[1]) == "-DL") {
		logEn = true;
		deamon2();
	}
	return 0;
}
