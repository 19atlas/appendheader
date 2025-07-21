// appendheader  add DHTB to boot.img file
// Copyright (C) 2024  19atlas

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOOT_MAGIC              "ANDROID!"
#define BOOT_MAGIC_SIZE           8

int main(int argc, char** argv) {
    FILE *sourceFile, *destinationFile;
    int stay = argc; // if 3 delete input file and create boot.img file
    char *dhtb = "DHTB";
    char nullString[508] = {0}; // create null string 508 bytes long

    // yeni eklenen SEANDROIDENFORCE charı
    char *seandroid_str = "SEANDROIDENFORCE";
    int add_seandroid = 0; // -s etiketi kontrolü

    // i/o file names
    char* iname = NULL;
    char* oname = "new_boot.img";
    
    argc--;
    argv++;
    while(argc > 0) { // get file names via commandline
        char *arg = argv[0];
        char *val = argv[1];
        // -s etiketi için özel kontrol
        if (!strcmp(arg, "-s") || !strcmp(arg, "--seandroid")) {
            add_seandroid = 1;
            argc -= 1;
            argv += 1;
            continue;
        }
        argc -= 2;
        argv += 2;
        if (!strcmp(arg, "--input") || !strcmp(arg, "-i")) {
            iname = val;
        }
        else if (!strcmp(arg, "--output") || !strcmp(arg, "-o")) {
            oname = val;
        }
    }

    // get input and output file names
    if (iname == NULL) {
        printf("appendheader -i [input file] -o [output file](optional) [-s]\n");
        return 1;
    }

    sourceFile = fopen(iname, "rb"); // open source file in read and write mode
    if (sourceFile == NULL) {
        printf("source file %s didn't open.\n", iname);
        return 1;
    }
    
    // get file path
    char* gwd = realpath(iname, NULL);
    printf("boot file dir: %s\n",gwd);
    
    // check for DHTB magic
    const char DHTB_CHAR[] = {0x44, 0x48, 0x54, 0x42};
    char tmp[4096];
    fseek(sourceFile, 0, SEEK_SET);
    if(fread(tmp, sizeof(DHTB_CHAR), 1, sourceFile)){};
    if (memcmp(tmp, DHTB_CHAR, sizeof(DHTB_CHAR)) == 0) {
        printf("DHTB header magic already present!\n");
        fclose(sourceFile);
        return 1;
    }

    // check for ANDROID! magic
    // fseek(sourceFile, 0, SEEK_SET);
    // fread(tmp, BOOT_MAGIC_SIZE, 1, sourceFile);
    // if (memcmp(tmp, BOOT_MAGIC, BOOT_MAGIC_SIZE) != 0) {
    //     printf("(ANDROID!) magic not found!\n");
    //     fclose(sourceFile);
    //     return 1;
    // }

    destinationFile = fopen(oname, "wb"); // open target file in write mode and binary mode
    if (destinationFile == NULL) {
        printf("output file %s didn't open.\n", oname);
        return 1;
    }

    fseek(sourceFile, 0, SEEK_END); // positioning at the end of the file

    // read current contents of boot.img
    long fileSize = ftell(sourceFile);
    char *fileContent = malloc(fileSize);
    fseek(sourceFile, 0, SEEK_SET);
    fread(fileContent, 1, fileSize, sourceFile);

    // writing "DHTB" at the beginning of the file followed by a 508 byte long null string
    fseek(sourceFile, 0, SEEK_SET);
    fwrite(dhtb, sizeof(char), strlen(dhtb), destinationFile);
    fwrite(nullString, sizeof(char), sizeof(nullString), destinationFile);
    fwrite(fileContent, 1, fileSize, destinationFile);

    // -s etiketi varsa SEANDROIDENFORCE stringini sona ekle
    if(add_seandroid) {
        fwrite(seandroid_str, sizeof(char), strlen(seandroid_str), destinationFile);
        printf("SEANDROIDENFORCE appended to boot.img\n");
    }

    printf("appended DHTB to boot.img\n");
    
    // close files
    fclose(sourceFile);
    fclose(destinationFile);
    
    // delete input file and rename output file to "boot.img" and move to working dir
     if (stay == 3) {
        if (remove(iname) == 0) {
            printf("deleted %s successfully\n", iname);
            if(rename(oname, gwd) == 0){ // move and rename
                printf("created boot.img\n");
            }
        }
        else {
            printf("Unable to delete %s file\n", iname);
            return 1;
        }
    }

    return 0;
}