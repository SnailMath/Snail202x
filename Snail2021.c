
#ifndef MOD_TXT
  #define MOD_TXT "'Place the default modification here"
#endif

#include <io.h> //access()
#include <stdio.h>
#include <stdlib.h> // system()
#include "zlib.h"   // gzip deflate() and inflate()

#define CHUNK 0x40000	//256k Chunks
#define LEVEL 6		//Compression level 6
#define memLevel 9	//Zlib, 1 - 9, 9 is best, fast and more compact.

#define true 1

int main(){

  system("color f0");

  int theMagicByte = 0;

  int resin86 = 0; // If resourceHacker is in x86 folder

  #define VERLEN 10
  char mod_ver[VERLEN+1] ; //The version written in mod.txt (10 characters )
  mod_ver[0]=0; //Initialize. this will stay like this, if there is no ver nr in mod.txt
  mod_ver[VERLEN]=0; //Add the terminating 0
 

  //The inflate stuff...
  z_stream strm;
  unsigned char  in[CHUNK];
  unsigned char out[CHUNK];
  int ret;

  //The file stuff
  FILE *Fin;
  FILE *Fout;
  FILE *Fin2;

  printf(
"This program was written by SnailMath (aka Pascal, aka Oberschnecke)\n\
This project was inspired by an article from the6p4c.\n\
This program uses the program \"Resource Hacker\".\n\
This program was written in C and compiled using \"gcc\" from \"minGW\".\n\
This program uses the libary \"zlib.h\" (mingw32-libz-dev).\n\
\n\
My first Video about this: Video: https://www.youtube.com/watch?v=Llibqwt7Jsg\n\
\n\
=============================================================================\n\
\n\
This program modifies the firmware of the Calculator.\n\
There is a Youtube video explaining the process on my Youtube channel.\n\
Channel: https://www.youtube.com/channel/UC4MX6_QKFwnA2sG9eGwqcjA\n\
hollyhock-2 on GitHub: https://github.com/SnailMath/hollyhock-2\n\
Snail202x   on GitHub: https://github.com/SnailMath/Snail202x\n\
\n\
If you have questions, ask me on Discord: https://discord.com/invite/fWxZXvy\n\
\n\
This whole project was inspired by an article by The6p4c. This is their page:\n\
https://the6p4c.github.io/2018/01/15/hacking-the-gc-part-1.html\n\
I'm not affiliated with him. I'm just a YouTube subscriber of them.\n\
\n\
So, first download the official updater. You need the correct version.\n\
If you are installing hollyhock-2, you need the version OSver2_01_2000 .\n\
You can download this specific version here:\n\
     tiplanet.org/forum/archives_voir.php?id=1044960 \n\
Download it, extract it and start it.\n\
This should start the installation of the actual clculator updater.\n\
You need to press OK and Agree multiple times.\n\
When it asks you to connect the calculator, just leave it open and come back\n\
to this window. We will extract the firmware from the temp files.\n\
\n\
[press ENTER to continue...]\n");
  char str[4];
  fgets(str, 3,stdin);
  if (str[0]=='q') return 0;

printf("\n\n\n\
You will need another program called \"Resource Hacker\" from angusj.com.\n\
Go on its official website, scroll down and select \"EXE install\".\n\
Just follow the installation instructions and don't change the path.\n\
     angusj.com/resourcehacker/\n\
(The license says, I'm not allowed to distribute it, so download it on your own!It says, only use it for legal stuff, using your own calculator is legal.)\n\n\
ONE IMPORTANT THING!!!\n\
This file (\"Snail2021.exe\") MUST be in a folder called Snail2021 on the Desktop.\n\
(because I'm lazy)\n\n\
\n\
Do you have done everything mentioned above? Let's go.\n\
(If you want to abort, type q and press enter.)\n\
\n\
[press ENTER to continue...]\n\n\n\n\n");
  fgets(str, 3,stdin);
  if (str[0]=='q') return 0;

  printf("Checking if Resource Hacker is installed...\n");
  if( access( "\\Program Files\\Resource Hacker\\ResourceHacker.exe", R_OK) != -1 ) { 
    printf("  OK\n"); 
  } else
  if( access( "\\Program Files (x86)\\Resource Hacker\\ResourceHacker.exe", R_OK) != -1 ) { 
    printf("  OK (x86)\n"); 
    resin86 = 1;
  } else {
    printf("\n  ERROR! Resource Hacker cannot be found at:\n\
  C:\\Program Files\\Resource Hacker\\ResourceHacker.exe  or\n\
  C:\\Program Files\\Resource Hacker (x86)\\ResourceHacker.exe\n\
  Pleas install this first. It must be in this path, because I'm lazy.\n\n");
    fgets(str, 3,stdin); return -1;
  }

  printf("\nChecking if updater is present...\n");
  if( 
  ( access("OSupdateDLL_orig.dll", R_OK) != -1 ) &&
  ( access("LanguageResource.dll", R_OK) != -1 ) &&
  ( access("fxASPI.dll", R_OK) != -1 ) ) {
    printf("  OK - all dlls where already present\n\n");
  } else {

    printf("  dlls not present, extracting from temp files...\n");
    system("copy ..\\..\\AppData\\Local\\Temp\\{15B89FD6-8906-4C3B-A271-A4B3A29D545A} .\\");
    system("move OSupdateDLL.dll OSupdateDLL_orig.dll");
    if(
    ( access("OSupdateDLL_orig.dll", R_OK) != -1 ) &&
    ( access("LanguageResource.dll", R_OK) != -1 ) &&
    ( access("fxASPI.dll", R_OK) != -1 ) ) {
      printf("  OK - all dlls where extracted\n\nYou can now close the updater.\n\n");
    } else {
      printf("\n  ERROR! The updater is not present.\n\
Did you download it from the official website?\n\
Is the updater program still open?\n\
Are the files in \"AppData/Local/Temp/{15B89FD6-8906-4C3B-A271-A4B3A29D545A}\"?\n\
Is this program in \"Desktop/Snail2021\"?\n\
If you have a question, ask on Discord: https://discord.com/invite/fWxZXvy !\n");
    fgets(str, 3,stdin); return -1; 
    }
  }

  //Now everything is there.

  printf("Let's begin. First I'm extracting 3070 and unzipping it to 3070_orig.bin.\n");
  if(access("3070_orig.bin", R_OK) != -1 ){
    printf("3070_orig.bin already there, skipping this step.\n");
  }else{
    if (resin86) { // If resourceHacker is in x86 folder
      system("\"\\Program Files (x86)\\Resource Hacker\\ResourceHacker.exe\" -open OSupdateDLL_orig.dll -save 3070extract.bin -action extract -mask RCData,3070,");
    }else {
      system("\"\\Program Files\\Resource Hacker\\ResourceHacker.exe\" -open OSupdateDLL_orig.dll -save 3070extract.bin -action extract -mask RCData,3070,");
    }

    //Now deflate that stuff.


    strm.zalloc   = Z_NULL;
    strm.zfree    = Z_NULL;
    strm.opaque   = Z_NULL;
    strm.avail_in = 0;
    strm.next_in  = in;
  
    ret = inflateInit2(&strm, 16+MAX_WBITS); //16 stands for gzip
    if (ret != Z_OK) {
      printf("  ERROR! Zlib error %d\n", ret);
      if (ret == Z_MEM_ERROR) {
        printf("  ERROR! Zlib has not enough memory. :-(\n");
      }
      fgets(str, 3,stdin);
      return ret;
    }
    //so inflateInit2 was ok
  
    //open the input file
    //FILE *Fin;
    Fin = fopen("3070extract.bin","rb"); //Read Binary
    if (Fin == NULL) {
      printf("  ERROR! The file 3070extract.bin could not be opened... :-(\n");
      fgets(str, 3,stdin);
      return -1;
    }
    //open the output file
    //FILE *Fout;
    Fout = fopen("3070_orig.bin","wb"); //Write Binary
    if (Fout == NULL) {
      printf("ERROR! The file 3070_orig.bin could not be opened for writing... :-(\n");
      return -1;
    }
    //now all files are open. Now start the inflation.
  
    //The header the calculator company removed, read the article by the6p4c
    in[0]=0x1F;in[1]=0x8B;in[2]=0x08;in[3]=0x00;in[4]=0x00;in[5]=0x00;in[6]=0x00;in[7]=0x00;in[8]=0x04;in[9]=0x00;
    //read from 0x0000 to 0x2FF5 into the var "in" at 0x000A to 0x2FFF
    fread(in+10,1,0x2FF6,Fin);
    //The next byte is the hardcoded byte.
    in[0x3000]=0x9b;//0x0B; The file 3069 has 0B at this location, 3070 has 9B in this location, we are inflating 3070 right now. (We don't need 3069)
    //Now there are 0x3001 bytes (from 0 to 0x3000, don't forget the 0)
    strm.avail_in = 0x3001;
  
    printf("unzipping the binary (This may take a while)\n\
  (The resource is a gzip file without the first 10 bytes. The byte 9B at 0x3000 is\n\
  also removed and has to be added again.)\nJust wait a moment");
  
    do {
      strm.avail_out = CHUNK;
      strm.next_out = out;
      inflate(&strm, Z_NO_FLUSH); //I think inflation does not need to flush.
      unsigned have = CHUNK - strm.avail_out;
      //write it to a file
      fwrite(out, 1, have, Fout);
    } while (strm.avail_out == 0);
    putc('.',stdout); //printf(".");
  
    //now the rest of the file:
    do {
      strm.avail_in = fread(in, 1, CHUNK, Fin);
      if (strm.avail_in == 0) {
        printf("\nFile End");
        break;
      }
      strm.next_in = in;
      do {
        strm.avail_out = CHUNK;
        strm.next_out = out;
        int ret = inflate(&strm, Z_NO_FLUSH); //I think inflation does not need to flush.
        unsigned have = CHUNK - strm.avail_out;
        //write it to a file
        fwrite(out, 1, have, Fout);
      } while (strm.avail_out == 0);
      putc('.',stdout);
    }while (ret != Z_STREAM_END);
    printf("\nSuccessfully inflated.\n"); 
    fclose(Fout); fclose(Fin); //I will open Forig in read mode later.
  }


//Create default mod.txt if not present
  if(access("mod.txt", R_OK) != -1 ){
    printf("There is a file called mod.txt. It will be used.\n");
  } else {
    Fin = fopen("mod.txt","wb");
    if (Fin == NULL){
      printf("  ERROR! Cannot create the file \"mod.txt\". Either let me create the default\n         version or create your own.\n");
      fgets(str, 3,stdin); return -1;
    }
    fputs( MOD_TXT ,Fin);
    fclose(Fin);

  }

  printf("\n\nNow we have the firmware binary.\n\
The next step is to modify it.\n\
If you wrote your own modification, call this file \"mod.txt\".\n\
The file starts with the address of the mod in rom (e.g.80133638) followed by\n\
The modification in hex. This is terminated by the letter * or by the end of\n\
the file. A mod.txt can have multiple sections. Spaces, \\r ans \\n are\n\
allowed, but ignored. You don't know, what this means? This will install\n\
\"hollyhock-2\" by default. Just hit Enter.\n\
\n\
[press ENTER to continue...]\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  fgets(str, 3,stdin);
  if (str[0]=='q') return 0;

  //Open input file. mod.txt
  Fin = fopen("mod.txt","rb"); 
  if (Fin == NULL) { //no file
    printf("\n  ERROR! The file \"mod.txt\" is missing. Did you just delete it? It was there\n         a second ago...");
    fgets(str, 3,stdin); return -1;
  } 
  //input File opened.
  
  //Check firmware version in mod.txt (Added in Snail2021)
  {
    //The first line may contain a version number store this in mod_txt_ver 
    //      'ver02.01.2000
    if (fgetc(Fin) == '\''){ //If it starts with a comment
      if (fgetc(Fin) == 'v'){ //If it starts with 'ver' it is the version info.
        if (fgetc(Fin) == 'e'){
          if (fgetc(Fin) == 'r'){
            for ( unsigned char i = 0; i < VERLEN; i++){
              int ch = fgetc(Fin);
	      if (ch==EOF){
	        printf("\n  ERROR! EOF in mod.txt.\n");
                fgets(str, 3,stdin); fclose(Fin); return -1;
              }
              mod_ver[i]=ch;
	    }
	    printf("Info: The file mod.txt is for version %s\n\n",mod_ver);
          }
	}
      }
    }
    //Go back to the beginning of the file.
    fseek(Fin, 0, SEEK_SET); 
  }

  //Open input file2. 3070_orig.bin
  Fin2 = fopen("3070_orig.bin","rb"); //binary
  if (Fin2 == NULL) { //no file
    printf("\n  ERROR! The file \"3070_orig\" is missing. I don't know what went wrong.\n         I was able to write to it a second ago...\n");
    fgets(str, 3,stdin); fclose(Fin); return -1;
  } //input File opened.

  //Check firmware version of 3070 (Added in Snail2021)
  if(mod_ver[0]!=0){ //If mod.txt contained a version (the var was initialised with 0)
    fseek(Fin2, 0x20020, SEEK_SET);
    printf("Checking version of 3070_orig.bin at offset 0x20020...\n");
    char bin_ver[VERLEN+1]; bin_ver[0]=0; bin_ver[VERLEN]=0;
    char ver_wrong = 0;
    for ( unsigned char i = 0; i < VERLEN; i++){
      int ch = fgetc(Fin2);
      if (ch==EOF){
        printf("\n  ERROR! EOF in 3070_orig.bin while checking version number.\n");
        fgets(str, 3,stdin); fclose(Fin);fclose(Fin2); return -1;
      }
      bin_ver[i]=ch;
      if (ch!=mod_ver[i]){ //Compare with the version of mod.txt
        ver_wrong = 1;
      }
    }
    if (ver_wrong){
      printf("\n\n\
  ##### ###   ###    ###  ###\n\
  #     #  #  #  #  #   # #  #\n\
  ##### ###   ###   #   # ###\n\
  #     #  #  #  #  #   # #  #\n\
  ##### #   # #   #  ###  #   #\n\
\n\n\
  ERROR! The version of the mod.txt is   \"%s\" but\n\
         the version of 3070_orig.bin is \"%s\".\n\n\
Make sure to use the right version of the updater. THIS IS NOT A JOKE! You have\n\
to use the right version because the addresses of functions are different!!!\n\
A mod for one version WILL NOT WORK with another version. There is even a risk\n\
of bricking the calculator. So make sure to use the right version.\n\
(For hollyhock-2 use version 02.01.2000 !!!)\n\n\n\n\n\n\n\n",mod_ver,bin_ver);
      fgets(str, 3,stdin); fclose(Fin);fclose(Fin2); return -1;
    }
    fseek(Fin2, 0, SEEK_SET);
  }

  //Open output file.
  Fout = fopen("3070_mod.bin","wb"); //binary
  if (Fin == NULL) { //Error
    printf("\n  ERROR! Cannot open the file \"mod.txt\" for writing. I don't know what went\n         wrong...\n");
    fgets(str, 3,stdin); return -1;
  } //output File opened.

  long current_address = 0 ; //Current position in in and out files.
  int ch;

// needs to be repeated?
  char moddone = 0; //is set to 1 if done
  do{  

    //// Read Address from mod.txt

    int i = 0;
    unsigned long moda = 0; //the mod address 
    if (moddone==0){
      while (i<8) { //convert 8 characters //0 and 1 are ignored, i is 2
        ch = fgetc(Fin);
        //printf("Read character %x from File Fin\n",ch);
        if (ch >= '0' && ch <= '9'){ //0-9
          moda = (moda << 4) + (ch - '0'); //each character represents a nibble (4 bit)
        } else if (ch >= 'A' && ch <='F') {
          moda = (moda << 4) + (ch +10 -'A'); //each character represents a nibble (4 bit)
        } else if (ch >= 'a' && ch <='f') {
          moda = (moda << 4) + (ch +10 -'a'); //each character represents a nibble (4 bit)
        } else if (ch == ' ' || ch == '\r' || ch == '\n'){
          continue;
        } else 
        //If there is a comment starting with ' and ending with \r or \n
        if (ch == '\'') {
          while (ch != '\n' && ch != '\r' && ch != EOF){
            ch = fgetc(Fin); //read next character
          }
          continue;
        } else if (ch == EOF) {
          moddone = 1;
          break;
        } else {
          printf("  ERROR! The file \"mod.txt\" has an error.\n         Wrong Character '%c'(0x%2x) in an address.", ch, ch);
          fgets(str, 3,stdin); return -1;    
        }
        i++; //When the character was a valid digit
      }
    }
    if (moddone) {
      printf("All modifications done, finishing 3070_mod.bin\n");
      moda = 0x1500000; //copy 'til the end
    } else {
      printf("  Modifying Address %x\n", moda);
      moda -= 0x80000000;
      if (moda > 0x14fffff){
        printf("  ERROR! The file \"mod.txt\" was created by an idiot. The firmware is only\n         0x14ffff bytes long. I can't modify 0x%x!!!\n", moda);
        fgets(str, 3,stdin); return -1;    
      }
    }
    //so wen need to copy everything before this mod.
    //we are currently at 'current_address' in Fin2 and in Fout.
    //we need to copy until before 'moda'
    //that are (moda - current_address) bytes.
    //e.g. we are at 0, we want to mod 9, we need to copy 9-0 = 9 bytes from 0-8
    //if that is too much, we do it in multiple steps.
    //current_address points to the next address that is written to.
    printf("Copying");
    while (true) {
      unsigned long copylen = moda - current_address;
      //printf("Copying 0x%x bytes.. ", copylen);
      fputc('.',stdout);
      if (copylen == 0){
        break; //copy until we are there
      }
      if (copylen > CHUNK){ //I want to use our array with the same size.
        copylen = CHUNK;
      }
      if (fread(in, 1, copylen, Fin2) !=copylen){ // read the bytes
        printf("\n\n\n\n  ERROR! Reached the end of 3070_orig.bin without performing all mods.\n\
         There are two things that could have happened:\n\
       - Either 3070_orig.bin has an error, in this case just delete it and\n\
         extract it from the updater again.\n\
       - Or mod.txt has an error. If you supplied your own mod.txt fix the\n\
         error. (make sure to order the modifications  by their addresses.)\n\
         Or, if you want to use the default mod.txt (aka if you want to install\n\
         hollyhock-2), delete mod.txt. The default mod.\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        fgets(str, 3,stdin); return -1;}
      fwrite(in, 1, copylen, Fout); //write the bytes
      current_address += copylen;
      //printf("Copied 0x%x bytes\n", copylen);
    }

    //Now we are at the correct address.
    if (moddone) {
      printf("End of file reached\n");
      break;
    }
    printf("Modifying");
    unsigned char thisbyte = 0;
    //low or high nibble
    char lohi = 0; // Read the high nibble
    //        = 1; // Read the low  nibble
    //        = 2; // both are read, now save that...
    do {
      ch = fgetc(Fin); //read next character

      //Numbers 0-9
      if (ch >= '0' && ch <= '9'){ //0-9
        if (!lohi) {
          //read first nibble
          thisbyte = (ch - '0') << 4; //each character represents a nibble (4 bit)
          lohi = 1;
        }else{
          //read second nibble
          thisbyte += (ch - '0'); //each character represents a nibble (4 bit)
          lohi = 2;
        }
      } else
      //Numbers A-F
      if (ch >= 'A' && ch <= 'F'){ //A-F
        if (!lohi) {
          //read first nibble
          thisbyte = (ch +10 - 'A') << 4; //each character represents a nibble (4 bit)
          lohi = 1;
        }else{
          //read second nibble
          thisbyte += (ch +10 - 'A'); //each character represents a nibble (4 bit)
          lohi = 2;
        }
      } else
      //Numbers a-f
      if (ch >= 'a' && ch <= 'f'){ //a-f
        if (!lohi) {
          //read first nibble
          thisbyte = (ch +10 - 'a') << 4; //each character represents a nibble (4 bit)
          lohi = 1;
        }else{
          //read second nibble
          thisbyte += (ch +10 - 'a'); //each character represents a nibble (4 bit)
          lohi = 2;
        }
      } else
      //If there is a comment starting with ' and ending with \r or \n
      if (ch == '\'') {
        while (ch != '\n' && ch != '\r' && ch != EOF){
          ch = fgetc(Fin); //read next character
        }
      }
      //Test if a full byte was read
      if (lohi==2) {
        fputc(thisbyte, Fout);
        fputc('.',stdout);
        current_address ++;
        if ( fgetc(Fin2) == EOF){ //This byte is not needed, it gets replaced by the mod. 
          printf("  ERROR! You cannot modify anything outside the ROM. Either you tried to write\n\
         to an address after the end of the file or there is a file error\n\
         with3070_orig.\n");
          fgets(str, 3,stdin); return -1;}
        lohi = 0; //read next byte
      }
    } while(ch !=EOF && ch!= '*');
    fputc('\n',stdout); //Printing the dots while modifying
    if (ch==EOF){
      moddone=1;
    }
  } while(true); 
  (void)fclose(Fin);
  (void)fclose(Fin2);
  (void)fclose(Fout);
  printf("\nYayyyyy the firmware is modified. Now we need to execute every step in reverse..\n\n");
printf("           ___\n\
          /   \\\n\
         ( 8 8 )\n\
      \\\\  \\ * /  //\n\
       \\\\   H   //       /  +---+\n\
        \\\\=XXX=//      /  / |[ ]|\n\
           XXX          //  |789|\n\
           XXX          / / |123|\n\
          // \\\\             +---+\n\
          || ||\n\
          || ||\n\
          || ||        The flying calc\n\
         HHH HHH\n\
\n\n\n\n\nI think drawing doesn't make this program faster. Maybe I should program more\nand I could finish this in this century...\n\n\n\n\n\
First, compress that stuff again...\nWhy do I have to do this...\n\n\n\n\n");

  //Bäää why, why do I have to do this

  //This zlib stuff. When I read it yesterday for the first time, I thaught,
  //I have to copy and paste everything from somebody else, but now I can do it
  //forwards and backwards. 
  //(The pun inflate is forwards and deflate is backwards...)

  strm.zalloc    = Z_NULL;
  strm.zfree     = Z_NULL;
  strm.opaque    = Z_NULL;
  strm.avail_in  = 0;
  strm.next_in   = in;
  strm.avail_out = 0;
  strm.next_out  = out;
                    //z_streamp, level, method, windowBits, memLevel, strategy
  ret = deflateInit2(&strm, LEVEL, Z_DEFLATED, 16+MAX_WBITS, memLevel, Z_DEFAULT_STRATEGY); //16 stands for gzip
  if (ret != Z_OK) {
    printf("  ERROR! Zlib Error %d\n", ret); 
    fgets(str, 3,stdin); return ret;
  }
  //open input file
  Fin = fopen("3070_mod.bin","rb"); //Binary mode!!! Windows is stupidoo
  if (Fin == NULL) {
    printf("  ERROR! Your computer is so strange. I can't open \"3070_mod.bin\".\n");
    fgets(str, 3,stdin); return -1;
  }
  //output file


  Fout = fopen("3070new.bin","wb"); //Binary mode
  if (Fout == NULL) {
    printf("  ERROR! Your computer is so strange. I can't open \"3070new.bin\".\n");
    fgets(str, 3,stdin); return -1;
  }
  printf("\nWow, that are a lot of files that are called 3070.\n\
  3070exxtract.bin - The resource extractet from OSupdateDLL\n\
  3070_orig.bin    - The uncompressed version of this, the raw memory\n\
  3070_mod.bin     - The modified raw memory (using mod.txt)\n\
  3070new.bin      - The modified version in compressed form, ready for the DLL\n\n\
Now compressing...\n");// ( . input  | output)\n");

  int flush = Z_NO_FLUSH; //don't flush
  char firststuff = 1; //collect first full buffer, so that we can do that stuff
  strm.avail_out = CHUNK;
  strm.next_out = out;
  do {
    strm.avail_in = fread(in, 1, CHUNK, Fin);
    //strm.avail_in = fread(in, 1, 0x2000, Fin); //test what happens when zlib returns less
    if (feof(Fin)){
      //fputc(':',stdout);
      flush = Z_FINISH; //Flush the gzip stuff
    } //else {
      //fputc('.',stdout);
    //}
    strm.next_in = in;

    do {
      if (!firststuff){ //don't clear output while firststuff
        strm.avail_out = CHUNK;
        strm.next_out = out;
      }
      deflate(&strm, flush);
      unsigned have = CHUNK - strm.avail_out; //how much was written
      //if (have > 0) {
      //  fputc('|',stdout);
      //}
      if (firststuff){
        if (have>0x3001){ // trash 0-9; copy a-2fff; trash 3000; copy from 3001
          printf("Doing that stuff...\n");
          fwrite(out+10,1,0x3000-10,Fout);
          printf("The Magic Byte is: 0x%2x\n%8d#%7d",out[0x3000],0x3000-10,have-0x3001);
          theMagicByte = out[0x3000];
          fwrite(out+0x3001,1,have-0x3001,Fout);
          firststuff=0;
        } else {
          printf("Zlib gave to little, waiting... :-(\n");
        }
      } else {
        //printf("use %d characters\n", have);
        printf("%8x", have);
        if (fwrite(out, 1, have, Fout) != have){
          printf("\n  ERROR! Why can't I write to this stupid file?\n");
          fgets(str, 3,stdin); return -1;
        }
      }
    } while (strm.avail_out == 0);
    if (strm.avail_in != 0) {
      printf("  ERROR! Zlib didn't ate all of it's food.\n");
      fgets(str, 3,stdin); return -1;
    }
  } while (flush != Z_FINISH);

  (void)fclose(Fin);
  (void)fclose(Fout);
  printf("Successfully packed the firmware into the archive.\n\
Now modify the dll file and save as \"OSupdate_mod.dll\".\n");      
  if (resin86) { // If resourceHacker is in x86 folder
    system("\"\\Program Files (x86)\\Resource Hacker\\ResourceHacker.exe\" -open OSupdateDLL_orig.dll -save OSupdateDLL_mod.dll -res 3070new.bin -action addoverwrite -mask RCData,3070,");
  } else {
    system("\"\\Program Files\\Resource Hacker\\ResourceHacker.exe\" -open OSupdateDLL_orig.dll -save OSupdateDLL_mod.dll -res 3070new.bin -action addoverwrite -mask RCData,3070,");
  }
  printf("Look at the last message, if everything was successful.\n\n\
In the last step we will modify the binary value in the dll (from 0x3000)\n");

  //patching the binary!!!
  //theMagicByte;


  Fin = fopen("OSupdateDLL_mod.dll","rb+");
  //Fout = fopen("OSupdateDLL_mod.dll","wb");
  if (Fin == NULL) {
    printf("  ERROR! - Cannot open \"OSupdateDLL_mod.dll\" in \"rb+\" mode.");
    fgets(str, 3,stdin); return -1;
  } 
  //fread (in, 1, 0x2e51, Fin);
  //printf("The old byte is 0x%02x, the new one is 0x%02x \n", fgetc(Fin), theMagicByte);
  //fwrite(in, 1, 0x2e51, Fout);
  fseek(Fin, 0x2e51, SEEK_SET);
  fputc(theMagicByte, Fin);
  fclose(Fin);
  printf("The byte is changed to 0x%02x \n", theMagicByte);
  //fclose(Fout);


  //mod bat
  printf("Now creating the \"click_to_modify_the_calculator.bat\" file.\n");
  Fout = fopen("click_to_modify_the_calculator.bat","w");
  if (Fout == NULL) {
    printf("Error while creating \"click_to_modify_the_calculator.bat\"\n");
  } else {
    fputs("\
echo off\r\n\
color f0\r\n\
cls\r\n\
echo ########################################\r\n\
echo #                                      #\r\n\
echo #  Press [EXP] [/\\] [Clear] and Reset  #\r\n\
echo #                                      #\r\n\
echo ########################################\r\n\
rundll32 OSupdateDLL_mod.dll,OSUpdate\r\n",Fout);
    fclose(Fout);
  }
  //orig bat
  Fout = fopen("click_to_revert_changes_on_the_calc.bat","w");
  if (Fout == NULL) {
    printf("Error while creating \"click_to_revert_changes_on_the_calc.bat\"\n");
  } else {
    fputs("\
echo off\r\n\
color f0\r\n\
cls\r\n\
echo ########################################\r\n\
echo #                                      #\r\n\
echo #  Press [EXP] [/\\] [Clear] and Reset  #\r\n\
echo #                                      #\r\n\
echo ########################################\r\n\
rundll32 OSupdateDLL_orig.dll,OSUpdate\r\n",Fout);
    fclose(Fout);
  }

printf(
"\n\n\
  ########################################################\n\
  #                                                      #\n\
  #  Connect your calculator to the USB port.            #\n\
  #  Hold [EXP] + [^] + [Clear] on the calculator while  #\n\
  #  pressing [reset] on the back to enter update mode.  #\n\
  #                                                      #\n\
  ########################################################\n\
\n[press ENTER to continue] [And hit the OK button to start the update]\n");
  fgets(str, 3,stdin);
  if (str[0]=='q') return 0;
  printf("\nThe updater will start now...\n\n\
If you want to install the update on another calculator or if you\n\
want to undo the changes, doubleclick the file in this folder, where the name\n\
starts with \"click_to_\".\n\
\n\
If there is an error with some dll stuff, just hit ok.\n\
In this case the language file didn't work, just hit ok.\n\
If this happens, there will be no text, but the update will still work.\n\
");

  system("start rundll32 OSupdateDLL_mod.dll,OSUpdate");

  printf("\nEverything done. The update may take up to 10 minutes.\n\n\
Have Fun!!!\n\n\
[press ENTER to close this program...]\n");

  fgets(str, 3,stdin); return -1;
}
