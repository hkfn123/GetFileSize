//
//  main.c
//  FileSize
//
//  Created by zhan zhi on 2/13/15.
//  Copyright (c) 2015 zhan zhi. All rights reserved.
//

#include <stdio.h>
#import <dirent.h>
#import <sys/stat.h>
#import <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define k_file_path_length  1024

static long long getFileSize(const char *path);
static int deleteFileAtPath(const char *path);

int main(int argc, const char * argv[]) {
    
    printf("%lld\n",getFileSize("/Users/***/Desktop/test"));
    printf("%d\n",deleteFileAtPath("/Users/***/Desktop/test"));
    
    return 0;
}


static int deleteFileAtPath(const char *path){
    char filepath[k_file_path_length] = {0};
    struct stat file_stat = {0};
    
    if (stat(path, &file_stat) == -1){
        perror("error:%m");
        return -1;
    }
    
    
    else{
        
        if(S_ISDIR(file_stat.st_mode)){
            DIR *dir;
            struct dirent *file;
            
            if (!(dir = opendir(path))) {
                printf("open dir error.\n");
                return -1;
            }
            
            while ((file = readdir(dir)) != NULL) {
                memset(filepath, 0, k_file_path_length);
                if (strcmp(file->d_name,".") == 0 ||
                    strcmp(file->d_name,"..") == 0)
                    continue;
                sprintf(filepath,"%s/%s",path,file->d_name);
                deleteFileAtPath(filepath);
            }
            rmdir(path);
        }
        
        else if (S_ISREG(file_stat.st_mode)){
            remove(path);
        }
    }
    return 0;
}


static long long getFileSize(const char *path){
    long long fileSize = 0;
    char filepath[k_file_path_length] = {0};
    struct stat file_stat = {0};
    
    if (stat(path, &file_stat) == -1){
        perror("error:%m");
        return fileSize;
    }

    
    else{
        
        if(S_ISDIR(file_stat.st_mode)){
            DIR *dir;
            struct dirent *file;
            
            if (!(dir = opendir(path))) {
                printf("open dir error.\n");
                return fileSize;
            }
            
            while ((file = readdir(dir)) != NULL) {
                memset(filepath, 0, k_file_path_length);
                if (strcmp(file->d_name,".") == 0 ||
                    strcmp(file->d_name,"..") == 0)
                    continue;
                sprintf(filepath,"%s/%s",path,file->d_name);
                fileSize += getFileSize(filepath);
            }
        }
        
        else if (S_ISREG(file_stat.st_mode)){
            fileSize += file_stat.st_size;
        }
    }
    return fileSize;
}


