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
#include "usb.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
using namespace std;
bool log = false;
config c;
char *homedir_1;
 std::string homedir2_1;
 const char *view_file_name = "config.cfg";
  std::string  view_file_name_std;
 char* btn_codes[] = {"1E", "1F", "20","21","22","23","24","25","26","27","57","56"};
void info(char* argv[]) {
	  // Użycie porgramu
		        std::cerr << "Użycie: " << argv[0] << " -G Ustawienia w okienku gtk" << std::endl;
		        std::cerr << "Użycie: " << argv[0] << " -D Uruchomienie Deamona" << std::endl;
		        std::cerr << "Użycie: " << argv[0] << " -DL Uruchomienie Deamona i wyświetlanie Logów" << std::endl;
}

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
//std::vector<GtkEntry > codebox(1);





//codebox* = [t1_Text,t2_Text];

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
	    if ((homedir_1 = getenv("HOME")) == NULL) {
	   	     homedir_1 = getpwuid(getuid())->pw_dir;
	   	 }
	   	 homedir2_1 = homedir_1;
	   	 view_file_name_std = homedir2_1 + "/.config/MouseControl_view.glade";
	   	 view_file_name = view_file_name_std.c_str();;
	    gtk_builder_add_from_file (builder, view_file_name, NULL);

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


void deamon2() {
	c.init();

	 char* tmp_btn;
	while (true) {

	    struct usb_bus *busses;
	    struct usb_bus *bus;
	    struct usb_device *dev;
	    int ce, i, res,rezs;
	res =0 ;
	    char data[765];
	    char idata[10];

	    usb_init();
	    usb_find_busses();
	    usb_find_devices();
	    busses = usb_get_busses();
		if (log ==true)
	    printf("Szukanie urządenia ....");

	    for (bus = busses; bus; bus = bus->next) {

	        for (dev = bus->devices; dev; dev = dev->next) {
	        if(dev->descriptor.idProduct == 0xfc02 && dev->descriptor.idVendor == 0x04d9) {
	     //   printf("Product id: %04hx" ,dev->descriptor.idProduct);
	     //   printf("Vendor id: %04hx \n" ,dev->descriptor.idVendor);

	        usb_dev_handle *l_Handle = usb_open( dev);
	        if( NULL == l_Handle ){
	        	if (log ==true)
	        	 printf("Brak myszki");
	        	 exit(0);
	        }
	usb_detach_kernel_driver_np(l_Handle,1);
	        res = usb_claim_interface(l_Handle, 1);
	    	if (log ==true) {
	        if(res  == -16) {printf("Device interface not available to be claimed! \n"); }
	        if(res == -12) {printf("Insufficient Memory! \n"); }
	        printf("code: %d \n",res);
	    	}
	rezs = usb_interrupt_read(l_Handle, 0x82, data, 8, 2500);



	 ce=-1;
	               for(i=1;i<8;i++) {
	            idata[++ce] = data[i];
	        }
	        ce=atoi(idata);
	     //   printf( "\nMy data : %d\n",c);

	for (i = 0; i <8; i++)
	{
	if (idata[i] != 0) {
		if (idata[i] != 01) {
	if (idata[i] != 00) {
		if (log ==true)
			printf("\n");
			 printf("===Uwaga Tu często pojawiają się błędy === \n");
	    printf("data: %02X \n", idata[i]);
		tmp_btn = "wErr01";

	    printf("pre parse \n");
	    char wm[3];
	    sprintf(wm,"%02X", idata[i]);
	    printf(wm);
	    tmp_btn = wm ;
	    printf("parse ok \n");
	    std::string s = "wErr02";
	    s = tmp_btn;

	    printf("set val ok val = ");
	    printf(tmp_btn);
	    printf("\n");
int n;
printf("===Tu już rzadziej=== \n");
	    for ( n=0 ; n<12 ; ++n )
	    {
	    	if (btn_codes[n] == s) {

	    		if (log ==true) {
printf("button : %d \n",n + 1);
printf(	c.readmouse(n ));
	    		}
system(c.readmouse(n ));
	    	}
	
	    }
// czyszczenie wartości zmiennych po wykonaniu testu
//s = "NN";
//tmp_btn = "NN";

	idata[i] = 0;

	}}}
	}


	        usb_release_interface(l_Handle, 0);
	        usb_close(l_Handle);
	        }
	       }
	    }

	}


}




int main(int argc, char* argv[]) {

	// Sprawdzenie poprawności argumentów
	 if (argc < 2) {
	      info(argv);
	        return 1;
	    }
	 if (!(std::string(argv[1]) == "-D" || std::string(argv[1]) == "-G" || std::string(argv[1]) == "-DL" )) {
		  info(argv);
		  return 1;
	 }
if (std::string(argv[1]) == "-G") {
	gtksettings(argc,argv);
}

if (std::string(argv[1]) == "-D") {
	deamon2();
}
if (std::string(argv[1]) == "-DL") {
	log = true;
	deamon2();
}

	    return 0;
}


